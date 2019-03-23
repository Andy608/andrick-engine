#ifndef ANDRICK_TEXTURE_H_
#define ANDRICK_TEXTURE_H_

#include "../../asset/Asset.h"
#include "../../filesystem/path/file/FileLocation.h"

namespace andrick
{
	class Texture : public Asset
	{
		friend class TextureWrapper;

	public:
		Texture(std::string assetID, FileLocation imageFileLocation);
		virtual ~Texture();

		inline const Texture& operator=(const Texture& another) { return another; };

		virtual GLboolean load() override;
		virtual GLboolean unload() override;

		inline const GLuint getWidth() const { return mWidth; };
		inline const GLuint getHeight() const { return mHeight; };

	private:
		static const std::string msCLASS_NAME;

		FileLocation mImageFileLocation;
		GLint mWidth;
		GLint mHeight;
		GLint mColorChannels;
		GLubyte *mPixelData;
	};
}

#endif