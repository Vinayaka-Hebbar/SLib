/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#ifndef CHECKHEADER_SLIB_CORE_FILE
#define CHECKHEADER_SLIB_CORE_FILE

#include "definition.h"

#include "list.h"
#include "io.h"

typedef sl_reg sl_file;
#define SLIB_FILE_INVALID_HANDLE ((sl_file)(-1))

namespace slib
{
	
	class FileMode
	{
	public:
		int value;
		SLIB_MEMBERS_OF_FLAGS(FileMode, value)
		
		enum {
			Read = 1,
			Write = 2,

			NotCreate = 0x00001000,
			NotTruncate = 0x00002000,
			SeekToEnd = 0x10000000,
			HintRandomAccess = 0x20000000,

			ReadWrite = Read | Write,
			Append = Write | NotTruncate | SeekToEnd,
			RandomAccess = Read | Write | NotTruncate | HintRandomAccess,
			RandomRead = Read | HintRandomAccess
		};
	};

	class FileAttributes
	{
	public:
		int value;
		SLIB_MEMBERS_OF_FLAGS(FileAttributes, value)

		enum {
			Default = 0,
			Directory = 1,
			Hidden = 2,
			NotExist = 0x8000
		};
	};
	
	class FilePermissions
	{
		int value;
		SLIB_MEMBERS_OF_FLAGS(FilePermissions, value)
		
		enum {
			ReadByOthers = 0x0001,
			WriteByOthers = 0x0002,
			ExecuteByOthers = 0x0004,
			Others = ReadByOthers | WriteByOthers | ExecuteByOthers,

			ReadByGroup = 0x0008,
			WriteByGroup = 0x0010,
			ExecuteByGroup = 0x0020,
			Group = ReadByGroup | WriteByGroup | ExecuteByGroup,

			ReadByUser = 0x0040,
			WriteByUser = 0x0080,
			ExecuteByUser = 0x0100,
			User = ReadByUser | WriteByUser | ExecuteByUser,

			Read = ReadByUser | ReadByGroup | ReadByOthers,
			Write = WriteByUser | WriteByGroup | WriteByOthers,
			Execute = ExecuteByUser | ExecuteByGroup | ExecuteByOthers,

			None = 0,
			All = Read | Write | Execute,
	
			ShareRead = 0x1000,
			ShareWrite = 0x2000,
			ShareReadWrite = ShareRead | ShareWrite,
			ShareDelete = 0x4000,
			ShareAll = ShareRead | ShareWrite | ShareDelete

		};
	
	};
	
	class SLIB_EXPORT File : public IO
	{
		SLIB_DECLARE_OBJECT
	
	private:
		sl_file m_file;

	public:
		File(sl_file file);
	
		~File();
	
	public:
		static Ref<File> open(const StringParam& filePath, const FileMode& mode, const FilePermissions& permissions);

		static Ref<File> open(const StringParam& filePath, const FileMode& mode);
	
		static Ref<File> openForRead(const StringParam& filePath, sl_bool flagShareRead = sl_true);

		static Ref<File> openForWrite(const StringParam& filePath);

		static Ref<File> openForReadWrite(const StringParam& filePath);

		static Ref<File> openForAppend(const StringParam& filePath);

		static Ref<File> openForRandomAccess(const StringParam& filePath);
	
		static Ref<File> openForRandomRead(const StringParam& filePath, sl_bool flagShareRead = sl_true);

		/*
			Physical Disks and Volumes
		 
				"\\\\.\\PhysicalDrive0"  (Win32)
				"\\\\.\\CdRom0"
				"\\\\.\\A:"
		 
		 		"/dev/disk0"  (macOS)
		 		"/dev/sda1"   (Linux)
		*/
		static Ref<File> openDevice(const StringParam& path, sl_bool flagRead, sl_bool flagWrite);

	public:
		void close() override;

		sl_bool isOpened() const;
		
		sl_file getHandle() const;
		
		void setHandle(sl_file handle);
		
		void clearHandle();

		sl_uint64 getPosition() override;

		sl_uint64 getSize() override;
		
		sl_bool seek(sl_int64 offset, SeekPosition from) override;
	

		sl_int32 read32(void* buf, sl_uint32 size) override;

		sl_int32 write32(const void* buf, sl_uint32 size) override;
	
	
		// works only if the file is already opened
		sl_bool setSize(sl_uint64 size) override;

		
		static sl_uint64 getSize(sl_file fd);
		
		static sl_uint64 getSize(const StringParam& path);
		
		static sl_uint64 getDiskSize(sl_file fd);
		
		static sl_uint64 getDiskSize(const StringParam& path);
		
		
		sl_bool lock();

		sl_bool unlock();
	
		sl_uint64 getDiskSize();

		
		Time getModifiedTime();

		Time getAccessedTime();

		Time getCreatedTime();

		static Time getModifiedTime(const StringParam& filePath);

		static Time getAccessedTime(const StringParam& filePath);

		static Time getCreatedTime(const StringParam& filePath);

		static sl_bool setModifiedTime(const StringParam& filePath, Time time);

		static sl_bool setAccessedTime(const StringParam& filePath, Time time);

