#ifndef ANDRICK_RBO_WRAPPER_H_
#define ANDRICK_RBO_WRAPPER_H_

#include "../GLObjectWrapper.h"
#include "../../../window/AndrickWindow.h"

namespace andrick
{
	class RBOWrapper : public GLObjectWrapper
	{
	public:
		RBOWrapper();
		~RBOWrapper();

		virtual void bind();
		virtual void unbind();

		void setStorage(const glm::ivec2& size, const EnumInternalFormatType& storageType = EnumInternalFormatType::DEPTH24_STENCIL8);

	private:
		virtual void createID();
	};
}

#endif