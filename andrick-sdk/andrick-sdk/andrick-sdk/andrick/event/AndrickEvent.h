#ifndef ANDRICK_EVENT_H_
#define ANDRICK_EVENT_H_

#include <glad/glad.h>
#include "../memory/TrackableObject.h"
#include "../input/InputProcessor.h"

namespace andrick
{
	enum EnumAndrickEvent : GLint
	{
		INVALID_EVENT = -1,

		/* Framework Events */
		KEYBOARD_EVENT,
		MOUSE_BUTTON_EVENT,
		MOUSE_MOVE_EVENT,
		MOUSE_SCROLL_EVENT,
		WINDOW_RESIZE_EVENT,
		QUIT_EVENT,

		/* Camera Events */
		CAMERA_EVENT,
		CAMERA_FORWARD_EVENT,
		CAMERA_BACKWARD_EVENT,
		CAMERA_LEFT_EVENT,
		CAMERA_RIGHT_EVENT,
		CAMERA_UP_EVENT,
		CAMERA_DOWN_EVENT,

		NUM_EVENT_TYPES
	};

	struct AndrickEvent : public TrackableObject
	{
		inline AndrickEvent(const EnumAndrickEvent& eventType) : mEventType(eventType) {};
		inline ~AndrickEvent() = 0 {};

		inline EnumAndrickEvent getEventType() const { return mEventType; };

	private:
		EnumAndrickEvent mEventType;
	};

	struct QuitEvent : public AndrickEvent
	{
		inline QuitEvent() : AndrickEvent(EnumAndrickEvent::QUIT_EVENT) {};
	};

	struct KeyboardEvent : public AndrickEvent
	{
		inline KeyboardEvent(EnumInput inputCode, GLboolean isDown) :
			AndrickEvent(EnumAndrickEvent::KEYBOARD_EVENT), inputCode(inputCode), isDown(isDown) {}

		EnumInput inputCode;
		GLboolean isDown;
	};

	//Keeps track of current mouse position, previous mouse position, and mouse button click
	struct MouseMoveEvent : public AndrickEvent
	{
		inline MouseMoveEvent(GLdouble newX, GLdouble newY, GLdouble previousX, GLdouble previousY) :
			AndrickEvent(EnumAndrickEvent::MOUSE_MOVE_EVENT), newX(newX), newY(newY), previousX(previousX), previousY(previousY) {}

		GLdouble newX;
		GLdouble newY;
		GLdouble previousX;
		GLdouble previousY;
	};

	//Keeps track of window pos, window size, window focus, and if window should close
	//Break these up into separate events ^
	struct WindowResizeEvent : public AndrickEvent
	{
		inline WindowResizeEvent(GLint newWidth, GLint newHeight, GLint prevWidth, GLint prevHeight) :
			AndrickEvent(EnumAndrickEvent::WINDOW_RESIZE_EVENT), newWidth(newWidth), newHeight(newHeight), prevWidth(prevWidth), prevHeight(prevHeight) {};

		GLint newWidth;
		GLint newHeight;
		GLint prevWidth;
		GLint prevHeight;
	};

	struct CameraEvent : public AndrickEvent
	{
		enum EnumCameraMovement
		{
			FORWARD, BACKWARD, LEFT, RIGHT, UP, DOWN
		};

		inline CameraEvent(EnumCameraMovement movementType, GLboolean isMoving) :
			AndrickEvent(EnumAndrickEvent::CAMERA_EVENT), movementType(movementType), isMoving(isMoving) {};

		GLboolean isMoving;
		EnumCameraMovement movementType;
	};
}

#endif