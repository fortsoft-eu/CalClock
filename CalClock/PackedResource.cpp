/**
 * This is open-source software licensed under the terms of the MIT License.
 *
 * Copyright (c) 2026 Petr Červinka - FortSoft <cervinka@fortsoft.eu>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 **
 * Last modified for version 1.7.2.5
 */

#include "PackedResource.h"

/// Tracks compressed input, buffered DEFLATE bits and decoding validity.
struct Bits {
    const BYTE* p;
    DWORD n;
    DWORD pos;
    DWORD buf;
    int have;
    BOOL ok;
};

/// Stores canonical Huffman code-length counts and their ordered symbols.
struct Huff {
    WORD count[16];
    WORD symbol[288];
};

static const DWORD packedSignature = 0x4D494450;

/// Fills a memory region with zero bytes.
static void zero(void* a, DWORD n) {
    BYTE* p = (BYTE*)a;
    while (n--) {
        *p++ = 0;
    }
}

/// Reads an unaligned 32-bit little-endian value.
static DWORD u32(const BYTE* p) {
    return p[0] | (DWORD)p[1] << 8 | (DWORD)p[2] << 16 | (DWORD)p[3] << 24;
}

/// Calculates the ZIP-compatible CRC32 checksum of a byte sequence.
static DWORD crc(const BYTE* p, DWORD n) {
    DWORD c = ~0UL;
    while (n--) {
        c ^= *p++;
        for (int k = 0; k < 8; k++) {
            c = c >> 1 ^ (0UL - (c & 1) & 0xEDB88320UL);
        }
    }
    return ~c;
}

/// Allocates a byte buffer from the process heap. Returns null on failure.
static void* alloc(DWORD n) {
    return HeapAlloc(GetProcessHeap(), 0, n);
}

/// Releases a process-heap buffer. Accepts a null pointer.
static void release(void* p) {
    if (p) {
        HeapFree(GetProcessHeap(), 0, p);
    }
}

/// Reads n bits from a DEFLATE stream, least significant bit first.
/// Marks the stream invalid if the input ends before enough bits are available.
static unsigned bits(Bits* b, int n) {
    while (b->have < n) {
        if (b->pos == b->n) {
            b->ok = FALSE;
            return 0;
        }
        b->buf |= (DWORD)b->p[b->pos++] << b->have;
        b->have += 8;
    }
    unsigned v = b->buf & (1UL << n) - 1;
    b->buf >>= n;
    b->have -= n;
    return v;
}

/// Builds a canonical Huffman decoding table from symbol code lengths.
/// Rejects invalid lengths and oversubscribed trees.
static BOOL tree(Huff* h, const BYTE* l, int n) {
    WORD off[16] = {};
    zero(h, sizeof(*h));
    for (int i = 0; i < n; i++) {
        if (l[i] > 15) {
            return FALSE;
        }
        h->count[l[i]]++;
    }
    int left = 1;
    for (int k = 1; k <= 15; k++) {
        left = left * 2 - h->count[k];
        if (left < 0) {
            return FALSE;
        }
    }
    off[1] = 0;
    for (int k = 1; k < 15; k++) {
        off[k + 1] = off[k] + h->count[k];
    }
    for (int i = 0; i < n; i++) {
        if (l[i]) {
            h->symbol[off[l[i]]++] = (WORD)i;
        }
    }
    return TRUE;
}

/// Decodes one Huffman symbol, or returns -1 and marks the stream invalid.
static int symbol(Bits* b, Huff* h) {
    unsigned code = 0, first = 0, index = 0;
    for (int n = 1; n <= 15; n++) {
        code |= bits(b, 1);
        unsigned count = h->count[n];
        if (code >= first && code - first < count) {
            return h->symbol[index + code - first];
        }
        index += count;
        first = (first + count) << 1;
        code <<= 1;
    }
    b->ok = FALSE;
    return -1;
}

