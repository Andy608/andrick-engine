#include "AndrickWindow.h"
#include "../logger/LoggerMaster.h"
using namespace andrick;

const std::string AndrickWindow::msCLASS_NAME = "AndrickWindow";
const std::string AndrickWindow::msLOGGER_NAME = msCLASS_NAME + " Logger";
std::map<std::string, AndrickWindow*> AndrickWindow::msWindowList = std::map<std::string, AndrickWindow*>();
AndrickWindow* AndrickWindow::msFocusedWindow = nullptr;
GLboolean AndrickWindow::msIsGLFWInitialized = GL_FALSE;

GLboolean AndrickWindow::init()
{
	if (!glfwInit())
	{
		LoggerMaster::getLogger(msLOGGER_NAME)->logCritical(msCLASS_NAME, "Unable to initialize GLFW and AndrickWindow.");
		msIsGLFWInitialized = GL_FALSE;
	}
	else
	{
		LoggerMaster::getUniversalLogger().logInfo(msCLASS_NAME, "Initializing GLFW and AndrickWindow.");
		setErrorCallback(defaultErrorCallback);
		msIsGLFWInitialized = GL_TRUE;
	}

	return msIsGLFWInitialized;
}

void AndrickWindow::cleanup()
{
	auto windowIter = msWindowList.begin();
	for (; windowIter != msWindowList.end(); ++windowIter)
	{
		delete windowIter->second;
		windowIter->second = nullptr;
	}

	glfwTerminate();
	msIsGLFWInitialized = GL_FALSE;
}

GLboolean AndrickWindow::addWindow(std::string windowID, AndrickWindow* windowFrame)
{
	GLboolean success = GL_FALSE;

	if (windowFrame)
	{
		msWindowList.insert(std::make_pair(windowID, windowFrame));
		success = GL_TRUE;
	}

	return success;
}

GLboolean AndrickWindow::destroyWindow(std::string windowID)
{
	GLboolean success = GL_FALSE;
	auto windowIter = msWindowList.find(windowID);
	
	if (windowIter != msWindowList.end())
	{
		delete windowIter->second;
		windowIter->second = nullptr;
		msWindowList.erase(windowIter);
		success = GL_TRUE;
	}

	return success;
}

GLboolean AndrickWindow::destroyWindow(AndrickWindow*& window)
{
	GLboolean success = GL_FALSE;

	for (auto windowIter = msWindowList.begin(); windowIter != msWindowList.end(); ++windowIter)
	{
		if (windowIter->second == window)
		{
			delete windowIter->second;
			windowIter->second = nullptr;
			window = nullptr;
			msWindowList.erase(windowIter);
			success = GL_TRUE;
			break;
		}
	}

	return success;
}

void AndrickWindow::closeWindow(AndrickWindow* window)
{
	glfwSetWindowShouldClose(window->mWindowContext, GL_TRUE);
}

AndrickWindow* AndrickWindow::initWindow(std::string windowID, std::string title, GLuint width, GLuint height)
{
	AndrickWindow* frame = nullptr;
	auto windowIter = msWindowList.find(windowID);

	if (windowIter != msWindowList.end())
	{
		LoggerMaster::getLogger(msLOGGER_NAME)->logWarn(msCLASS_NAME, "WindowID: \"" + windowID + "\" is already initialized. Updating existing values.");
		frame = windowIter->second;
		frame->setTitle(windowID);
		frame->setSize(width, height);
	}
	else
	{
		frame = new AndrickWindow(windowID, title, width, height);
		addWindow(windowID, frame);
	}
	
	return getWindow(windowID);
}

AndrickWindow* AndrickWindow::getWindow(std::string windowID)
{
	auto windowIter = msWindowList.find(windowID);

	if (windowIter != msWindowList.end())
	{
		return windowIter->second;
	}
	else
	{
		std::string errMessage = "Unable to get windowID: \"" + windowID + "\". The id is not registered as a valid window.";
		LoggerMaster::getLogger(msLOGGER_NAME)->logWarn(msCLASS_NAME, errMessage);
		return nullptr;
	}
}

GLboolean AndrickWindow::shouldClose(AndrickWindow* window)
{
	if (!window)
	{
		LoggerMaster::getLogger(msLOGGER_NAME)->logError(msCLASS_NAME, "The window frame is null! Returning false.");
	}
	else
	{
		if (window->mWindowContext)
		{
			return glfwWindowShouldClose(window->mWindowContext);
		}
		else
		{
			LoggerMaster::getLogger(msLOGGER_NAME)->logWarn(msCLASS_NAME, "The window context does not exist for windowID: \"" + window->mWindowID + "\". Returning false.");
		}
	}

	return GL_FALSE;
}

