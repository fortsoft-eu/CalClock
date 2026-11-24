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
 * Last modified for version 1.7.3.1
 */

using System;
using System.IO;
using System.IO.Compression;

/// <summary>
/// Prepares compressed library and data resources during the native application's build.
/// </summary>
public static class ResourcePacker {

    /// <summary>
    /// Identifies the packed library-resource header consumed by the native decompressor.
    /// </summary>
    private const uint Signature = 0x4D494450;

    /// <summary>
    /// Writes the resource signature, original length and CRC32 followed by the source's DEFLATE-compressed
    /// bytes.
    /// </summary>
    /// <param name="source">The path of the original x86 PE library to embed without modifying its bytes.
    /// </param>
    /// <param name="destination">The path of the packed resource file to create or overwrite.</param>
    /// <exception cref="InvalidDataException">The source does not contain an x86 PE header.</exception>
    /// <exception cref="IOException">The source cannot be read or the destination cannot be written.
    /// </exception>
    /// <exception cref="UnauthorizedAccessException">Access to the source or destination is denied.
    /// </exception>
    public static void Pack(string source, string destination) {
        Pack(source, destination, false);
    }

    /// <summary>
    /// Packs library or raw data bytes with the same length, CRC32 and DEFLATE resource format.
    /// </summary>
    /// <param name="source">The input file to compress.</param>
    /// <param name="destination">The packed resource file to create or overwrite.</param>
    /// <param name="rawData">True for data; false retains the required x86 PE validation.</param>
    public static void Pack(string source, string destination, bool rawData) {
        byte[] data = File.ReadAllBytes(source);
        if (!rawData) {
            int pe = data.Length >= 64 ? BitConverter.ToInt32(data, 60) : -1;
            if (pe < 64
                    || pe > data.Length - 24
                    || BitConverter.ToUInt32(data, pe) != 0x4550
                    || BitConverter.ToUInt16(data, pe + 4) != 0x14C) {
                throw new InvalidDataException("Expected an x86 Windows library: " + source);
            }
        }
        uint crc = 0xFFFFFFFF;
        foreach (byte value in data) {
            crc ^= value;
            for (int bit = 0; bit < 8; bit++) {
                crc = crc >> 1 ^ ((crc & 1) != 0 ? 0xEDB88320 : 0);
            }
        }
        crc ^= 0xFFFFFFFF;
        using (FileStream stream = File.Create(destination)) {
            using (BinaryWriter writer = new BinaryWriter(stream)) {
                writer.Write(Signature);
                writer.Write((uint)data.Length);
                writer.Write(crc);
                writer.Flush();
                using (DeflateStream compressed = new DeflateStream(stream, CompressionLevel.Optimal, true)) {
                    compressed.Write(data, 0, data.Length);
                }
            }
        }
    }
}
