#if defined(_WIN32)

#include "WindowsFileSystem.h"
#include <fstream>
using namespace andrick;

GLboolean WindowsFileSystem::createDirectory(const std::string& directory)
{
	GLboolean success = GL_FALSE;

	try
	{
		//In the future we need to look into CreateDirectoryW
		if (CreateDirectoryA(directory.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
		{
			success = GL_TRUE;
			//logger.log(Logger::LEVEL_DEBUG, "Valid directory at: \'" + getPath() + "\'.");
		}
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
		//logger.log(Logger::LEVEL_ERROR, e.what());
	}

	return success;
}

GLboolean WindowsFileSystem::createDirectory(const DirectoryLocation& directory)
{
	return createDirectory(directory.getPath());
}

#endif
