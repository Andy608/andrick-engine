#ifndef ANDRICK_DIRECTORY_LOCATION_H_
#define ANDRICK_DIRECTORY_LOCATION_H_

#include "../PathLocation.h"

namespace andrick
{
	class DirectoryLocation : public PathLocation
	{
	public:

		DirectoryLocation(const DirectoryLocation& parentDir, std::string name);
		DirectoryLocation(std::string parentPath, std::string name, const EnumPathType& pathType);
		inline virtual ~DirectoryLocation() {};

		std::string getPath() const override;

	private:
		//Hold a list of child directories in the future.
	};
}

#endif