#include "EBOWrapper.h"

namespace andrick
{
	EBOWrapper::EBOWrapper(std::vector<GLint> pIndices) :
		GLObjectWrapper(), mpIndiceData(pIndices)
	{
		createID();
	}

	void EBOWrapper::cleanup()
	{
		glDeleteBuffers(1, &mID);
		mpIndiceData.clear();
	}

	void EBOWrapper::bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * mpIndiceData.size(), &mpIndiceData[0], GL_STATIC_DRAW);//In the future, we may need to not hardcode GL_STATIC_DRAW.
	}

	void EBOWrapper::unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void EBOWrapper::createID()
	{
		glGenBuffers(1, &mID);
	}
}