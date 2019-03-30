#include "TextureWrapper.h"

namespace andrick
{
	//Create a texture using the data from the image asset.
	TextureWrapper::TextureWrapper(Image& image,
		const EnumWrapStyle& wrapStyleS,
		const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify,
		const EnumMagFilter& magnify,
		const GLboolean& generateMipmap) :
		TextureWrapper(image.getWidth(), image.getHeight(), image.getData(),
			EnumTextureType::TEXTURE_2D, generateMipmap,
			EnumInternalFormatType::RGBA,//TODO: Get the correct data from image
			EnumDataFormat::RGBA_FORMAT,//TODO: Get the correct data from image
			EnumDataType::UNSIGNED_BYTE,//TODO: Get the correct data from image
			wrapStyleS, wrapStyleT, minify, magnify)
	{

	}

	TextureWrapper::TextureWrapper(const glm::ivec2& size, GLubyte* pPixelData,
		const EnumTextureType& textureType,
		const GLboolean& generateMipmap,
		const EnumInternalFormatType& colorComponents, const EnumDataFormat& dataFormat, const EnumDataType& dataType,
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify) :
		TextureWrapper(size.x, size.y, pPixelData, textureType, generateMipmap,
			colorComponents, dataFormat, dataType, wrapStyleS, 
			wrapStyleT, minify, magnify)
	{

	}

	TextureWrapper::TextureWrapper(const GLuint& width, const GLuint& height, GLubyte* pPixelData,
		const EnumTextureType& textureType,
		const GLboolean& generateMipmap,
		const EnumInternalFormatType& colorComponents, const EnumDataFormat& dataFormat, const EnumDataType& dataType,
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify) :
		mTextureWidth(width),
		mTextureHeight(height),
		mTextureType(textureType),
		mGenerateMipmap(generateMipmap),
		mColorComponents(colorComponents),
		mpPixelData(pPixelData),
		mDataFormat(dataFormat),
		mDataType(dataType),
		mTextureUnit(0)
	{
		setSampleSize(GLObjectWrapper::msDEFAULT_SAMPLE_SIZE);
		setWrapStyleS(wrapStyleS);
		setWrapStyleT(wrapStyleT);
		setMinifyFilter(minify);
		setMagnifyFilter(magnify);
		createID();
	}

	void TextureWrapper::setProperties(const GLuint& width, const GLuint& height, GLubyte* pPixelData,
		const EnumTextureType& textureType,
		const GLboolean& generateMipmap,
		const EnumInternalFormatType& colorComponents,
		const EnumDataFormat& dataFormat,
		const EnumDataType& dataType,
		const EnumWrapStyle& wrapStyleS, const EnumWrapStyle& wrapStyleT,
		const EnumMinFilter& minify, const EnumMagFilter& magnify)
	{
		mTextureWidth = width;
		mTextureHeight = height;
		mpPixelData = pPixelData;
		mTextureType = textureType;
		mGenerateMipmap = generateMipmap;
		
		mColorComponents = colorComponents;
		mDataFormat = dataFormat;
		mDataType = dataType;

		setSampleSize(GLObjectWrapper::msDEFAULT_SAMPLE_SIZE);
		setWrapStyleS(wrapStyleS);
		setWrapStyleT(wrapStyleT);
		setMinifyFilter(minify);
		setMagnifyFilter(magnify);
	}

	void TextureWrapper::cleanup()
	{
		glDeleteTextures(1, &mID);
	}

	void TextureWrapper::bind()
	{
		mTextureUnit = 0;
		bind(mTextureUnit);
	}

	void TextureWrapper::bind(const GLubyte& textureUnit)
	{
		mTextureUnit = textureUnit;

		//if (mpPixelData)
		//{
			glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		//}

		glBindTexture(mTextureType, mID);
	}

	void TextureWrapper::unbind()
	{
		//if (mpPixelData)
		//{
			glActiveTexture(GL_TEXTURE0 + mTextureUnit);
		//}

		glBindTexture(mTextureType, 0);
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

	void TextureWrapper::resizeBuffer(const GLuint& width, const GLuint& height)
	{
		setProperties(width, height, mpPixelData, mTextureType, mGenerateMipmap, mColorComponents, mDataFormat, mDataType, mWrapStyleS, mWrapStyleT, mMinifyFilter, mMagnifyFilter);
		generateGLTexture();
	}

	void TextureWrapper::generateGLTexture(const GLint& textureUnit)
	{
		mTextureUnit = textureUnit;

		bind(mTextureUnit);
		glTexParameteri(mTextureType, GL_TEXTURE_WRAP_S, mWrapStyleS);
		glTexParameteri(mTextureType, GL_TEXTURE_WRAP_T, mWrapStyleT);

		glTexParameteri(mTextureType, GL_TEXTURE_MIN_FILTER, mMinifyFilter);
		glTexParameteri(mTextureType, GL_TEXTURE_MAG_FILTER, mMagnifyFilter);

		//Create a texture with the pixel data. If pixel data is null, create empty texture.
		if (mTextureType == EnumTextureType::TEXTURE_2D_MULTISAMPLE)
		{
			glTexImage2DMultisample(mTextureType, mSampleSize, mColorComponents, mTextureWidth, mTextureHeight, GL_TRUE);
		}
		else
		{
			glTexImage2D(mTextureType, 0, mColorComponents, mTextureWidth, mTextureHeight, 0, mDataFormat, mDataType, mpPixelData);
		}

		//No need to generate mipmap if empty texture.
		if (mpPixelData && mGenerateMipmap)
		{
			glGenerateMipmap(mTextureType);
		}

		unbind();
	}

	void TextureWrapper::createID()
	{
		glGenTextures(1, &mID);
	}
}