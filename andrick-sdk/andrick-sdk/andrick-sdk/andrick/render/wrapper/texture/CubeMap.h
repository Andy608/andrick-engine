#ifndef ANDRICK_CUBE_MAP_H_
#define ANDRICK_CUBE_MAP_H_

#include "../../../asset/image/Image.h"
#include "../GLObjectWrapper.h"
#include <array>

namespace andrick
{
	class CubeMap : public GLObjectWrapper
	{
	public:
		enum EnumCubeMapOrientation
		{
			TEXTURE_RIGHT = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
			TEXTURE_LEFT = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
			TEXTURE_TOP = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
			TEXTURE_BOTTOM = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
			TEXTURE_BACK = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
			TEXTURE_FRONT = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
		};

		CubeMap();
		inline virtual ~CubeMap() { cleanup(); };

		virtual void cleanup();
		
		virtual void bind();
		virtual void bind(const GLubyte& textureUnit);
		virtual void unbind();

		void addTextures(const std::array<Image*, 6>& images);
		void setTexture(const EnumCubeMapOrientation& orientation, const Image* image);

		void generateGLCubeMap();
		void generateGLCubeMap(const GLint& textureUnit);

		const GLuint& getTextureUnit() const { return mTextureUnit; };

	private:
		GLuint mTextureUnit;
		std::array<const Image*, 6> mCubeTextures;

		virtual void createID();
	};
}

#endif