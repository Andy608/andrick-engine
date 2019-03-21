#ifndef ANDRICK_FILE_LOCATION_H_
#define ANDRICK_FILE_LOCATION_H_

#include <vector>
#include "../PathLocation.h"

namespace andrick
{
	class DirectoryLocation;

	class FileLocation : public PathLocation
	{
	public:
		enum EnumExtensionType : GLuint
		{
			TXT_EXT,
			PNG_EXT,
			OBJ_EXT,
			VS_EXT,
			FS_EXT
		};

		FileLocation(const DirectoryLocation& parentDirectory, std::string name, const EnumExtensionType& extensionType = FileLocation::EnumExtensionType::TXT_EXT);
		FileLocation(std::string parentPath, std::string name, const EnumPathType& pathType, const EnumExtensionType& extensionType = FileLocation::EnumExtensionType::TXT_EXT);
		inline virtual ~FileLocation() {};

		std::string getPath() const override;
		std::string getPathNoExt() const;

		inline std::string getExtAsString() const { return mEXTENSION; };

		inline std::string getNameAndExt() const { return mNAME + mEXTENSION; };

		//Returns the extension type
		inline EnumExtensionType getExt() const { return mEXT_TYPE; };

	private:
		static const GLuint EXT_TYPES_LENGTH;
		static std::string EXT_TYPES[];

		EnumExtensionType mEXT_TYPE;
		const std::string mEXTENSION;

		static std::string getExt(EnumExtensionType ext);
	};
}

#endif