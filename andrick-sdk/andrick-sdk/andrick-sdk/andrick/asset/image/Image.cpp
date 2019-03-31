#include "Image.h"
#include "../../logger/LoggerMaster.h"
#include <stb_image/stb_image.h>

namespace andrick
{
	const std::string Image::msCLASS_NAME = "Image";

	Image::Image(std::string assetID, FileLocation imageFileLocation, const EnumInternalFormatType& formatType) :
		Asset(assetID),
		mImageFileLocation(imageFileLocation),
		mInternalFormat(formatType)
	{

	}

	Image::~Image()
	{
		if (mIsLoaded)
		{
			unload();
		}
	}

	GLboolean Image::load()
	{
		if (!mIsLoaded)
		{

			mpPixelData = stbi_load(mImageFileLocation.getPath().c_str(), &mWidth, &mHeight, &mColorChannels, convertFormatToSTBIType(mInternalFormat));

			if (mpPixelData != nullptr)
			{
				LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Successfully loaded texture: " + mImageFileLocation.getPath());
				mIsLoaded = GL_TRUE;
			}
			else
			{
				LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Failed to load texture: " + mImageFileLocation.getPath());
				mIsLoaded = GL_FALSE;
			}
		}

		return mIsLoaded;
	}

	GLboolean Image::unload()
	{
		if (mIsLoaded)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Unloading texture: " + mImageFileLocation.getPath());
			stbi_image_free(mpPixelData);
			mIsLoaded = GL_FALSE;
		}

		return (mIsLoaded == GL_FALSE);
	}

	const GLint Image::convertFormatToSTBIType(const EnumInternalFormatType& formatType)
	{
		GLint value;

		switch (formatType)
		{
		case EnumInternalFormatType::RGB:
			value = STBI_rgb;
			break;
		default:
			value = STBI_rgb_alpha;
			break;
		}

		return value;
	}
}