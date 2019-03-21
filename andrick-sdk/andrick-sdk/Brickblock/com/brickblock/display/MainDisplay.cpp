#include "MainDisplay.h"
#include <andrick/logger/LoggerMaster.h>
#include <andrick/window/callback/WindowCallbacks.h>
#include <andrick/event/AndrickEvent.h>
#include <andrick/event/AndrickEventQueue.h>
#include <andrick/input/InputProcessor.h>
#include "../setting/SettingsData.h"

namespace bb
{
	MainDisplay* MainDisplay::mspInstance = nullptr;
	const std::string MainDisplay::msCLASS_NAME = "MainDisplay";
	const std::string MainDisplay::msLOGGER_ID = msCLASS_NAME + " Logger";

	GLboolean MainDisplay::initInstance()
	{
		if (!mspInstance)
		{
			try
			{
				mspInstance = new MainDisplay();
			}
			catch (const std::runtime_error& e)
			{
				andrick::LoggerMaster::getLogger(msLOGGER_ID)->logCritical(msCLASS_NAME, std::string(e.what()));
			}
		}

		return mspInstance != nullptr;
	}

	void MainDisplay::cleanupInstance()
	{
		if (mspInstance)
		{
			//andrick::LoggerMaster::getLogger(msLOGGER_ID)->logTrace(getClassStatic(), "Cleaning up Main Display.");
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	MainDisplay::MainDisplay()
	{
		andrick::AndrickEventQueue::addListener(andrick::EnumAndrickEvent::QUIT_EVENT, this);

		//Get saved start position and window dimensions here in the future.

		mpWindow = andrick::AndrickWindow::initWindow("main_display", "Brickblock v0.1.0a", 960, 540);

		if (mpWindow)
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logTrace(msCLASS_NAME, "Creating Main Display.");

			mpWindow->addCallback(new andrick::CursorPosCallback(MainDisplay::cursorPosCallback));
			mpWindow->addCallback(new andrick::FramebufferSizeCallback(MainDisplay::framebufferSizeCallback));
			mpWindow->addCallback(new andrick::KeyboardCallback(MainDisplay::keyCallback));
			mpWindow->addCallback(new andrick::MouseButtonCallback(MainDisplay::mouseButtonCallback));
			mpWindow->addCallback(new andrick::ScrollCallback(MainDisplay::mouseScrollCallback));
			mpWindow->addCallback(new andrick::WindowCloseCallback(MainDisplay::windowCloseCallback));
			mpWindow->addCallback(new andrick::WindowFocusCallback(MainDisplay::windowFocusCallback));
			mpWindow->addCallback(new andrick::WindowPosCallback(MainDisplay::windowPositionCallback));
			mpWindow->addCallback(new andrick::WindowSizeCallback(MainDisplay::windowSizeCallback));

			mpWindow->constructWindow();

			//Get settings from SettingsData
			andrick::BooleanSetting* vSync = SettingsData::getSetting<andrick::BooleanSetting*>(SettingsData::V_SYNC);
			andrick::AndrickWindow::setVerticalSync(mpWindow, vSync->getCustomInteger());

			//Default, set the viewport to the whole window.
			mpWindow->setViewport(glm::ivec2(), mpWindow->getSize());
		}
		else
		{
			throw(std::runtime_error("Unable to construct the Main Display."));
		}
	}

	MainDisplay::~MainDisplay()
	{
		andrick::LoggerMaster::getLogger(msLOGGER_ID)->logTrace(msCLASS_NAME, "Destroying Main Display.");
		andrick::AndrickWindow::destroyWindow(mpWindow);
		mpWindow = nullptr;
	}

	void MainDisplay::handleEvent(const andrick::AndrickEvent& theEvent)
	{
		if (theEvent.getEventType() == andrick::EnumAndrickEvent::QUIT_EVENT)
		{
			andrick::AndrickWindow::closeWindow(mpWindow);
		}
	}

	/*void MainDisplay::errorCallback(GLint error, const GLchar *description)
	{
		//Log to a special file in the future maybe.
	}*/

	void MainDisplay::cursorPosCallback(GLdouble xPosition, GLdouble yPosition)
	{
		static GLdouble prevX = 0, prevY = 0;

		if (prevX == 0 && prevY == 0)
		{
			mspInstance->mpWindow->getCursorPos(&prevX, &prevY);
		}

		andrick::MouseMoveEvent* mouseMoveEvent = new andrick::MouseMoveEvent(xPosition, yPosition, prevX, prevY);
		prevX = xPosition;
		prevY = yPosition;

		//andrick::LoggerMaster::getUniversalLogger().logDebug(msCLASS_NAME, "CURSOR MOVED");
		andrick::AndrickEventQueue::addEventToQueue(mouseMoveEvent);
	}

	void MainDisplay::framebufferSizeCallback(GLint windowWidth, GLint windowHeight)
	{

	}

	void MainDisplay::keyCallback(GLint key, GLint scancode, GLint action, GLint mode)
	{
		GLboolean isPressed = GL_FALSE;

		switch (action)
		{
		case GLFW_PRESS:
			isPressed = GL_TRUE;
			break;
		case GLFW_RELEASE:
			isPressed = GL_FALSE;
			break;
		default:
			return;
		}

		andrick::KeyboardEvent* keyboardEvent = new andrick::KeyboardEvent(static_cast<andrick::EnumInput>(key), isPressed);
		andrick::AndrickEventQueue::addEventToQueue(keyboardEvent);
	}

	void MainDisplay::mouseButtonCallback(GLint button, GLint action, GLint mode)
	{

	}

	void MainDisplay::mouseScrollCallback(GLdouble xOffset, GLdouble yOffset)
	{

	}

	void MainDisplay::windowCloseCallback()
	{

	}

	void MainDisplay::windowFocusCallback(GLint isFocused)
	{

	}

	void MainDisplay::windowPositionCallback(GLint xPosition, GLint yPosition)
	{

	}

	void MainDisplay::windowSizeCallback(GLint windowWidth, GLint windowHeight)
	{
		static glm::ivec2 windowSize;

		//First time initializing.
		if (windowSize.length() == 0)
		{
			windowSize = mspInstance->mpWindow->getSize();
		}
		
		andrick::WindowResizeEvent* windowResizeEvent = new andrick::WindowResizeEvent(windowWidth, windowHeight, windowSize.x, windowSize.y);
		windowSize.x = windowWidth;
		windowSize.y = windowHeight;

		andrick::AndrickEventQueue::addEventToQueue(windowResizeEvent);
	}
}