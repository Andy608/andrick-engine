#ifndef ANDRICK_TEXTURE_WRAPPER_H_
#define ANDRICK_TEXTURE_WRAPPER_H_

#include "../GLObjectWrapper.h"
#include "../../../asset/texture/Texture.h"

namespace andrick
{
	class TextureWrapper : public GLObjectWrapper
	{
	public:
		enum class EnumWrapStyle : GLint
		{
			REPEAT = GL_REPEAT,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};

		enum class EnumMinFilter : GLint
		{
			NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
			LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,
			NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
			LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR
		};

		enum class EnumMagFilter : GLint
		{
			NEAREST = GL_NEAREST,
			LINEAR = GL_LINEAR
		};

		TextureWrapper(Texture& texture);
		~TextureWrapper();

		virtual void bind() const;
		virtual void unbind() const;

		void setTexture(Texture &texture);

		void setWrapStyleS(const EnumWrapStyle& wrapStyleS);
		void setWrapStyleT(const EnumWrapStyle& wrapStyleT);

		void setMinifyFilter(const EnumMinFilter& minifyFilter);
		void setMagnifyFilter(const EnumMagFilter& magnifyFilter);

		void generateGLTexture();

		const Texture& getCurrentTexture() const;

		inline const EnumWrapStyle& getWrapStyleS() const { return mWrapStyleS; };
		inline const EnumWrapStyle& getWrapStyleT() const { return mWrapStyleT; };

		inline const EnumMinFilter& getMinFilter() const { return mMinifyFilter; };
		inline const EnumMagFilter& getMagFilter() const { return mMagnifyFilter; };

	private:
		Texture& mTexture;

		EnumWrapStyle mWrapStyleS;
		EnumWrapStyle mWrapStyleT;

		EnumMinFilter mMinifyFilter;
		EnumMagFilter mMagnifyFilter;

		virtual void createID();
	};
}

#endif