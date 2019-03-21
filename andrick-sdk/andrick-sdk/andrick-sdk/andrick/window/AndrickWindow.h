#ifndef ANDRICK_WINDOW_H_
#define ANDRICK_WINDOW_H_

#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <glm/detail/type_vec.hpp>
#include <map>
#include "../memory/TrackableObject.h"
#include "../memory/NonCopyable.h"
#include "callback/WindowCallbacks.h"
#include "AndrickViewport.h"

namespace andrick
{
	class AndrickWindow : public TrackableObject, NonCopyable
	{
		friend class AndrickCore;

	public:
		enum EnumWindowHint
		{
			CONTEXT_VERSION_MAJOR = GLFW_CONTEXT_VERSION_MAJOR,
			CONTEXT_VERSION_MINOR = GLFW_CONTEXT_VERSION_MINOR,
			OPENGL_PROFILE_TYPE = GLFW_OPENGL_PROFILE,
			OPENGL_CORE_PROFILE = GLFW_OPENGL_CORE_PROFILE,
			OPENGL_FORWARD_COMPATIBLE = GLFW_OPENGL_FORWARD_COMPAT,
			RESIZABLE = GLFW_RESIZABLE
		};

		static void showCursor(AndrickWindow* window);
		static void disableCursor(AndrickWindow* window);

		static void setErrorCallback(WindowCallback::ErrorFunc errorFunc) { glfwSetErrorCallback(errorFunc); };
		
		static GLboolean destroyWindow(AndrickWindow*& window);
		static GLboolean destroyWindow(std::string windowID);
		static void closeWindow(AndrickWindow* window);
		
		static AndrickWindow* initWindow(std::string windowID, std::string title, GLuint width, GLuint height);
		static AndrickWindow* getWindow(std::string windowID);

		static GLboolean shouldClose(AndrickWindow* window);
		static inline void pollEvents() { glfwPollEvents(); };
		static void setVerticalSync(AndrickWindow* window, GLboolean isVerticalSync);

		static inline AndrickWindow* getFocusedWindow() { return msFocusedWindow; };
		
		void setTitle(std::string title);

		void setViewport(glm::ivec2 startPos, glm::ivec2 dimensions);
		void setViewport(glm::ivec2 startPos, glm::ivec2 dimensions, Camera* camera);

		void update(const GLdouble& deltaTime);
		//void render(const GLdouble& alpha);

		//Set will override a previous window hint if it is already in the hints list.
		void setWindowHint(EnumWindowHint hintType, GLint hintValue);

		//Add will only set the hint for the window if it is not already in the list.
		void addWindowHint(EnumWindowHint hintType, GLint hintValue);

		void addCallback(WindowCallback* callback);

		void setWidth(const GLuint& width);
		void setHeight(const GLuint& height);
		void setSize(const GLuint& width, const GLuint& height);

		void showWindow() const;
		void hideWindow() const;

		void clearColor(const GLfloat& red, const GLfloat& green, const GLfloat& blue, const GLfloat& alpha) const;
		void flip();
		void setViewport(GLuint startX, GLuint startY, GLuint width, GLuint height) const;

		void constructWindow();

		inline const std::string& getTitle() const { return mTitle; };
		inline const glm::ivec2& getSize() const { return mWindowSize; };

		inline void getCursorPos(GLdouble* posX, GLdouble* posY) { glfwGetCursorPos(mWindowContext, posX, posY); };
		inline AndrickViewport& getViewport() const { return *mpViewport; };

	private:
		static GLboolean init();
		//Cleans up GLFW as well.
		static void cleanup();

		static GLboolean addWindow(std::string windowID, AndrickWindow* windowFrame);

		static const std::string msCLASS_NAME;
		static const std::string msLOGGER_NAME;
		static std::map<std::string, AndrickWindow*> msWindowList;
		static GLboolean msIsGLFWInitialized;
		static AndrickWindow* msFocusedWindow;

		GLboolean mIsWindowCreated;
		GLFWwindow* mWindowContext;
		std::string mWindowID;
		std::string mTitle;
		//Window Icon
		glm::ivec2 mWindowSize;
		AndrickViewport* mpViewport;

		std::map<EnumWindowHint, GLint> mWindowHints;
		std::map<WindowCallback::EnumCallback, WindowCallback*> mWindowCallbacks;

		AndrickWindow(std::string windowID, std::string title, GLuint width, GLuint height);
		virtual ~AndrickWindow();

		GLboolean isWindowCreated();
		void initWindowHints();
		void initDefaultWindowHints();
		void initWindowCallbacks();

		void cleanupContext();

		static AndrickWindow* getFocusedWindow(GLFWwindow* windowHandle);

		static void defaultErrorCallback(GLint error, const GLchar *description);
		static void cursorPosCallback(GLFWwindow* windowHandle, GLdouble xPosition, GLdouble yPosition);
		static void framebufferSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight);
		static void keyCallback(GLFWwindow* windowHandle, GLint key, GLint scancode, GLint action, GLint mode);
		static void mouseButtonCallback(GLFWwindow* windowHandle, GLint button, GLint action, GLint mode);
		static void mouseScrollCallback(GLFWwindow* windowHandle, GLdouble xOffset, GLdouble yOffset);
		static void windowCloseCallback(GLFWwindow* windowHandle);
		static void windowFocusCallback(GLFWwindow* windowHandle, GLint isFocused);
		static void windowPositionCallback(GLFWwindow* windowHandle, GLint xPosition, GLint yPosition);
		static void windowSizeCallback(GLFWwindow* windowHandle, GLint windowWidth, GLint windowHeight);
	};
}

#endif