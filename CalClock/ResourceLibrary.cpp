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

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include "ResourceLibrary.h"
#include "PackedResource.h"
#include "resource.h"
#include <shlobj.h>
#include <wincrypt.h>
#include <cstring>
#include <memory>
#include <vector>

#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Shell32.lib")

static const DWORD resourceSignature = 0x4D494450;

/// Computes the ZIP-compatible CRC32 used by the existing packed-library format.
static DWORD ResourceChecksum(const BYTE* bytes, DWORD size) {
    DWORD checksum = ~0UL;
    while (size-- != 0) {
        checksum ^= *bytes++;
        for (int bit = 0; bit < 8; bit++) {
            checksum = checksum >> 1 ^ 0UL - (checksum & 1) & 0xEDB88320UL;
        }
    }
    return ~checksum;
}

/// Compares the cached file's complete contents against the embedded length and CRC32.
static bool ResourceCacheMatches(const std::wstring& path, DWORD size, DWORD checksum) {
    HANDLE file = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE,
        nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return false;
    }
    LARGE_INTEGER length = {};
    bool matches = GetFileSizeEx(file, &length) && length.QuadPart == size;
    if (matches) {
        std::vector<BYTE> bytes(size);
        DWORD offset = 0;
        while (matches && offset < size) {
            DWORD received = 0;
            matches = ReadFile(file, bytes.data() + offset, size - offset, &received, nullptr)
                && received != 0;
            offset += received;
        }
        matches = matches && ResourceChecksum(bytes.data(), size) == checksum;
    }
    CloseHandle(file);
    return matches;
}

/// Releases the process-heap buffer allocated by the shared resource decoder.
static void ReleaseResourceBytes(BYTE* bytes) {
    if (!HeapFree(GetProcessHeap(), 0, bytes)) {
        OutputDebugStringW(L"CalClock could not release its decoded icon-library buffer.\n");
    }
}

/// Flushes a complete decoded DLL to a temporary file and atomically installs it in the cache.
static HRESULT WriteResourceCache(const std::wstring& path, const BYTE* bytes, DWORD size) {
    std::wstring temporary = path + L"." + std::to_wstring(GetCurrentProcessId()) + L".partial";
    HANDLE file = CreateFileW(temporary.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL, nullptr);
    if (file == INVALID_HANDLE_VALUE) {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    HRESULT result = S_OK;
    DWORD offset = 0;
    while (SUCCEEDED(result) && offset < size) {
        DWORD written = 0;
        if (!WriteFile(file, bytes + offset, size - offset, &written, nullptr)) {
            result = HRESULT_FROM_WIN32(GetLastError());
        } else if (written == 0) {
            result = HRESULT_FROM_WIN32(ERROR_WRITE_FAULT);
        }
        offset += written;
    }
    if (SUCCEEDED(result) && !FlushFileBuffers(file)) {
        result = HRESULT_FROM_WIN32(GetLastError());
    }
    if (!CloseHandle(file) && SUCCEEDED(result)) {
        result = HRESULT_FROM_WIN32(GetLastError());
    }
    if (SUCCEEDED(result)
            && !MoveFileExW(temporary.c_str(), path.c_str(),
                MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        result = HRESULT_FROM_WIN32(GetLastError());
    }
    if (FAILED(result) && !DeleteFileW(temporary.c_str())) {
        OutputDebugStringW(L"CalClock could not remove its incomplete icon-library cache file.\n");
    }
    return result;
}

/// Resolves the profile cache and its SHA256-addressed library version without loading executable code.
static HRESULT ResourceCachePath(const BYTE* packed, DWORD packedSize, const std::wstring& cacheRoot,
        std::wstring* path) {
    std::wstring directory = cacheRoot;
    if (directory.empty()) {
        wchar_t local[MAX_PATH] = {};
        HRESULT result = SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, local);
        if (FAILED(result)) {
            return result;
        }
        directory = std::wstring(local) + L"\\FortSoft\\CalClock\\Libraries";
    }
    BYTE hash[32] = {};
    DWORD hashSize = sizeof(hash);
    if (!CryptHashCertificate2(L"SHA256", 0, nullptr, packed, packedSize, hash, &hashSize)) {
        return HRESULT_FROM_WIN32(GetLastError());
    }
    directory += L"\\";
    for (BYTE value : hash) {
        wchar_t encoded[3] = {};
        swprintf_s(encoded, L"%02X", value);
        directory += encoded;
    }
    int created = SHCreateDirectoryExW(nullptr, directory.c_str(), nullptr);
    if (created != ERROR_SUCCESS && created != ERROR_ALREADY_EXISTS) {
        return HRESULT_FROM_WIN32(created);
    }
    *path = directory + L"\\Resources.dll";
    return S_OK;
}

/// Validates and atomically extracts the complete embedded DLL, reusing an identical cached file.
HRESULT ResourceLibrary::Initialize(HINSTANCE instance, const std::wstring& cacheRoot) {
    path.clear();
    HRSRC resource = FindResourceW(instance, MAKEINTRESOURCEW(IDR_IMAGE_LIBRARY), RT_RCDATA);
    HGLOBAL loaded = resource == nullptr ? nullptr : LoadResource(instance, resource);
    const BYTE* packed = loaded == nullptr ? nullptr : static_cast<const BYTE*>(LockResource(loaded));
    DWORD packedSize = resource == nullptr ? 0 : SizeofResource(instance, resource);
    if (packed == nullptr || packedSize <= 12) {
        return HRESULT_FROM_WIN32(ERROR_RESOURCE_DATA_NOT_FOUND);
    }
    DWORD signature = 0;
    DWORD size = 0;
    DWORD checksum = 0;
    std::memcpy(&signature, packed, sizeof(signature));
    std::memcpy(&size, packed + 4, sizeof(size));
    std::memcpy(&checksum, packed + 8, sizeof(checksum));
    if (signature != resourceSignature || size == 0 || size > 128UL * 1024 * 1024) {
        return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
    }
    std::wstring destination;
    HRESULT result = ResourceCachePath(packed, packedSize, cacheRoot, &destination);
    if (FAILED(result)) {
        return result;
    }
    if (!ResourceCacheMatches(destination, size, checksum)) {
        BYTE* decoded = nullptr;
        DWORD decodedSize = 0;
        if (!UnpackLibraryBytes(packed, packedSize, &decoded, &decodedSize)) {
            return HRESULT_FROM_WIN32(ERROR_INVALID_DATA);
        }
        std::unique_ptr<BYTE, decltype(&ReleaseResourceBytes)> buffer(decoded, ReleaseResourceBytes);
        result = WriteResourceCache(destination, buffer.get(), decodedSize);
        if (FAILED(result)) {
            return result;
        }
    }
    path = destination;
    return S_OK;
}

/// Returns an owned icon at the requested index and native pixel dimensions, or null on failure.
HICON ResourceLibrary::LoadIconAtIndex(int index, int width, int height) const {
    HICON icon = nullptr;
    UINT extracted = PrivateExtractIconsW(path.c_str(), index, width, height, &icon, nullptr, 1, 0);
    if (extracted != 1 && icon != nullptr) {
        DestroyIcon(icon);
        icon = nullptr;
    }
    return icon;
}

/// Returns the extracted library's absolute path after successful initialization.
const std::wstring& ResourceLibrary::GetPath() const {
    return path;
}
