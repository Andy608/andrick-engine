#include "TextureWrapper.h"

namespace andrick
{
	//Create a texture using the data from the image asset.
	TextureWrapper::TextureWrapper(Image& image,
		const EnumWrapStyle& wrapStyleS,
		const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify,
		const EnumMagFilter& magnify) :
		TextureWrapper(image.getWidth(), image.getHeight(), image.getData(), 
			EnumInternalFormatType::RGBA,//TODO: Get the correct data from image
			EnumDataFormat::RGBA_FORMAT,//TODO: Get the correct data from image
			EnumDataType::UNSIGNED_BYTE,//TODO: Get the correct data from image
			wrapStyleS, wrapStyleT, minify, magnify)
	{

	}

	TextureWrapper::TextureWrapper(const glm::ivec2& size, GLubyte* pPixelData,
		const EnumInternalFormatType& colorComponents, const EnumDataFormat& dataFormat, const EnumDataType& dataType,
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify) : 
		TextureWrapper(size.x, size.y, 
			pPixelData, colorComponents, dataFormat, dataType, 
			wrapStyleS, wrapStyleT, minify, magnify)
	{

	}

	TextureWrapper::TextureWrapper(const GLuint& width, const GLuint& height, GLubyte* pPixelData,
		const EnumInternalFormatType& colorComponents, const EnumDataFormat& dataFormat, const EnumDataType& dataType,
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify) :
		mTextureWidth(width),
		mTextureHeight(height),
		mColorComponents(colorComponents),
		mpPixelData(pPixelData),
		mDataFormat(dataFormat),
		mDataType(dataType),
		mTextureUnit(0)
	{
		setWrapStyleS(wrapStyleS);
		setWrapStyleT(wrapStyleT);
		setMinifyFilter(minify);
		setMagnifyFilter(magnify);
		createID();
	}

	void TextureWrapper::setProperties(const GLuint& width, const GLuint& height, GLubyte* pPixelData,
		const EnumInternalFormatType& colorComponents,
		const EnumDataFormat& dataFormat,
		const EnumDataType& dataType,
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify)
	{
		mTextureWidth = width;
		mTextureHeight = height;
		mpPixelData = pPixelData;
		
		mColorComponents = colorComponents;
		mDataFormat = dataFormat;
		mDataType = dataType;

		setWrapStyleS(wrapStyleS);
		setWrapStyleT(wrapStyleT);
		setMinifyFilter(minify);
		setMagnifyFilter(magnify);
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
	}

	void TextureWrapper::bind(const GLubyte& textureUnit)
	{
		mTextureUnit = textureUnit;

		glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_2D, mID);
	}

	void TextureWrapper::unbind()
	{
		glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		glBindTexture(GL_TEXTURE_2D, 0);
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
		generateGLTexture(mTextureUnit);
	}

	void TextureWrapper::generateGLTexture(const GLint& textureUnit)
	{
		mTextureUnit = textureUnit;

		bind(mTextureUnit);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, mWrapStyleS);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, mWrapStyleT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mMinifyFilter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mMagnifyFilter);

		//Create a texture with the pixel data. If pixel data is null, create empty texture.
		glTexImage2D(GL_TEXTURE_2D, 0, mColorComponents, mTextureWidth, mTextureHeight, 0, mDataFormat, mDataType, mpPixelData);

		//No need to generate mipmap if empty texture.
		if (mpPixelData)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		unbind();
	}

	void TextureWrapper::createID()
	{
		glGenTextures(1, &mID);
	}
}