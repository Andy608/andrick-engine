#include "FreeRoamCamera.h"
#include <andrick/util/math/MathHelper.h>
#include <andrick/window/AndrickWindow.h>
#include "../../input/InputData.h"

namespace bb
{
	FreeRoamCamera::FreeRoamCamera(glm::vec3 position, glm::vec3 rotation) :
		Camera(position, rotation)
	{

	}

	void FreeRoamCamera::update(const GLdouble& deltaTime)
	{
		mTransform->sync();

		//In the future add a selected camera variable to make sure all cameras don't move when input is pressed.

		//Move forward
		if (InputData::getKeyBinding(SettingsData::EnumGameSetting::CAMERA_FORWARD_KEYBINDING)->isPressed())
		{
			mMoveDirection += mCameraForward;
		}

		//Move backward
		if (InputData::getKeyBinding(SettingsData::EnumGameSetting::CAMERA_BACKWARD_KEYBINDING)->isPressed())
		{
			mMoveDirection += -mCameraForward;
		}

		//Move left
		if (InputData::getKeyBinding(SettingsData::EnumGameSetting::CAMERA_LEFT_KEYBINDING)->isPressed())
		{
			mMoveDirection += -mCameraRight;
		}

		//Move right
		if (InputData::getKeyBinding(SettingsData::EnumGameSetting::CAMERA_RIGHT_KEYBINDING)->isPressed())
		{
			mMoveDirection += mCameraRight;
		}

		//Move up
		if (InputData::getKeyBinding(SettingsData::EnumGameSetting::CAMERA_UP_KEYBINDING)->isPressed())
		{
			mMoveDirection += mCameraUp;
		}

		//Move down
		if (InputData::getKeyBinding(SettingsData::EnumGameSetting::CAMERA_DOWN_KEYBINDING)->isPressed())
		{
			mMoveDirection += -mCameraUp;
		}

		if (andrick::MathHelper::magnitudeSquared(mMoveDirection) > 0)
		{
			mMoveDirection = glm::normalize(mMoveDirection);
			mTransform->addPosition((float)(5.0 * deltaTime) * mMoveDirection);
		}

		mMoveDirection.x = 0.0f;
		mMoveDirection.y = 0.0f;
		mMoveDirection.z = 0.0f;

		andrick::AndrickWindow* window = andrick::AndrickWindow::getFocusedWindow();
		if (window)
		{
			const glm::ivec2 mouseDelta = InputData::getMouseDelta();
			const GLfloat mouseSensitivity = static_cast<GLfloat>(SettingsData::getSetting<andrick::IntegerSetting*>(SettingsData::EnumGameSetting::MOUSE_SENSITIVITY)->getCustomInteger());
			glm::vec3& rotation = mTransform->mRotation;
			rotation.x -= mouseDelta.y * static_cast<GLfloat>(deltaTime) * mouseSensitivity;
			rotation.y -= mouseDelta.x * static_cast<GLfloat>(deltaTime) * mouseSensitivity;

			if (rotation.x >= 89.0f) rotation.x = 89.0f;
			if (rotation.x <= -89.0f) rotation.x = -89.0f;
		}
	}
}