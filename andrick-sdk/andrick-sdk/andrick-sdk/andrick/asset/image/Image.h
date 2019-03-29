#ifndef ANDRICK_IMAGE_H_
#define ANDRICK_IMAGE_H_

#include "../../asset/Asset.h"
#include "../../filesystem/path/file/FileLocation.h"

namespace andrick
{
	class Image : public Asset
	{
	public:
		Image(std::string assetID, FileLocation imageFileLocation);
		virtual ~Image();

		inline const Image& operator=(const Image& another) { return another; };

		virtual GLboolean load() override;
		virtual GLboolean unload() override;

		inline const GLuint getWidth() const { return mWidth; };
		inline const GLuint getHeight() const { return mHeight; };
		inline GLubyte* getData() const { return mpPixelData; };

	private:
		static const std::string msCLASS_NAME;

		FileLocation mImageFileLocation;

		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte* mpPixelData;
	};
}

#endif