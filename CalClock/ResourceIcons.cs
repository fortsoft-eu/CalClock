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
using System.Collections.Generic;
using System.ComponentModel;
using System.IO;
using System.Runtime.InteropServices;

/// <summary>
/// Extracts native icon groups by zero-based resource index into standalone ICO files.
/// </summary>
public sealed class ResourceIcons {

    /// <summary>
    /// Receives each resource name during enumeration; returning true continues enumeration.
    /// </summary>
    private delegate bool ResourceNameCallback(IntPtr module, IntPtr type, IntPtr name, IntPtr parameter);

    /// <summary>
    /// Identifies an individual native icon image.
    /// </summary>
    private const int IconResource = 3;

    /// <summary>
    /// Identifies a native icon group containing the directory of its images.
    /// </summary>
    private const int GroupIconResource = 14;

    /// <summary>
    /// Maps the library as data without executing its initialization code.
    /// </summary>
    private const uint LoadLibraryAsDataFile = 0x00000002;

    /// <summary>
    /// Uses image-resource mapping so the resource APIs can read the mapped library.
    /// </summary>
    private const uint LoadLibraryAsImageResource = 0x00000020;

    /// <summary>
    /// Retains icon-group identifiers in the order reported by resource enumeration.
    /// </summary>
    private readonly List<IntPtr> names = new List<IntPtr>();

    /// <summary>
    /// Maps a library using the supplied loader flags and returns zero on failure.
    /// </summary>
    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    private static extern IntPtr LoadLibraryEx(string path, IntPtr file, uint flags);

    /// <summary>
    /// Enumerates resource names of the requested type through the supplied callback.
    /// </summary>
    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    private static extern bool EnumResourceNames(IntPtr module, IntPtr type,
        ResourceNameCallback callback, IntPtr parameter);

    /// <summary>
    /// Locates a named or numbered resource of the requested type in the mapped library.
    /// </summary>
    [DllImport("kernel32.dll", CharSet = CharSet.Unicode, SetLastError = true)]
    private static extern IntPtr FindResource(IntPtr module, IntPtr name, IntPtr type);

    /// <summary>
    /// Returns the size in bytes of a located resource.
    /// </summary>
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern uint SizeofResource(IntPtr module, IntPtr resource);

    /// <summary>
    /// Loads a located resource and returns its data handle, or zero on failure.
    /// </summary>
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr LoadResource(IntPtr module, IntPtr resource);

    /// <summary>
    /// Returns a resource-data pointer that remains valid while its library is mapped.
    /// </summary>
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern IntPtr LockResource(IntPtr resource);

    /// <summary>
    /// Releases the mapped library and reports whether the operation succeeded.
    /// </summary>
    [DllImport("kernel32.dll", SetLastError = true)]
    private static extern bool FreeLibrary(IntPtr module);

    /// <summary>
    /// Writes all images belonging to the selected icon group into one ICO file.
    /// </summary>
    public static void Extract(string library, int index, string destination) {
        ResourceIcons extractor = new ResourceIcons();
        extractor.ExtractIcon(library, index, destination);
    }

    /// <summary>
    /// Maps the library, enumerates its icon groups, writes the selected group and releases the mapping.
    /// </summary>
    private void ExtractIcon(string library, int index, string destination) {
        IntPtr module = LoadLibraryEx(library, IntPtr.Zero,
            LoadLibraryAsDataFile | LoadLibraryAsImageResource);
        if (module == IntPtr.Zero) {
            throw new Win32Exception(Marshal.GetLastWin32Error(), "Loading icon resources: " + library);
        }
        try {
            ResourceNameCallback callback = CollectIconName;
            if (!EnumResourceNames(module, new IntPtr(GroupIconResource), callback, IntPtr.Zero)) {
                throw new Win32Exception(Marshal.GetLastWin32Error(),
                    "Enumerating icon resources: " + library);
            }
            if (index < 0 || index >= names.Count) {
                throw new ArgumentOutOfRangeException("index", "The requested icon index is not present.");
            }
            WriteIcon(module, names[index], destination);
        } finally {
            if (!FreeLibrary(module)) {
                throw new Win32Exception(Marshal.GetLastWin32Error(), "Unloading icon resources: " + library);
            }
        }
    }

    /// <summary>
    /// Appends an icon-group identifier in enumeration order and returns true to continue enumeration.
    /// </summary>
    private bool CollectIconName(IntPtr module, IntPtr type, IntPtr name, IntPtr parameter) {
        names.Add(name);
        return true;
    }

    /// <summary>
    /// Finds and loads a nonempty resource, validates its size and copies its bytes into managed memory.
    /// </summary>
    private static byte[] ReadResource(IntPtr module, IntPtr name, int type) {
        IntPtr resource = FindResource(module, name, new IntPtr(type));
        if (resource == IntPtr.Zero) {
            throw new Win32Exception(Marshal.GetLastWin32Error(), "Finding an icon resource.");
        }
        uint size = SizeofResource(module, resource);
        IntPtr loaded = LoadResource(module, resource);
        if (loaded == IntPtr.Zero) {
            throw new Win32Exception(Marshal.GetLastWin32Error(), "Loading an icon resource.");
        }
        IntPtr data = LockResource(loaded);
        if (size == 0 || size > int.MaxValue || data == IntPtr.Zero) {
            throw new InvalidDataException("The icon resource is empty or invalid.");
        }
        byte[] bytes = new byte[size];
        Marshal.Copy(data, bytes, 0, bytes.Length);
        return bytes;
    }

    /// <summary>
    /// Validates the icon group, resolves its images and writes the ICO directory with image-file offsets.
    /// </summary>
    private static void WriteIcon(IntPtr module, IntPtr name, string destination) {
        byte[] group = ReadResource(module, name, GroupIconResource);
        if (group.Length < 6
                || BitConverter.ToUInt16(group, 0) != 0
                || BitConverter.ToUInt16(group, 2) != 1) {
            throw new InvalidDataException("Invalid icon group header.");
        }
        ushort count = BitConverter.ToUInt16(group, 4);
        if (count == 0 || group.Length < 6 + count * 14) {
            throw new InvalidDataException("Invalid icon group directory.");
        }
        List<byte[]> images = new List<byte[]>();
        for (int index = 0; index < count; ++index) {
            int entry = 6 + index * 14;
            ushort identifier = BitConverter.ToUInt16(group, entry + 12);
            byte[] image = ReadResource(module, new IntPtr(identifier), IconResource);
            uint length = BitConverter.ToUInt32(group, entry + 8);
            if (image.Length < length) {
                throw new InvalidDataException("The icon image length does not match its directory.");
            }
            Array.Resize(ref image, checked((int)length));
            images.Add(image);
        }
        using (BinaryWriter writer = new BinaryWriter(File.Create(destination))) {
            writer.Write((ushort)0);
            writer.Write((ushort)1);
            writer.Write(count);
            uint offset = (uint)(6 + count * 16);
            for (int index = 0; index < count; ++index) {
                writer.Write(group, 6 + index * 14, 12);
                writer.Write(offset);
                offset = checked(offset + (uint)images[index].Length);
            }
            foreach (byte[] image in images) {
                writer.Write(image);
            }
        }
    }
}
