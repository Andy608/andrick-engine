#include "CubeMap.h"

namespace andrick
{
	CubeMap::CubeMap()
	{
		createID();
	}

	void CubeMap::cleanup()
	{
		glDeleteTextures(1, &mID);
	}

	void CubeMap::bind()
	{
		bind(0);
	}

	void CubeMap::bind(const GLubyte& textureUnit)
	{
		mTextureUnit = textureUnit;

		glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_CUBE_MAP, mID);
	}

	void CubeMap::unbind()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void CubeMap::addTextures(const std::array<Image*, 6>& images)
	{
		GLint i;
		for (i = 0; i < mCubeTextures.size(); ++i)
		{
			mCubeTextures[i] = images[i];
		}
	}

	void CubeMap::setTexture(const EnumCubeMapOrientation& orientation, const Image* image)
	{
		//The array will always be the same size as the enum.
		mCubeTextures[orientation] = image;
	}

	void CubeMap::generateGLCubeMap()
	{
		bind(mTextureUnit);

		auto iter = mCubeTextures.begin();
		GLuint i;
		for (i = 0; iter != mCubeTextures.end(); ++iter, ++i)
		{
			glTexImage2D(EnumCubeMapOrientation::TEXTURE_RIGHT + i, 0,
				GL_RGB, (*iter)->getWidth(), (*iter)->getHeight(), 0,
				GL_RGB, GL_UNSIGNED_BYTE, (*iter)->getPixelData());
		}

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		unbind();
	}

	void CubeMap::generateGLCubeMap(const GLint& textureUnit)
	{

	}

	void CubeMap::createID()
	{
		glGenTextures(1, &mID);
	}
}