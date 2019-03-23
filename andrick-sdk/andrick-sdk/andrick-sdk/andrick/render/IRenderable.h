#ifndef ANDRICK_IRENDERABLE_H_
#define ANDRICK_IRENDERABLE_H_

#include <functional>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "../memory/TrackableObject.h"

namespace andrick
{
	class IRenderable : public TrackableObject
	{
	public:
		inline IRenderable() {};
		virtual ~IRenderable() = 0 {};

		inline void addRenderFunc(std::function<void()> renderFunc) { mRenderFunc = renderFunc; };
		inline virtual void render() { mRenderFunc(); };

		virtual const GLfloat* getTransformationMatrixPtr() = 0;

	private:
		std::function<void()> mRenderFunc;
	};
}

#endif