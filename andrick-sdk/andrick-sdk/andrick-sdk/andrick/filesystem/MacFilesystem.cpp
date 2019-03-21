#if defined __APPLE__
#include "MacFileSystem.h"
#include <fstream>
#include <sys/stat.h>
using namespace andrick;

GLboolean MacFileSystem::createDirectory(const std::string& directory)
{
	GLboolean success;

	if (mkdir(directory.c_str(), 0777) == 0)
	{
		success = GL_TRUE;
	}
	else
	{
		success = GL_FALSE;
	}

	return success;
}

GLboolean MacFileSystem::createDirectory(const DirectoryLocation& directory)
{
	return createDirectory(directory.getPath());
}

#endif
