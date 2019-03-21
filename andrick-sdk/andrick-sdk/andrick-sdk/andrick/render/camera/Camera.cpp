#include "Camera.h"
#include "../../util/math/MathHelper.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "../../logger/LoggerMaster.h"

namespace andrick
{
	const GLfloat Camera::msNEAR_PLANE = 0.001f;
	const GLfloat Camera::msFAR_PLANE  = 100.0f;
	glm::mat4 Camera::msPerspectiveMat = glm::mat4(1.0f);
	//glm::mat4 Camera::msOrthoMat;
	//std::shared_ptr<glm::mat4> Camera::mspProjectionMat = std::make_shared<glm::mat4>(msPerspectiveMat);

	const glm::mat4& Camera::getProjectionMatrix()
	{
		return msPerspectiveMat;
	}

	const GLfloat* Camera::getProjectionMatrixPtr()
	{
		return glm::value_ptr(msPerspectiveMat);
	}

	Camera::Camera(glm::vec3 position, glm::vec3 rotation) :
		mTransform(std::make_shared<Transform>(position, rotation, glm::vec3(1.0f))),
		mViewMatrix(glm::mat4(1.0f)),
		mCameraForward(glm::vec3(0.0, 0.0, -1.0f))
	{
		updateViewMatrix();

		/*
		Right now, there is only one camera in the scene, so this is not an issue right now. 
		(If there were more cameras they would all be hooked into this listener 
		and would all move, not just the one being controlled, which is an issue we 
		can solve in the future if we need multiple cameras)
		*/
		//EventQueue::addListener(EnumEvent::CAMERA_EVENT, this);
	}

	void Camera::update(const GLdouble& deltaTime)
	{
		mTransform->sync();

		if (MathHelper::magnitudeSquared(mMoveDirection) > 0)
		{
			mMoveDirection = glm::normalize(mMoveDirection);
			mTransform->addPosition((float)(5.0 * deltaTime) * mMoveDirection);
		}

		mMoveDirection.x = 0.0f;
		mMoveDirection.y = 0.0f;
		mMoveDirection.z = 0.0f;
	}

	void Camera::lerp(const GLdouble& alpha)
	{
		mTransform->lerp(alpha);
		updateViewMatrix();
	}

	void Camera::updateBasis()
	{
		mCameraRight = glm::normalize(glm::cross(mCameraForward, MathHelper::WORLD_UP));
		mCameraUp = glm::cross(mCameraRight, mCameraForward);
	}

	void Camera::updateViewMatrix()
	{
		const glm::vec3& lerpedPos = mTransform->getLerpedPosition();
		const glm::vec3& lerpedRot = mTransform->getLerpedRotation();

		mCameraForward = glm::vec3(0.0f, 0.0f, -1.0f);
		MathHelper::rotAroundXAxis(mCameraForward, lerpedRot.x);
		MathHelper::rotAroundYAxis(mCameraForward, lerpedRot.y);
		MathHelper::rotAroundZAxis(mCameraForward, lerpedRot.z);
		mCameraForward = glm::normalize(mCameraForward);

		updateBasis();

		mViewMatrix = glm::lookAt(lerpedPos, lerpedPos + mCameraForward, mCameraUp);
	}

	//Update this through listening for a ViewportChanged event
	void Camera::updateProjectionMatrix(GLint viewportWidth, GLint viewportHeight)
	{
		msPerspectiveMat = glm::perspective(glm::radians(57.0f), static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight), msNEAR_PLANE, msFAR_PLANE);
		//msOrthoMat = glm::ortho(-static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight), static_cast<GLfloat>(viewportWidth) / static_cast<GLfloat>(viewportHeight), -1.0f, 1.0f, msNEAR_PLANE, msFAR_PLANE);
	}
}