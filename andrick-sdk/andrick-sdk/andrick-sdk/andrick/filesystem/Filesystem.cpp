#include "FileSystem.h"
#include "WindowsFileSystem.h"
#include "MacFileSystem.h"
#include "../logger/LoggerMaster.h"
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
using namespace andrick;

GLboolean FileSystem::mIsInitialized = false;
FileSystem* FileSystem::smpFileSystem = nullptr;

GLboolean FileSystem::init()
{
	if (smpFileSystem == nullptr)
	{
		mIsInitialized = true;
#if defined(_WIN32)
		smpFileSystem = new WindowsFileSystem();
#elif defined(__APPLE__)
		smpFileSystem = new MacFileSystem();
#else
		smpFileSystem = nullptr;
		throw std::runtime_error("Unsupported system :(");
		mIsInitialized = false;
#endif
	}

	return mIsInitialized;
}

void FileSystem::cleanup()
{
	if (mIsInitialized)
	{
		delete smpFileSystem;
		smpFileSystem = nullptr;
		mIsInitialized = false;
	}
}

FileSystem* FileSystem::getFS()
{
	if (!smpFileSystem)
	{
		std::cout << "Make sure to init the file system first!" << std::endl;
	}

	return smpFileSystem;
}

GLboolean FileSystem::isDirectoryCreated(const std::string& path)
{
	GLboolean isCreated = GL_FALSE;
	struct stat info;

	if (stat(path.c_str(), &info) != 0)
	{
		/*if (LoggerMaster::isInitialized())
		{
			LoggerMaster::getUniversalLogger().logError(getClass(), "Cannot access path: \"" + path + "\".");
		}
		else
		{
			std::cout << "Cannot access path: " << path << "\"." << std::endl;
		}*/
	}
	else if (info.st_mode & S_IFDIR)
	{
		isCreated = GL_TRUE;
	}
	else
	{
		/*if (LoggerMaster::isInitialized())
		{
			LoggerMaster::getUniversalLogger().logInfo(getClass(), "No directory at: \"" + path + "\".");
		}
		else
		{
			std::cout << "No directory at: " << path << "\"." << std::endl;
		}*/
	}

	return isCreated;
}

GLboolean FileSystem::isDirectoryCreated(const DirectoryLocation& path)
{
	return isDirectoryCreated(path.getPath());
}

GLboolean FileSystem::isFileCreated(const FileLocation& path)
{
	std::ifstream inFileStream(path.getPath());
	return inFileStream.good();
}

GLboolean FileSystem::createFile(const FileLocation& path)
{
	GLboolean success;
	std::ofstream outFileStream;

	outFileStream.open(path.getPath(), std::fstream::app);

	if (outFileStream.good())
	{
		success = GL_TRUE;
	}
	else
	{
		success = GL_FALSE;
	}

	outFileStream.close();

	return success;
}
