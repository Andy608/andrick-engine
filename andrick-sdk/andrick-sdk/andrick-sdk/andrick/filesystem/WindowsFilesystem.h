#if defined(_WIN32)
#ifndef ANDRICK_WINDOWS_FILE_SYSTEM_H_
#define ANDRICK_WINDOWS_FILE_SYSTEM_H_

#include "FileSystem.h"

namespace andrick
{
	class WindowsFileSystem : public FileSystem
	{
		friend class FileSystem;

	public:

		//Creates a file/folder depending on the path location.
		virtual GLboolean createDirectory(const std::string& directory) override;
		virtual GLboolean createDirectory(const DirectoryLocation& directory) override;

	protected:
		inline WindowsFileSystem() {};
	};
}

#endif
#endif
