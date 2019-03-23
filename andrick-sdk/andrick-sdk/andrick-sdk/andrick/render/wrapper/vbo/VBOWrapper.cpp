#include "VBOWrapper.h"

namespace andrick
{
	VBOWrapper::VBOWrapper(const EnumBufferType& bufferType, std::vector<GLfloat> pBuffer, GLuint elementsPerVertex) :
		GLObjectWrapper(), mBUFFER_TYPE(bufferType), mpBufferData(pBuffer), mElementsPerVertex(elementsPerVertex), mVertexCount(static_cast<GLuint>(mpBufferData.size()) / mElementsPerVertex)
	{
		createID();
	}

	VBOWrapper::~VBOWrapper()
	{
		//Amount of buffers to delete, and the buffer to delete.
		glDeleteBuffers(1, &mID);

		mpBufferData.clear();
	}

	void VBOWrapper::bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mID);

		if (!mpBufferData.empty())
		{
			glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * mpBufferData.size(), &mpBufferData[0], GL_STATIC_DRAW);//In the future, we may need to not hardcode GL_STATIC_DRAW.
		}
	}

	void VBOWrapper::unbind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void VBOWrapper::createID()
	{
		//Amount of buffers to create, and the buffer to create.
		glGenBuffers(1, &mID);
	}
}