/// Decodes a raw RFC 1951 DEFLATE stream into a fixed-size output buffer.
/// Supports stored, fixed-Huffman, and dynamic-Huffman blocks and checks buffer bounds.
/// Returns TRUE only when input consumption and output length match the supplied sizes.
static BOOL inflate(const BYTE* src, DWORD ns, BYTE* out, DWORD no) {
    static const BYTE order[19] = { 16, 17, 18, 0, 8, 7, 9, 6, 10, 5, 11, 4, 12, 3, 13, 2, 14, 1, 15 };
    static const WORD lb[29] = {
        3,
        4,
        5,
        6,
        7,
        8,
        9,
        10,
        11,
        13,
        15,
        17,
        19,
        23,
        27,
        31,
        35,
        43,
        51,
        59,
        67,
        83,
        99,
        115,
        131,
        163,
        195,
        227,
        258
    };
    static const BYTE le[29] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
        1,
        1,
        1,
        2,
        2,
        2,
        2,
        3,
        3,
        3,
        3,
        4,
        4,
        4,
        4,
        5,
        5,
        5,
        5,
        0
    };
    static const WORD db[30] = {
        1,
        2,
        3,
        4,
        5,
        7,
        9,
        13,
        17,
        25,
        33,
        49,
        65,
        97,
        129,
        193,
        257,
        385,
        513,
        769,
        1025,
        1537,
        2049,
        3073,
        4097,
        6145,
        8193,
        12289,
        16385,
        24577
    };
    static const BYTE de[30] = {
        0,
        0,
        0,
        0,
        1,
        1,
        2,
        2,
        3,
        3,
        4,
        4,
        5,
        5,
        6,
        6,
        7,
        7,
        8,
        8,
        9,
        9,
        10,
        10,
        11,
        11,
        12,
        12,
        13,
        13
    };
    Bits b = { src, ns, 0, 0, 0, TRUE };
    DWORD pos = 0;
    BOOL last = FALSE;
    Huff h, d, c;
    BYTE lens[320] = {};
    while (!last && b.ok) {
        last = bits(&b, 1);
        unsigned type = bits(&b, 2);
        if (type == 0) {
            b.buf = 0;
            b.have = 0;
            unsigned len = bits(&b, 16), inv = bits(&b, 16);
            if ((len ^ inv) != 65535 || len > no - pos) {
                return FALSE;
            }
            while (len--) {
                out[pos++] = (BYTE)bits(&b, 8);
            }
            continue;
        }
        if (type == 1) {
            for (int i = 0; i < 288; i++) {
                lens[i] = (BYTE)(i < 144 ? 8 : i < 256 ? 9 : i < 280 ? 7 : 8);
            }
            if (!tree(&h, lens, 288)) {
                return FALSE;
            }
            for (int i = 0; i < 32; i++) {
                lens[i] = 5;
            }
            if (!tree(&d, lens, 32)) {
                return FALSE;
            }
        } else if (type == 2) {
            unsigned nl = bits(&b, 5) + 257, nd = bits(&b, 5) + 1, nc = bits(&b, 4) + 4;
            if (nl > 286) {
                return FALSE;
            }
            zero(lens, 320);
            for (unsigned i = 0; i < nc; i++) {
                lens[order[i]] = (BYTE)bits(&b, 3);
            }
            if (!tree(&c, lens, 19)) {
                return FALSE;
            }
            unsigned i = 0;
            while (i < nl + nd && b.ok) {
                int s = symbol(&b, &c);
                if (s < 0) {
                    return FALSE;
                }
                if (s < 16) {
                    lens[i++] = (BYTE)s;
                } else {
                    unsigned repeat;
                    BYTE v = 0;
                    if (s == 16) {
                        if (!i) {
                            return FALSE;
                        }
                        v = lens[i - 1];
                        repeat = bits(&b, 2) + 3;
                    } else if (s == 17) {
                        repeat = bits(&b, 3) + 3;
                    } else {
                        repeat = bits(&b, 7) + 11;
                    }
                    if (repeat > nl + nd - i) {
                        return FALSE;
                    }
                    while (repeat--) {
                        lens[i++] = v;
                    }
                }
            }
            if (!lens[256] || !tree(&h, lens, nl) || !tree(&d, lens + nl, nd)) {
                return FALSE;
            }
        } else {
            return FALSE;
        }
        while (true) {
            int s = symbol(&b, &h);
            if (!b.ok) {
                return FALSE;
            }
            if (s == 256) {
                break;
            }
            if (s < 256) {
                if (pos == no) {
                    return FALSE;
                }
                out[pos++] = (BYTE)s;
            } else {
                if (s > 285) {
                    return FALSE;
                }
                unsigned len = lb[s - 257] + bits(&b, le[s - 257]);
                int ds = symbol(&b, &d);
                if (ds < 0 || ds > 29) {
                    return FALSE;
                }
                unsigned dist = db[ds] + bits(&b, de[ds]);
                if (!b.ok || dist > pos || len > no - pos) {
                    return FALSE;
                }
                while (len--) {
                    out[pos] = out[pos - dist];
                    pos++;
                }
            }
        }
    }
    return b.ok && pos == no && b.pos == ns;
}

/// Validates a packed resource and decodes it only when its length and CRC32 agree.
bool UnpackLibraryBytes(const BYTE* packed, DWORD packedSize, BYTE** unpacked, DWORD* unpackedSize) {
    *unpacked = nullptr;
    *unpackedSize = 0;
    if (!packed || packedSize <= 12 || u32(packed) != packedSignature) {
        return false;
    }
    DWORD size = u32(packed + 4);
    if (!size || size > 128UL * 1024 * 1024) {
        return false;
    }
    BYTE* bytes = static_cast<BYTE*>(alloc(size));
    if (!bytes) {
        return false;
    }
    if (!inflate(packed + 12, packedSize - 12, bytes, size) || crc(bytes, size) != u32(packed + 8)) {
        release(bytes);
        return false;
    }
    *unpacked = bytes;
    *unpackedSize = size;
    return true;
}
