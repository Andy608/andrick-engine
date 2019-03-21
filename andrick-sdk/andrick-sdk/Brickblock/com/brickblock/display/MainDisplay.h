#ifndef BB_MAIN_DISPLAY_H_
#define BB_MAIN_DISPLAY_H_

#include <andrick/window/AndrickWindow.h>
#include <andrick/event/AndrickEventListener.h>
#include <andrick/memory/NonCopyable.h>

namespace andrick
{
	class Logger;
}

namespace bb
{
	class MainDisplay : public andrick::AndrickEventListener, andrick::NonCopyable
	{
		friend class Brickblock;

	public:
		virtual void handleEvent(const andrick::AndrickEvent& theEvent) override;

	private:
		static const std::string msCLASS_NAME;
		static MainDisplay* mspInstance;
		static const std::string msLOGGER_ID;

		static GLboolean initInstance();
		static void cleanupInstance();

		andrick::AndrickWindow* mpWindow;

		MainDisplay();
		virtual ~MainDisplay();

		//void errorCallback(GLint error, const GLchar *description);
		static void cursorPosCallback(GLdouble xPosition, GLdouble yPosition);
		static void framebufferSizeCallback(GLint windowWidth, GLint windowHeight);
		static void keyCallback(GLint key, GLint scancode, GLint action, GLint mode);
		static void mouseButtonCallback(GLint button, GLint action, GLint mode);
		static void mouseScrollCallback(GLdouble xOffset, GLdouble yOffset);
		static void windowCloseCallback();
		static void windowFocusCallback(GLint isFocused);
		static void windowPositionCallback(GLint xPosition, GLint yPosition);
		static void windowSizeCallback(GLint windowWidth, GLint windowHeight);
	};
}

#endif