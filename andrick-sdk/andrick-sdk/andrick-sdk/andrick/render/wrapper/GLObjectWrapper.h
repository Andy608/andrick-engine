#ifndef ANDRICK_GL_OBJECT_WRAPPER_H_
#define ANDRICK_GL_OBJECT_WRAPPER_H_

#include <glad/glad.h>
#include <vector>
#include "../../memory/TrackableObject.h"
#include "../../memory/NonCopyable.h"

namespace andrick
{
	class GLObjectWrapper : public TrackableObject, NonCopyable//Might not be able to do noncopyable, but we'll see.
	{
	public:
		static const GLuint msDEFAULT_SAMPLE_SIZE = 1;

		inline GLObjectWrapper() {};
		inline virtual ~GLObjectWrapper() {};

		virtual void cleanup() = 0;

		virtual void bind() = 0;
		virtual void unbind() = 0;

		inline const GLuint& getID() const { return mID; };

	protected:
		GLuint mID;

		virtual void createID() = 0;
	};

	enum EnumAttachmentType : GLint
	{
		DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT,
		STENCIL_ATTACHMENT = GL_STENCIL_ATTACHMENT,
		DEPTH_STENCIL_ATTACHMENT = GL_DEPTH_STENCIL_ATTACHMENT,

		COLOR_ATTACHMENT0 = GL_COLOR_ATTACHMENT0,
		COLOR_ATTACHMENT1 = GL_COLOR_ATTACHMENT1,
		COLOR_ATTACHMENT2 = GL_COLOR_ATTACHMENT2,
		COLOR_ATTACHMENT3 = GL_COLOR_ATTACHMENT3,
		COLOR_ATTACHMENT4 = GL_COLOR_ATTACHMENT4,
		COLOR_ATTACHMENT5 = GL_COLOR_ATTACHMENT5,
		COLOR_ATTACHMENT6 = GL_COLOR_ATTACHMENT6,
		COLOR_ATTACHMENT7 = GL_COLOR_ATTACHMENT7,
		COLOR_ATTACHMENT8 = GL_COLOR_ATTACHMENT8,
		COLOR_ATTACHMENT9 = GL_COLOR_ATTACHMENT9,
		COLOR_ATTACHMENT10 = GL_COLOR_ATTACHMENT10
	};

	enum EnumTextureType : GLint
	{
		TEXTURE_2D = GL_TEXTURE_2D,
		TEXTURE_2D_MULTISAMPLE = GL_TEXTURE_2D_MULTISAMPLE
	};

	enum EnumInternalFormatType : GLint
	{
		RGB = GL_RGB,
		RGBA = GL_RGBA,
		RGB16F = GL_RGB16F,

		DEPTH_COMPONENT = GL_DEPTH_COMPONENT,
		DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
		DEPTH32F_STENCIL8 = GL_DEPTH32F_STENCIL8,
	};

	enum EnumDataFormat : GLint
	{
		RGB_FORMAT = GL_RGB,
		RGBA_FORMAT = GL_RGBA,
		RGB16F_FORMAT = GL_RGB16F,

		DEPTH_STENCIL_FORMAT = GL_DEPTH_STENCIL,
	};

	enum EnumDataType : GLint
	{
		FLOAT = GL_FLOAT,
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE,
		UNSIGNED_INT_24_8 = GL_UNSIGNED_INT_24_8
	};
}

#endif