		static sl_bool setCreatedTime(const StringParam& filePath, Time time);
	

		static FileAttributes getAttributes(const StringParam& filePath);

		static sl_bool exists(const StringParam& filePath);
	
		static sl_bool isFile(const StringParam& filePath);
	
		static sl_bool isDirectory(const StringParam& filePath);

		static sl_bool isHidden(const StringParam& filePath);
	
		static sl_bool setHidden(const StringParam& filePath, sl_bool flagHidden = sl_true);
	

		static sl_bool createDirectory(const StringParam& dirPath, sl_bool flagErrorOnCreateExistingDirectory = sl_false);

		static sl_bool createDirectories(const StringParam& dirPath);

		static sl_bool deleteFile(const StringParam& filePath, sl_bool flagErrorOnDeleteNotExistingFile = sl_false);
	

		// Deletes the directory and its sub-directories and files
		static sl_bool deleteDirectoryRecursively(const StringParam& dirPath);

		// Changes the path of file or directory. Don't replace the existing file.
		static sl_bool rename(const StringParam& filePathOriginal, const StringParam& filePathNew);
	

		static List<String> getFiles(const StringParam& dirPath);
	
		static List<String> getAllDescendantFiles(const StringParam& dirPath);
	

		Memory readAllBytes(sl_size maxSize = SLIB_SIZE_MAX);
		
		static Memory readAllBytes(const StringParam& path, sl_size maxSize = SLIB_SIZE_MAX);
		
		String readAllTextUTF8(sl_size maxSize = SLIB_SIZE_MAX);

		static String readAllTextUTF8(const StringParam& path, sl_size maxSize = SLIB_SIZE_MAX);

		String16 readAllTextUTF16(EndianType endian = Endian::Little, sl_size maxSize = SLIB_SIZE_MAX);
		
		static String16 readAllTextUTF16(const StringParam& path, EndianType endian = Endian::Little, sl_size maxSize = SLIB_SIZE_MAX);
		
		String readAllText(Charset* outCharset = sl_null, sl_size maxSize = SLIB_SIZE_MAX);

		static String readAllText(const StringParam& path, Charset* outCharset = sl_null, sl_size maxSize = SLIB_SIZE_MAX);
		
		String16 readAllText16(Charset* outCharset = sl_null, sl_size maxSize = SLIB_SIZE_MAX);

		static String16 readAllText16(const StringParam& path, Charset* outCharset = sl_null, sl_size maxSize = SLIB_SIZE_MAX);
	
		static sl_size writeAllBytes(const StringParam& path, const void* buf, sl_size size);

		static sl_size writeAllBytes(const StringParam& path, const Memory& mem);

		static sl_bool writeAllTextUTF8(const StringParam& path, const StringParam& text, sl_bool flagWriteByteOrderMark = sl_false);

		static sl_bool writeAllTextUTF16LE(const StringParam& path, const StringParam& text, sl_bool flagWriteByteOrderMark = sl_false);

		static sl_bool writeAllTextUTF16BE(const StringParam& path, const StringParam& text, sl_bool flagWriteByteOrderMark = sl_false);

		static sl_size appendAllBytes(const StringParam& path, const void* buf, sl_size size);

		static sl_size appendAllBytes(const StringParam& path, const Memory& mem);

		static sl_bool appendAllTextUTF8(const StringParam& path, const StringParam& text);

		static sl_bool appendAllTextUTF16LE(const StringParam& path, const StringParam& text);

		static sl_bool appendAllTextUTF16BE(const StringParam& path, const StringParam& text);

	
		static String getParentDirectoryPath(const String& path);

		static String getFileName(const String& path);

		static String getFileExtension(const String& path);

		static String getFileNameOnly(const String& path);

		static String normalizeDirectoryPath(const String& path);
	

		// converts any invalid characters (0~0x1f, 0x7f~0x9f, :*?"<>|\/) into "_"
		static String makeSafeFileName(const String& fileName);
	
		// converts any invalid characters (0~0x1f, 0x7f~0x9f, :*?"<>|) into "_"
		static String makeSafeFilePath(const String& filePath);
	
		static String findParentPathContainingFile(const String& basePath, const String& filePath, sl_uint32 nDeep = SLIB_UINT32_MAX);
	
#if defined(SLIB_PLATFORM_IS_UNIX)
		static sl_bool setNonBlocking(int fd, sl_bool flag);
#endif
		
		static String getRealPath(const StringParam& filePath);

	private:
		static sl_file _open(const StringParam& filePath, const FileMode& mode, const FilePermissions& permissions);

		static sl_bool _close(sl_file file);

		static sl_bool _createDirectory(const StringParam& dirPath);

		static sl_bool _deleteFile(const StringParam& dirPath);

		static sl_bool _deleteDirectory(const StringParam& dirPath);

	};
	
	// FilePathSegments is not thread-safe
	class SLIB_EXPORT FilePathSegments
	{
	public:
		sl_uint32 parentLevel;
		List<String> segments;
	
	public:
		FilePathSegments();
		
		SLIB_DECLARE_CLASS_DEFAULT_MEMBERS(FilePathSegments)

	public:
		void parsePath(const String& path);

		String buildPath();
	
	};

}

#endif
