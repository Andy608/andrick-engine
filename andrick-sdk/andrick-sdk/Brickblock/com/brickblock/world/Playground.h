#ifndef BB_PLAYGROUND_H_
#define BB_PLAYGROUND_H_

#include <andrick/memory/TrackableObject.h>
#include <andrick/memory/NonCopyable.h>
#include <andrick/render/renderer/ModelRenderer.h>

#include <andrick/render/camera/Camera.h>

namespace bb
{
	class ShaderProgram;

	class Playground : public andrick::TrackableObject, andrick::NonCopyable
	{
		friend class Brickblock;

	private:
		static const std::string& msCLASS_NAME;

		andrick::Camera* mpCamera;
		andrick::ModelRenderer* mpModelRenderer;

		Playground();
		~Playground();

		void update(const GLdouble& deltaTime);
		void render(const GLdouble& alpha);

		void updatePomDemo(const double& deltaTime, const double& time, const float& switchTime = 2.0f);
		void updatePhongDemo(const double& deltaTime, const double& time);

		void renderPomDemo(const double& alpha, andrick::ShaderProgram*& currentProgram);
		void renderPhongDemo(const double& alpha, andrick::ShaderProgram*& currentProgram);
		void renderJuliaDemo(const double& alpha, andrick::ShaderProgram*& currentProgram);
		void renderMandelbrotDemo(const double& alpha, andrick::ShaderProgram*& currentProgram);
	};
}

#endif