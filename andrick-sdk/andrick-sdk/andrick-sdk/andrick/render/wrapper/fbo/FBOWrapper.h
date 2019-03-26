#ifndef ANDRICK_FBO_WRAPPER_H_
#define ANDRICK_FBO_WRAPPER_H_

#include "../GLObjectWrapper.h"
#include "../rbo/RBOWrapper.h"
#include "../texture/TextureWrapper.h"

namespace andrick
{
	class FBOWrapper : public GLObjectWrapper
	{
	public:
		enum EnumBindType : GLint
		{
			FRAMEBUFFER = GL_FRAMEBUFFER,
			READ_FRAMEBUFFER = GL_READ_FRAMEBUFFER,
			DRAW_FRAMEBUFFER = GL_DRAW_FRAMEBUFFER
		};

		FBOWrapper();
		~FBOWrapper();

		virtual void bind();
		virtual void unbind();

		void attachTexture(TextureWrapper& texture, const EnumBindType& bindType = EnumBindType::FRAMEBUFFER, const EnumAttachmentType& attachmentType = EnumAttachmentType::COLOR_ATTACHMENT0);
		void attachRBO(const RBOWrapper& rboWrapper, const EnumAttachmentType& attachmentType = EnumAttachmentType::DEPTH_STENCIL_ATTACHMENT);

	private:
		static const std::string msCLASS_NAME;
		virtual void createID();
	};
}

#endif
