#include "AndrickViewport.h"
#include "../event/AndrickEventQueue.h"

namespace andrick
{
	AndrickViewport::AndrickViewport() : AndrickViewport(glm::ivec2(), glm::ivec2(), nullptr) {}

	AndrickViewport::AndrickViewport(glm::ivec2 startPos, glm::ivec2 dimensions, Camera* pCamera) :
		mStartPosition(startPos), mDimensions(dimensions), mpCamera(pCamera)
	{
		if (mpCamera)
		{
			mpCamera->updateProjectionMatrix(mDimensions.x, mDimensions.y);
		}

		AndrickEventQueue::addListener(EnumAndrickEvent::WINDOW_RESIZE_EVENT, this);
	}

	AndrickViewport::~AndrickViewport()
	{

	}

	void AndrickViewport::update(const GLdouble& deltaTime)
	{
		if (mpCamera)
		{
			mpCamera->update(deltaTime);
		}
	}

	/*void AndrickViewport::render(const GLdouble& alpha)
	{
		if (!mpCamera.expired())
		{
			mpCamera.lock()->render(alpha);
		}
	}*/

	void AndrickViewport::updateCameraProjection()
	{
		if (mpCamera)
		{
			mpCamera->updateProjectionMatrix(mDimensions.x, mDimensions.y);
		}
	}

	void AndrickViewport::handleEvent(const AndrickEvent& theEvent)
	{
		if (theEvent.getEventType() == EnumAndrickEvent::WINDOW_RESIZE_EVENT)
		{
			const WindowResizeEvent& castedEvent = static_cast<const WindowResizeEvent&>(theEvent);

			//For now resize with window.
			//In the future the viewport should resize differently according to how the window wants it to.
			glViewport(mStartPosition.x, mStartPosition.y, castedEvent.newWidth, castedEvent.newHeight);

			if (mpCamera)
			{
				mpCamera->updateProjectionMatrix(castedEvent.newWidth, castedEvent.newHeight);
			}
		}
	}
}