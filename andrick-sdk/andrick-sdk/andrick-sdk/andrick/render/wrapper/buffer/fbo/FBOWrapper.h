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

		//IN THE MIDDLE OF IMPLEMENTING POST-PROCESSING. STILL NEED TO TEST RENDERING TO MULTIPLE FBOs
		virtual void bind();
		void bind(EnumBindType bindType);
		virtual void unbind();

		static void renderFBOToFBO(const FBOWrapper* readFBO, const FBOWrapper* writeFBO, 
			const glm::ivec2& readSize, const glm::ivec2& writeSize,
			const GLuint& readStartX = 0, const GLuint& readStartY = 0,
			const GLuint& writeStartX = 0, const GLuint& writeStartY = 0);

		void resizeBuffers(const GLint& width, const GLint& height);

		void attachTexture(TextureWrapper& texture, 
			const EnumBindType& bindType = EnumBindType::FRAMEBUFFER, 
			const EnumAttachmentType& attachmentType = EnumAttachmentType::COLOR_ATTACHMENT0,
			const EnumTextureType& textureType = EnumTextureType::TEXTURE_2D);

		void attachRBO(RBOWrapper& rboWrapper, 
			const EnumAttachmentType& attachmentType = EnumAttachmentType::DEPTH_STENCIL_ATTACHMENT);

	private:
		static const std::string msCLASS_NAME;
		virtual void createID();

		struct BoundTextureData
		{
			BoundTextureData() {};
			BoundTextureData(TextureWrapper* tex, const EnumBindType& bind, const EnumAttachmentType& attach, const EnumTextureType texture) :
				texture(tex), bindType(bind), attachmentType(attach), textureType(texture) {};
			TextureWrapper* texture = nullptr;
			EnumBindType bindType;
			EnumAttachmentType attachmentType;
			EnumTextureType textureType;
		};
		
		struct BoundRBOData
		{
			BoundRBOData() {};
			BoundRBOData(RBOWrapper* r, const EnumAttachmentType& attach) :
				rbo(r), attachmentType(attach) {};

			RBOWrapper* rbo = nullptr;
			EnumAttachmentType attachmentType;
		};

		EnumBindType mCurrentBindType;

		std::vector<BoundTextureData> mAttachedTextures;
		std::vector<BoundRBOData> mAttachedRBOs;
	};
}

#endif
