#ifndef ANDRICK_RBO_WRAPPER_H_
#define ANDRICK_RBO_WRAPPER_H_

#include "../GLObjectWrapper.h"
#include "../../../window/AndrickWindow.h"

namespace andrick
{
	class RBOWrapper : public GLObjectWrapper
	{
	public:
		enum EnumRBOStorageType : GLint
		{
			DEPTH24_STENCIL8 = GL_DEPTH24_STENCIL8,
			DEPTH32_STENCIL8 = GL_DEPTH32F_STENCIL8
		};

		enum EnumRBOAttachmentType : GLint
		{
			DEPTH_ATTACHMENT = GL_DEPTH_ATTACHMENT,
			STENCIL_ATTACHMENT = GL_STENCIL_ATTACHMENT,
			DEPTH_STENCIL_ATTACHMEN = GL_DEPTH_STENCIL_ATTACHMENT
		};

		RBOWrapper();
		~RBOWrapper();

		virtual void bind();
		virtual void unbind();

		void setStorage(const glm::vec2& size = AndrickWindow::getFocusedWindow()->getSize(), EnumRBOStorageType storageType = EnumRBOStorageType::DEPTH32_STENCIL8);

	private:
		virtual void createID();
	};
}

#endif