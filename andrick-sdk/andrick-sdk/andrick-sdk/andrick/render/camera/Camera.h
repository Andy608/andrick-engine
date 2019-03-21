#ifndef ANDRICK_CAMERA_H_
#define ANDRICK_CAMERA_H_

#include <memory>
#include <glm/gtc/type_ptr.hpp>
#include "../../memory/TrackableObject.h"
#include "../../util/math/Transform.h"

namespace andrick
{
	struct AndrickEvent;
	class AndrickEventQueue;

	class Camera : public TrackableObject
	{
		friend class AndrickViewport;

	public:
		static const glm::mat4& getProjectionMatrix();
		static const GLfloat* getProjectionMatrixPtr();

		Camera(glm::vec3 position, glm::vec3 rotation);
		inline virtual ~Camera() {};

		virtual void update(const GLdouble& deltaTime);
		void lerp(const GLdouble& alpha);

		inline std::shared_ptr<Transform> getTransform() { return mTransform; };
		inline const glm::mat4& getViewMatrix() const { return mViewMatrix; };
		inline const GLfloat* getViewMatrixPtr() const { return glm::value_ptr(mViewMatrix); };

	protected:
		std::shared_ptr<Transform> mTransform;

		glm::vec3 mCameraUp;
		glm::vec3 mCameraRight;
		glm::vec3 mCameraForward;

		//The direction the camera is moving. Not the same as the direction the camera is looking.
		glm::vec3 mMoveDirection;

		void updateViewMatrix();

	private:
		static const GLfloat msNEAR_PLANE;
		static const GLfloat msFAR_PLANE;

		//For now this is OK but in the future this should be per viewport.
		static glm::mat4 msPerspectiveMat;
		//static glm::mat4 msOrthoMat;
		//static std::shared_ptr<glm::mat4> mspProjectionMat;

		glm::mat4 mViewMatrix;

		void updateBasis();

		void updateProjectionMatrix(GLint viewportWidth, GLint viewportHeight);
	};
}

#endif