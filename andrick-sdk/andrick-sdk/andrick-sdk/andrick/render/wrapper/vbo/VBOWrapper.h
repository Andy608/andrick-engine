#ifndef ANDRICK_VBO_WRAPPER_H_
#define ANDRICK_VBO_WRAPPER_H_

#include "../GLObjectWrapper.h"

namespace andrick
{
	class VBOWrapper : public GLObjectWrapper
	{
		friend class VAOWrapper;

	public:
		enum class EnumBufferType : const GLuint
		{
			POSITIONS,
			COLORS,
			TEX_COORDS,
			NORMALS
		};

		const EnumBufferType mBUFFER_TYPE;

		VBOWrapper(const EnumBufferType& bufferType, std::vector<GLfloat> pBuffer, GLuint elementsPerVertex);
		~VBOWrapper();

		virtual void bind() const;
		virtual void unbind() const;

		const std::vector<GLfloat>& getBufferData() const { return mpBufferData; };
		GLuint getBufferSize() const { return static_cast<GLuint>(mpBufferData.size()); }

	private:
		std::vector<GLfloat> mpBufferData;
		GLuint mElementsPerVertex;
		GLuint mVertexCount;

		virtual void createID();
	};
}

#endif