AndrickWindow::AndrickWindow(std::string windowID, std::string title, GLuint width, GLuint height) :
	mIsWindowCreated(GL_FALSE), 
	mWindowID(windowID),
	mpViewport(new AndrickViewport())
{
	//Default viewport settings.
	//setViewport(glm::ivec2(), glm::ivec2(width, height), std::weak_ptr<Camera>());
	setTitle(title);
	setSize(width, height);
}

AndrickWindow::~AndrickWindow()
{
	cleanupContext();
}

void AndrickWindow::cleanupContext()
{
	if (mWindowContext)
	{
		glfwDestroyWindow(mWindowContext);
		mWindowContext = nullptr;

		if (mpViewport)
		{
			delete mpViewport;
			mpViewport = nullptr;
		}

		auto iter = mWindowCallbacks.begin();
		for (; iter != mWindowCallbacks.end(); ++iter)
		{
			delete iter->second;
		}

		mWindowCallbacks.clear();
	}

	mIsWindowCreated = GL_FALSE;
}

void AndrickWindow::setViewport(glm::ivec2 startPos, glm::ivec2 dimensions)
{
	mpViewport->setStartPosition(startPos);
	mpViewport->setDimensions(dimensions);

	glViewport(startPos.x, startPos.y, dimensions.x, dimensions.y);
}

void AndrickWindow::setViewport(glm::ivec2 startPos, glm::ivec2 dimensions, Camera* camera)
{
	setViewport(startPos, dimensions);
	mpViewport->setCamera(camera);
}

void AndrickWindow::update(const GLdouble& deltaTime)
{
	mpViewport->update(deltaTime);
}

//void AndrickWindow::render(const GLdouble& alpha)
//{
//	mpViewport->render(alpha);
//}

//Set will override a previous window hint if it is already in the hints list.
void AndrickWindow::setWindowHint(EnumWindowHint hintType, GLint hintValue)
{
	auto hintIter = mWindowHints.find(hintType);

	if (hintIter != mWindowHints.end())
	{
		hintIter->second = hintValue;
	}
	else
	{
		mWindowHints.insert(std::make_pair(hintType, hintValue));
	}
}

//Add will only set the hint for the window if it is not already in the list.
void AndrickWindow::addWindowHint(EnumWindowHint hintType, GLint hintValue)
{
	mWindowHints.insert(std::make_pair(hintType, hintValue));
}

void AndrickWindow::addCallback(WindowCallback* callback)
{
	mWindowCallbacks.insert(std::make_pair(callback->getCallbackType(), callback));
}

void AndrickWindow::initWindowHints()
{
	//Use the default window hints
	if (mWindowHints.empty())
	{
		initDefaultWindowHints();
	}

	auto iter = mWindowHints.begin();
	for (; iter != mWindowHints.end(); ++iter)
	{
		glfwWindowHint(iter->first, iter->second);
	}
}

void AndrickWindow::initDefaultWindowHints()
{
	addWindowHint(CONTEXT_VERSION_MAJOR, 3);
	addWindowHint(CONTEXT_VERSION_MINOR, 3);
	addWindowHint(OPENGL_PROFILE_TYPE, OPENGL_CORE_PROFILE);
	addWindowHint(OPENGL_FORWARD_COMPATIBLE, GL_TRUE);
	addWindowHint(RESIZABLE, GL_TRUE);
}

