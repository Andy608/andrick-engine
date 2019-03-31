#include "FileLocation.h"
#include "../directory/DirectoryLocation.h"
using namespace andrick;

const GLuint FileLocation::EXT_TYPES_LENGTH = 5;
std::string FileLocation::EXT_TYPES[] = { ".txt", ".png", ".obj", ".glsl", ".tga" };

std::string FileLocation::getExt(EnumExtensionType ext)
{
	if (ext < EXT_TYPES_LENGTH)
	{
		return EXT_TYPES[ext];
	}
	else
	{
		//use a warning console logger when they are set up and ready for use.
		std::cout << ("[FileLocation] Unknown file extension type. Could not map \'" + std::to_string(ext) + "\'extension to string.").c_str() << std::endl;
		return EXT_TYPES[0];
	}
}

FileLocation::FileLocation(const DirectoryLocation& parentPath, std::string name, const EnumExtensionType& extensionType) :
	PathLocation(parentPath.getPath(), name, parentPath.getPathType()),
	mEXT_TYPE(extensionType),
	mEXTENSION(getExt(extensionType))
{

}

FileLocation::FileLocation(std::string parentPath, std::string name, const EnumPathType& pathType, const EnumExtensionType& extensionType) :
	PathLocation(parentPath, name, pathType),
	mEXT_TYPE(extensionType),
	mEXTENSION(getExt(extensionType))
{

}

std::string FileLocation::getPath() const
{
	if (mPARENT_PATH.length() > 0)
	{
		return mPARENT_PATH + "/" + getNameAndExt();
	}
	else
	{
		return getNameAndExt();
	}
}

std::string FileLocation::getPathNoExt() const
{
	if (mPARENT_PATH.length() > 0)
	{
		return mPARENT_PATH + "/" + getName();
	}
	else
	{
		return getName();
	}
}