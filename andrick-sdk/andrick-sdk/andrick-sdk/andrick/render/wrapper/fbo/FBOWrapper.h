#ifndef ANDRICK_FBO_WRAPPER_H_
#define ANDRICK_FBO_WRAPPER_H_

#include "../GLObjectWrapper.h"

namespace andrick
{
	class FBOWrapper : public GLObjectWrapper
	{
	public:
		enum class EnumFBOBindType : GLint
		{
			FRAMEBUFFER = GL_FRAMEBUFFER,
			READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
			DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER
		};

		FBOWrapper();
		~FBOWrapper();

		virtual void bind();
		virtual void unbind();

		void attachRBO();

	private:
		virtual void createID();
	};
}

#endif
