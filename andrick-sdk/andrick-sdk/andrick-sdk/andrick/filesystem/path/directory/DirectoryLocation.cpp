#include "DirectoryLocation.h"
using namespace andrick;

DirectoryLocation::DirectoryLocation(const DirectoryLocation& parentDir, std::string name) :
	PathLocation(parentDir.getPath(), name, parentDir.getPathType())
{

}

DirectoryLocation::DirectoryLocation(std::string parentPath, std::string name, const EnumPathType& pathType) :
	PathLocation(parentPath, name, pathType)
{

}

std::string DirectoryLocation::getPath() const
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