#include "TextureWrapper.h"

namespace andrick
{
	TextureWrapper::TextureWrapper(Texture &texture, 
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify) :
		mTexture(texture),
		mTextureUnit(0)
	{
		setWrapStyleS(wrapStyleS);
		setWrapStyleT(wrapStyleT);
		setMinifyFilter(minify);
		setMagnifyFilter(magnify);
		createID();
	}

	TextureWrapper::~TextureWrapper()
	{
		glDeleteTextures(1, &mID);
	}

	void TextureWrapper::bind()
	{
		mTextureUnit = 0;
		glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_2D, mID);
		//glActiveTexture(0);
	}

	void TextureWrapper::bind(const GLubyte& textureUnit)
	{
		mTextureUnit = textureUnit;

		glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_2D, mID);
		//glActiveTexture(0);
	}

	void TextureWrapper::unbind()
	{
		glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void TextureWrapper::updateProperties(Texture& texture,
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify)
	{
		setTexture(texture);
		setWrapStyleS(wrapStyleS);
		setWrapStyleT(wrapStyleT);
		setMinifyFilter(minify);
		setMagnifyFilter(magnify);
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
		bind(mTextureUnit);
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