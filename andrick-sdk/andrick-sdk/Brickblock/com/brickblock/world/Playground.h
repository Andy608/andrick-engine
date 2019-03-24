#ifndef BB_PLAYGROUND_H_
#define BB_PLAYGROUND_H_

#include <andrick/memory/TrackableObject.h>
#include <andrick/memory/NonCopyable.h>
#include <andrick/render/renderer/ModelRenderer.h>

#include <andrick/render/camera/Camera.h>

namespace bb
{
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
	};
}

#endif