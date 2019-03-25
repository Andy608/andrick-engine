#ifndef ANDRICK_GL_OBJECT_WRAPPER_H_
#define ANDRICK_GL_OBJECT_WRAPPER_H_

#include <glad/glad.h>
#include <vector>
#include "../../memory/TrackableObject.h"
#include "../../memory/NonCopyable.h"

namespace andrick
{
	class GLObjectWrapper : public TrackableObject, NonCopyable//Might not be able to do noncopyable, but we'll see.
	{
	public:
		inline GLObjectWrapper() {};
		inline virtual ~GLObjectWrapper() {};

		virtual void bind() = 0;
		virtual void unbind() = 0;

		inline const GLuint& getID() const { return mID; };

	protected:
		GLuint mID;

		virtual void createID() = 0;
	};
}

#endif