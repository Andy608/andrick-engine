#ifndef ANDRICK_RBO_WRAPPER_H_
#define ANDRICK_RBO_WRAPPER_H_

#include "../../GLObjectWrapper.h"
#include "../../../../window/AndrickWindow.h"

namespace andrick
{
	class RBOWrapper : public GLObjectWrapper
	{
	public:
		RBOWrapper();
		inline virtual ~RBOWrapper() { cleanup(); };

		virtual void cleanup();

		virtual void bind();
		virtual void unbind();

		void setStorage(const glm::ivec2& size, const EnumInternalFormatType& storageType = EnumInternalFormatType::DEPTH24_STENCIL8);
		void setStorage(const GLint& width, const GLint& height, const EnumInternalFormatType& storageType = EnumInternalFormatType::DEPTH24_STENCIL8);
		void resizeBuffer(const GLint& width, const GLint& height);

		const EnumInternalFormatType getStorageType() const { return mInternalFormatType; }

	private:
		virtual void createID();

		EnumInternalFormatType mInternalFormatType;
	};
}

#endif