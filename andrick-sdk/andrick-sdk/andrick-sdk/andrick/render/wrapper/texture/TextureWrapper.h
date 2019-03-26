#ifndef ANDRICK_TEXTURE_WRAPPER_H_
#define ANDRICK_TEXTURE_WRAPPER_H_

#include "../GLObjectWrapper.h"
#include <glm/vec2.hpp>

#include "../../../asset/image/Image.h"

namespace andrick
{
	class TextureWrapper : public GLObjectWrapper
	{
	public:
		enum EnumWrapStyle : GLint
		{
			REPEAT = GL_REPEAT,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};

		enum EnumMinFilter : GLint
		{
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
		};

		enum EnumMagFilter : GLint
		{
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR
		};

		//Create a texture using the data from the image asset.
		TextureWrapper(Image& image,
			const EnumWrapStyle& wrapStyleS = EnumWrapStyle::REPEAT,
			const EnumWrapStyle& wrapStyleT = EnumWrapStyle::REPEAT,
			const EnumMinFilter& minify = EnumMinFilter::LINEAR_MIPMAP_LINEAR,
			const EnumMagFilter& magnify = EnumMagFilter::LINEAR);

		//Create a texture using the data from the image asset.
		TextureWrapper(const GLuint& width, const GLuint& height, GLubyte* pPixelData, 
			const EnumInternalFormatType& colorComponents = EnumInternalFormatType::RGBA,
			const EnumDataFormat& dataFormat = EnumDataFormat::RGBA_FORMAT,
			const EnumDataType& dataType = EnumDataType::UNSIGNED_BYTE,
			const EnumWrapStyle& wrapStyleS = EnumWrapStyle::REPEAT,
			const EnumWrapStyle& wrapStyleT = EnumWrapStyle::REPEAT,
			const EnumMinFilter& minify = EnumMinFilter::LINEAR_MIPMAP_LINEAR,
			const EnumMagFilter& magnify = EnumMagFilter::LINEAR);

		//Create a texture using the data from the image asset.
		TextureWrapper(const glm::ivec2& size, GLubyte* pPixelData,
			const EnumInternalFormatType& colorComponents = EnumInternalFormatType::RGBA,
			const EnumDataFormat& dataFormat = EnumDataFormat::RGBA_FORMAT,
			const EnumDataType& dataType = EnumDataType::UNSIGNED_BYTE,
			const EnumWrapStyle& wrapStyleS = EnumWrapStyle::REPEAT, 
			const EnumWrapStyle& wrapStyleT = EnumWrapStyle::REPEAT,
			const EnumMinFilter& minify = EnumMinFilter::LINEAR_MIPMAP_LINEAR,
			const EnumMagFilter& magnify = EnumMagFilter::LINEAR);

		void setProperties(const GLuint& width, const GLuint& height, GLubyte* pPixelData,
			const EnumInternalFormatType& colorComponents = EnumInternalFormatType::RGBA,
			const EnumDataFormat& dataFormat = EnumDataFormat::RGBA_FORMAT,
			const EnumDataType& dataType = EnumDataType::UNSIGNED_BYTE,
			const EnumWrapStyle& wrapStyleS = EnumWrapStyle::REPEAT,
			const EnumWrapStyle& wrapStyleT = EnumWrapStyle::REPEAT,
			const EnumMinFilter& minify = EnumMinFilter::LINEAR_MIPMAP_LINEAR,
			const EnumMagFilter& magnify = EnumMagFilter::LINEAR);

		~TextureWrapper();

		virtual void bind();
		virtual void bind(const GLubyte& textureUnit);
		virtual void unbind();

		void setWrapStyleS(const EnumWrapStyle& wrapStyleS);
		void setWrapStyleT(const EnumWrapStyle& wrapStyleT);

		void setMinifyFilter(const EnumMinFilter& minifyFilter);
		void setMagnifyFilter(const EnumMagFilter& magnifyFilter);

		void generateGLTexture();
		void generateGLTexture(const GLint& textureUnit);

		const GLuint& getTextureUnit() const { return mTextureUnit; };

		inline const GLuint getWidth() const { return mTextureWidth; };
		inline const GLuint getHeight() const { return mTextureHeight; };

		inline const EnumWrapStyle& getWrapStyleS() const { return mWrapStyleS; };
		inline const EnumWrapStyle& getWrapStyleT() const { return mWrapStyleT; };

		inline const EnumMinFilter& getMinFilter() const { return mMinifyFilter; };
		inline const EnumMagFilter& getMagFilter() const { return mMagnifyFilter; };

		inline const EnumInternalFormatType& getComponentType() const { return mColorComponents; };
		inline const EnumDataFormat& getDataFormat() const { return mDataFormat; };
		inline const EnumDataType& getDataType() const { return mDataType; };

	private:
		GLuint mTextureWidth;
		GLuint mTextureHeight;
		GLuint mTextureUnit;
		GLubyte* mpPixelData;

		//Specifies the number of color components in the texture.
		EnumInternalFormatType mColorComponents;

		//Specifies the format of the pixel data.
		EnumDataFormat mDataFormat;
		
		//Specifies the data type of the pixel data.
		EnumDataType mDataType;

		EnumWrapStyle mWrapStyleS;
		EnumWrapStyle mWrapStyleT;

		EnumMinFilter mMinifyFilter;
		EnumMagFilter mMagnifyFilter;

		virtual void createID();
	};
}

#endif