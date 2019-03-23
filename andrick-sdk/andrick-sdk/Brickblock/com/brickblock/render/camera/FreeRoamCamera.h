#ifndef BB_FREE_ROAM_CAMERA_H_
#define BB_FREE_ROAM_CAMERA_H_

#include <andrick/render/camera/Camera.h>

namespace bb
{
	class FreeRoamCamera : public andrick::Camera
	{
	public:
		FreeRoamCamera(glm::vec3 position, glm::vec3 rotation);
		inline virtual ~FreeRoamCamera() {};

		virtual void update(const GLdouble& deltaTime) override;
	};
}

#endif