#ifndef ANDRICK_EBO_WRAPPER_H_
#define ANDRICK_EBO_WRAPPER_H_

#include "../GLObjectWrapper.h"

namespace andrick
{
	class EBOWrapper : public GLObjectWrapper
	{
		friend class Mesh;

	public:
		EBOWrapper(std::vector<GLint> pIndices);
		~EBOWrapper();

		virtual void bind();
		virtual void unbind();

		inline GLint getIndiceCount() { return static_cast<GLint>(mpIndiceData.size()); };

	private:
		std::vector<GLint> mpIndiceData;

		virtual void createID();
	};
}

#endif