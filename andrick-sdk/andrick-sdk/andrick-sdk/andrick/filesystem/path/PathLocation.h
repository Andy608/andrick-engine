#ifndef ANDRICK_PATH_LOCATION_H_
#define ANDRICK_PATH_LOCATION_H_

#include <glad/glad.h>
#include <string>
#include "../../memory/TrackableObject.h"

namespace andrick
{
	class PathLocation : public TrackableObject
	{
	public:
		enum EnumPathType : GLuint
		{
			ABSOLUTE_PATH,
			RELATIVE_PATH
		};

		//Returns the whole path as a usable string.
		virtual std::string getPath() const = 0;

		//In the future, maybe return a PathLocation if it's necessary.
		inline const std::string& getParentPath() const { return mPARENT_PATH; };

		//Returns the name of the file or folder
		inline std::string getName() const { return mNAME; };

		//Is the path relative or absolute?
		inline EnumPathType getPathType() const { return mPATH_TYPE; };


	protected:
		const std::string mPARENT_PATH;
		const std::string mNAME;
		const EnumPathType mPATH_TYPE;

		inline PathLocation(std::string parentPath, std::string name, const EnumPathType& pathType/*, const EnumExtensionType& extensionType*/) :
			mPARENT_PATH(parentPath),
			mNAME(name),
			mPATH_TYPE(pathType)
		{

		}
		
		inline virtual ~PathLocation() {};
	};
}

#endif