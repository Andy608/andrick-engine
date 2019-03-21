#ifndef ANDRICK_FILE_SYSTEM_H_
#define ANDRICK_FILE_SYSTEM_H_

#include <glad/glad.h>
#include "../memory/TrackableObject.h"
#include "../memory/NonCopyable.h"
#include "path/directory/DirectoryLocation.h"
#include "path/file/FileLocation.h"

namespace andrick
{
	class FileSystem : public TrackableObject, private NonCopyable
	{
		friend class AndrickCore;

	public:
		static FileSystem* getFS();

		//Creates a file/folder depending on the path location.
		virtual GLboolean createDirectory(const std::string& directory) = 0;
		virtual GLboolean createDirectory(const DirectoryLocation& directory) = 0;
		GLboolean createFile(const FileLocation& path);

		//Checks if the path is a real path on in the file system.
		GLboolean isDirectoryCreated(const std::string& path);
		GLboolean isDirectoryCreated(const DirectoryLocation& path);
		GLboolean isFileCreated(const FileLocation& path);

	protected:
		inline FileSystem() {};
		inline virtual ~FileSystem() {};

	private:
		static GLboolean mIsInitialized;
		static FileSystem* smpFileSystem;

		static GLboolean init();
		static void cleanup();
	};
}

#endif
