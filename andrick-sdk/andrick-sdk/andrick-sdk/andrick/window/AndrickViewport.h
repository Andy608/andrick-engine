#ifndef ANDRICK_VIEWPORT_H_
#define ANDRICK_VIEWPORT_H_

#include "../event/AndrickEventListener.h"
#include "../render/camera/Camera.h"
#include <glm/vec2.hpp>
#include <memory>

namespace andrick
{
	class AndrickViewport : public AndrickEventListener
	{
	public:
		//If the camera is null, then nothing will render to the viewport.
		AndrickViewport();
		AndrickViewport(glm::ivec2 startPos, glm::ivec2 dimensions, Camera* pCamera);
		~AndrickViewport();

		void update(const GLdouble& deltaTime);
		//void render(const GLdouble& alpha);

		inline Camera* getCamera() const { return mpCamera; };
		inline const glm::ivec2& getDimensions() const { return mDimensions; };
		inline const glm::ivec2& getStartPosition() const { return mStartPosition; };

		inline void setStartPosition(glm::ivec2 startPos) { mStartPosition = startPos; };
		inline void setDimensions(glm::ivec2 dimensions) { mDimensions = dimensions; updateCameraProjection(); };
		inline void setCamera(Camera* camera) { mpCamera = camera; updateCameraProjection(); };
		void updateCameraProjection();

		virtual void handleEvent(const AndrickEvent& theEvent) override;

	private:
		glm::ivec2 mStartPosition;
		glm::ivec2 mDimensions;
		Camera* mpCamera;

	};
}

#endif