void AndrickWindow::initWindowCallbacks()
{
	auto iter = mWindowCallbacks.begin();
	for (; iter != mWindowCallbacks.end(); ++iter)
	{
		switch (iter->first)
		{
		case WindowCallback::EnumCallback::CURSOR_POS_CALLBACK:						//If the window supports cursor position callbacks, bind function
			glfwSetCursorPosCallback(mWindowContext, cursorPosCallback);
			break;
		case WindowCallback::EnumCallback::FRAMEBUFFER_SIZE_CALLBACK:				//If the window supports framebuffer size callbacks, bind function
			glfwSetFramebufferSizeCallback(mWindowContext, framebufferSizeCallback);
			break;
		case WindowCallback::EnumCallback::KEYBOARD_CALLBACK:						//If the window supports keyboard callbacks, bind function
			glfwSetKeyCallback(mWindowContext, keyCallback);
			break;
		case WindowCallback::EnumCallback::MOUSE_BUTTON_CALLBACK:					//If the window supports mouse button callbacks, bind function
			glfwSetMouseButtonCallback(mWindowContext, mouseButtonCallback);
			break;
		case WindowCallback::EnumCallback::SCROLL_CALLBACK:							//If the window supports scroll callbacks, bind function
			glfwSetScrollCallback(mWindowContext, mouseScrollCallback);
			break;
		case WindowCallback::EnumCallback::WINDOW_CLOSE_CALLBACK:					//If the window supports window close callbacks, bind function
			glfwSetWindowCloseCallback(mWindowContext, windowCloseCallback);
			break;
		case WindowCallback::EnumCallback::WINDOW_FOCUS_CALLBACK:					//If the window supports window focus callbacks, bind function
			glfwSetWindowFocusCallback(mWindowContext, windowFocusCallback);
			break;
		case WindowCallback::EnumCallback::WINDOW_POS_CALLBACK:						//If the window supports window position callbacks, bind function
			glfwSetWindowPosCallback(mWindowContext, windowPositionCallback);
			break;
		case WindowCallback::EnumCallback::WINDOW_SIZE_CALLBACK:					//If the window supports window size callbacks, bind function
			glfwSetWindowSizeCallback(mWindowContext, windowSizeCallback);
			break;
		default:
			LoggerMaster::getLogger(msLOGGER_NAME)->logCritical(msCLASS_NAME, "Unknown window callback.");
		}
	}
}

void AndrickWindow::constructWindow()
{
	if (mIsWindowCreated)
	{
		LoggerMaster::getLogger(msLOGGER_NAME)->logWarn(msCLASS_NAME, "Window is already created for windowID: \"" + mWindowID + "\". Destroying current context and recreating...");
		cleanupContext();
	}

	mWindowContext = glfwCreateWindow(mWindowSize.x, mWindowSize.y, mTitle.c_str(), nullptr, nullptr);
	
	if (mWindowContext)
	{
		//Set the current glfw context to the new window so we can set the window hints.
		GLFWwindow* previousContext = glfwGetCurrentContext();
		glfwMakeContextCurrent(mWindowContext);

		initWindowHints();
		glfwHideWindow(mWindowContext);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			mIsWindowCreated = GL_FALSE;
			
			LoggerMaster::getLogger(msLOGGER_NAME)->logCritical(msCLASS_NAME, "Unable to initialize GLAD.");
			cleanup();
		}
		else
		{
			mIsWindowCreated = GL_TRUE;

			initWindowCallbacks();

			//Temporary. Have separate function so the viewport can be variable.
			glViewport(0, 0, mWindowSize.x, mWindowSize.y);
			glfwShowWindow(mWindowContext);
		}

		//Set the glfw window context back to the previous if it wasn't NULL.
		if (previousContext)
		{
			glfwMakeContextCurrent(previousContext);
		}
	}
}

//Mutators
///////////////////////////

void AndrickWindow::setTitle(std::string title)
{
	mTitle = title;

	if (mWindowContext)
	{
		glfwSetWindowTitle(mWindowContext, mTitle.c_str());
	}
}

void AndrickWindow::setWidth(const GLuint& width)
{
	setSize(width, mWindowSize.y);
}

void AndrickWindow::setHeight(const GLuint& height)
{
	setSize(mWindowSize.x, height);
}

void AndrickWindow::setSize(const GLuint& width, const GLuint& height)
{
	mWindowSize.x = width;
	mWindowSize.y = height;

	if (mWindowContext)
	{
		glfwSetWindowSize(mWindowContext, mWindowSize.x, mWindowSize.y);
	}
}

//NO SAFTEY CHECK FOR PERFORMACE. Make sure your window context is created before using.
void AndrickWindow::showWindow() const
{
	glfwShowWindow(mWindowContext);
}

//NO SAFTEY CHECK FOR PERFORMACE. Make sure your window context is created before using.
void AndrickWindow::hideWindow() const
{
	glfwHideWindow(mWindowContext);
}

//This is going to move to a renderer in the future.
void AndrickWindow::clearColor(const GLfloat& red, const GLfloat& green, const GLfloat& blue, const GLfloat& alpha) const
{
	//Is this slow to set the context every time we do this? Not sure, need to research.
	GLFWwindow* previousContext = glfwGetCurrentContext();
	glfwMakeContextCurrent(mWindowContext);
	glClearColor(red, green, blue, alpha);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glfwMakeContextCurrent(previousContext);
}

//NO SAFTEY CHECK FOR PERFORMACE. Make sure your window context is created before using.
void AndrickWindow::flip()
{
	glfwSwapBuffers(mWindowContext);
}

