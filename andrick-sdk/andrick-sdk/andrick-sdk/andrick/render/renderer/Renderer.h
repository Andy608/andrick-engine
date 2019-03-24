#ifndef ANDRICK_RENDERER_H_
#define ANDRICK_RENDERER_H_

#include <glad/glad.h>
#include "../camera/Camera.h"
#include "../../memory/NonCopyable.h"
#include "../../memory/TrackableObject.h"
#include "../../asset/shader/ShaderProgram.h"


namespace andrick
{
	class Renderer : public andrick::TrackableObject, andrick::NonCopyable
	{
	public:
		enum EnumDrawType : GLint
		{
			FILL = GL_FILL,
			OUTLINE = GL_LINE
		};

		enum EnumCullType
		{
			FRONT_ONLY = GL_FRONT,
			BACK_ONLY = GL_BACK,
			FRONT_AND_BACK = GL_FRONT_AND_BACK
		};

		inline void setShaderProgram(const ShaderProgram* shaderProgram) { mpShaderProgram = shaderProgram; };
		inline void setCamera(const Camera* camera) { mpCamera = camera; };
		inline void setDrawType(EnumDrawType drawType) { mDrawType = drawType; };
		inline void setCullType(EnumCullType cullType) { mCullType = cullType; };

		const ShaderProgram* getCurrentShaderProgram() const { return mpShaderProgram; };
		const Camera* getCurrentCamera() const { return mpCamera; };

	protected:
		inline Renderer() : mpShaderProgram(nullptr), mpCamera(nullptr),
			mDrawType(EnumDrawType::FILL), mCullType(EnumCullType::FRONT_ONLY) {};

		inline virtual ~Renderer() = 0 {};

		const ShaderProgram* mpShaderProgram;
		const Camera* mpCamera;

		EnumDrawType mDrawType;
		EnumCullType mCullType;
	};
}

#endif