#if defined __APPLE__
#ifndef ANDRICK_MAC_FILE_SYSTEM_H_
#define ANDRICK_MAC_FILE_SYSTEM_H_

#include "FileSystem.h"

namespace andrick
{
	class MacFileSystem : public FileSystem
	{
		friend class FileSystem;

	public:
		//Creates a file/folder depending on the path location.
		virtual GLboolean createDirectory(const std::string& directory) override;
		virtual GLboolean createDirectory(const DirectoryLocation& directory) override;

	protected:
		inline MacFileSystem() {};
	};
}

#endif
#endif
