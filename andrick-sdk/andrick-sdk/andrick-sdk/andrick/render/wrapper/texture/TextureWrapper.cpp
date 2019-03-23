#include "TextureWrapper.h"

namespace andrick
{
	TextureWrapper::TextureWrapper(Texture &texture) :
		mTexture(texture)
	{
		createID();
	}

	TextureWrapper::~TextureWrapper()
	{
		glDeleteTextures(1, &mID);
	}

	void TextureWrapper::bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mID);
	}

	void TextureWrapper::unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureWrapper::setTexture(Texture& texture)
	{
		mTexture = texture;
	}

	void TextureWrapper::setWrapStyleS(const EnumWrapStyle& wrapStyleS)
	{
		mWrapStyleS = wrapStyleS;
	}

	void TextureWrapper::setWrapStyleT(const EnumWrapStyle& wrapStyleT)
	{
		mWrapStyleT = wrapStyleT;
	}

	void TextureWrapper::setMinifyFilter(const EnumMinFilter& minifyFilter)
	{
		mMinifyFilter = minifyFilter;
	}

	void TextureWrapper::setMagnifyFilter(const EnumMagFilter& magnifyFilter)
	{
		mMagnifyFilter = magnifyFilter;
	}

	void TextureWrapper::generateGLTexture()
	{
		bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(mWrapStyleS));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(mWrapStyleT));

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(mMinifyFilter));
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(mMagnifyFilter));

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTexture.getWidth(), mTexture.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, mTexture.mPixelData);
		glGenerateMipmap(GL_TEXTURE_2D);
		unbind();
	}

	const Texture& TextureWrapper::getCurrentTexture() const
	{
		return mTexture;
	}

	void TextureWrapper::createID()
	{
		glGenTextures(1, &mID);
	}
}