#ifndef ANDRICK_IMAGE_H_
#define ANDRICK_IMAGE_H_

#include "../../asset/Asset.h"
#include "../../filesystem/path/file/FileLocation.h"
#include "../../render/wrapper/GLObjectWrapper.h"

namespace andrick
{
	class Image : public Asset
	{
	public:
		Image(std::string assetID, FileLocation imageFileLocation, const EnumInternalFormatType& formatType = EnumInternalFormatType::RGBA);
		virtual ~Image();

		inline const Image& operator=(const Image& another) { return another; };

		virtual GLboolean load() override;
		virtual GLboolean unload() override;

		inline const GLuint getWidth() const { return mWidth; };
		inline const GLuint getHeight() const { return mHeight; };
		inline GLubyte* getPixelData() const { return mpPixelData; };

		static const GLint convertFormatToSTBIType(const EnumInternalFormatType& formatType);

	private:
		static const std::string msCLASS_NAME;

		FileLocation mImageFileLocation;
		EnumInternalFormatType mInternalFormat;

		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte* mpPixelData;
	};
}

#endif