void AndrickWindow::setViewport(GLuint startX, GLuint startY, GLuint width, GLuint height) const
{
	glViewport(startX, startY, width, height);
}

///////////////////////////

GLboolean AndrickWindow::isWindowCreated()
{
	if (mIsWindowCreated)
	{
		LoggerMaster::getLogger(msLOGGER_NAME)->logWarn(msCLASS_NAME, "This window context is already created.");
	}

	return mIsWindowCreated;
}

AndrickWindow* AndrickWindow::getFocusedWindow(GLFWwindow* windowHandle)
{
	AndrickWindow* focusedWindow = nullptr;

	for (auto windowIter = msWindowList.begin(); windowIter != msWindowList.end(); ++windowIter)
	{
		if (windowIter->second->mWindowContext == windowHandle)
		{
			focusedWindow = windowIter->second;
		}
	}

	return focusedWindow;
}

void AndrickWindow::defaultErrorCallback(GLint error, const GLchar *description)
{
	LoggerMaster::getLogger(msLOGGER_NAME)->logError(msCLASS_NAME, "GLFW Window Error #" + std::to_string(error) + ": " + std::string(description));
}

void AndrickWindow::cursorPosCallback(GLFWwindow* windowHandle, GLdouble xPosition, GLdouble yPosition)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		dynamic_cast<const CursorPosCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::CURSOR_POS_CALLBACK)->second)->mCALLBACK_FUNC(xPosition, yPosition);
	}
}

void AndrickWindow::framebufferSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		dynamic_cast<const FramebufferSizeCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::FRAMEBUFFER_SIZE_CALLBACK)->second)->mCALLBACK_FUNC(windowWidth, windowHeight);
	}
}

void AndrickWindow::keyCallback(GLFWwindow* windowHandle, GLint key, GLint scancode, GLint action, GLint mode)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		dynamic_cast<const KeyboardCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::KEYBOARD_CALLBACK)->second)->mCALLBACK_FUNC(key, scancode, action, mode);
	}
}

void AndrickWindow::mouseButtonCallback(GLFWwindow* windowHandle, GLint button, GLint action, GLint mode)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		dynamic_cast<const MouseButtonCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::MOUSE_BUTTON_CALLBACK)->second)->mCALLBACK_FUNC(button, action, mode);
	}
}

void AndrickWindow::mouseScrollCallback(GLFWwindow* windowHandle, GLdouble xOffset, GLdouble yOffset)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		dynamic_cast<const ScrollCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::SCROLL_CALLBACK)->second)->mCALLBACK_FUNC(xOffset, yOffset);
	}
}

void AndrickWindow::windowCloseCallback(GLFWwindow* windowHandle)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		dynamic_cast<const WindowCloseCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::WINDOW_CLOSE_CALLBACK)->second)->mCALLBACK_FUNC();

		if (shouldClose(windowFrame))
		{
			closeWindow(windowFrame);
		}
	}
}

void AndrickWindow::windowFocusCallback(GLFWwindow* windowHandle, GLint isFocused)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		msFocusedWindow = windowFrame;
		dynamic_cast<const WindowFocusCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::WINDOW_FOCUS_CALLBACK)->second)->mCALLBACK_FUNC(isFocused);
	}
}

void AndrickWindow::windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		dynamic_cast<const WindowPosCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::WINDOW_POS_CALLBACK)->second)->mCALLBACK_FUNC(xPosition, yPosition);
	}
}

void AndrickWindow::windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight)
{
	AndrickWindow* windowFrame = getFocusedWindow(windowHandle);

	if (windowFrame)
	{
		windowFrame->mWindowSize.x = windowWidth;
		windowFrame->mWindowSize.y = windowHeight;
		dynamic_cast<const WindowSizeCallback*>(windowFrame->mWindowCallbacks.find(WindowCallback::EnumCallback::WINDOW_SIZE_CALLBACK)->second)->mCALLBACK_FUNC(windowWidth, windowHeight);
	}
}

void AndrickWindow::showCursor(AndrickWindow* window)
{
	glfwSetInputMode(window->mWindowContext, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void AndrickWindow::disableCursor(AndrickWindow* window)
{
	glfwSetInputMode(window->mWindowContext, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void AndrickWindow::setVerticalSync(AndrickWindow* window, GLboolean isVerticalSync)
{
	GLFWwindow* previousContext = glfwGetCurrentContext();
	glfwMakeContextCurrent(window->mWindowContext);

	glfwSwapInterval(isVerticalSync);

	//Set the glfw window context back to the previous if it wasn't NULL.
	if (previousContext)
	{
		glfwMakeContextCurrent(previousContext);
	}
}