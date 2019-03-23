#ifndef VAO_WRAPPER_H_
#define VAO_WRAPPER_H_

#include "../GLObjectWrapper.h"

namespace andrick
{
	class VBOWrapper;
	class VAOWrapper : public GLObjectWrapper
	{
	public:
		VAOWrapper();
		~VAOWrapper();

		virtual void bind() const;
		virtual void unbind() const;

		void bindVBOToVAO(GLuint bufferIndex, VBOWrapper* vboWrapper);

	private:
		virtual void createID();
	};
}

#endif