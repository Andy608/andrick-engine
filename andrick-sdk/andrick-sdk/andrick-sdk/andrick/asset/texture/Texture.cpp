#include "Texture.h"
#include "../../logger/LoggerMaster.h"
#include <stb_image/stb_image.h>

namespace andrick
{
	const std::string Texture::msCLASS_NAME = "Texture";

	Texture::Texture(std::string assetID, FileLocation imageFileLocation) :
		Asset(assetID),
		mImageFileLocation(imageFileLocation)
	{

	}

	Texture::~Texture()
	{
		if (mIsLoaded)
		{
			unload();
		}
	}

	GLboolean Texture::load()
	{
		mPixelData = stbi_load(mImageFileLocation.getPath().c_str(), &mWidth, &mHeight, &mColorChannels, STBI_rgb_alpha);

		if (mPixelData != nullptr)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Successfully loaded texture: " + mImageFileLocation.getPath());
			mIsLoaded = GL_TRUE;
		}
		else
		{
			LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Failed to load texture: " + mImageFileLocation.getPath());
			mIsLoaded = GL_FALSE;
		}

		return mIsLoaded;
	}

	GLboolean Texture::unload()
	{
		if (mIsLoaded)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Unloading texture: " + mImageFileLocation.getPath());
			stbi_image_free(mPixelData);
			mIsLoaded = GL_FALSE;
		}

		return (mIsLoaded == GL_FALSE);
	}
}