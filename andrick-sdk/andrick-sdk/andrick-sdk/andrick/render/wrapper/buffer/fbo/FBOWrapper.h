#ifndef ANDRICK_FBO_WRAPPER_H_
#define ANDRICK_FBO_WRAPPER_H_

#include "../../GLObjectWrapper.h"
#include "../rbo/RBOWrapper.h"
#include "../../texture/TextureWrapper.h"

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
		inline virtual ~FBOWrapper() { cleanup(); };

		virtual void cleanup();

		virtual void bind();
		virtual void unbind();

		void resizeBuffers(const GLint& width, const GLint& height);

		void attachTexture(TextureWrapper& texture, const EnumBindType& bindType = EnumBindType::FRAMEBUFFER, const EnumAttachmentType& attachmentType = EnumAttachmentType::COLOR_ATTACHMENT0);
		void attachRBO(RBOWrapper& rboWrapper, const EnumAttachmentType& attachmentType = EnumAttachmentType::DEPTH_STENCIL_ATTACHMENT);

	private:
		static const std::string msCLASS_NAME;
		virtual void createID();

		struct BoundTextureData
		{
			BoundTextureData() {};
			BoundTextureData(TextureWrapper* tex, const EnumBindType& bind, const EnumAttachmentType& attach) :
				texture(tex), bindType(bind), attachmentType(attach) {};
			TextureWrapper* texture = nullptr;
			EnumBindType bindType;
			EnumAttachmentType attachmentType;
		};
		
		struct BoundRBOData
		{
			BoundRBOData() {};
			BoundRBOData(RBOWrapper* r, const EnumAttachmentType& attach) :
				rbo(r), attachmentType(attach) {};

			RBOWrapper* rbo = nullptr;
			EnumAttachmentType attachmentType;
		};

		std::vector<BoundTextureData> mAttachedTextures;
		std::vector<BoundRBOData> mAttachedRBOs;
	};
}

#endif
