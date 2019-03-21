#ifndef ANDRICK_WINDOW_CALLBACKS_H_
#define ANDRICK_WINDOW_CALLBACKS_H_

#include <glad/glad.h>

namespace andrick
{
	struct WindowCallback
	{
		typedef void(*ErrorFunc)(GLint, const GLchar*);
		typedef void(*CursorPosFunc)(GLdouble, GLdouble);
		typedef void(*FramebufferSizeFunc)(GLint, GLint);
		typedef void(*KeyboardFunc)(GLint, GLint, GLint, GLint);
		typedef void(*MouseButtonFunc)(GLint, GLint, GLint);
		typedef void(*ScrollFunc)(GLdouble, GLdouble);
		typedef void(*WindowFocusFunc)(GLint);
		typedef void(*WindowPosFunc)(GLint, GLint);
		typedef void(*WindowSizeFunc)(GLint, GLint);
		typedef void(*WindowCloseFunc)();

		enum EnumCallback
		{
			CURSOR_POS_CALLBACK,
			FRAMEBUFFER_SIZE_CALLBACK,
			KEYBOARD_CALLBACK,
			MOUSE_BUTTON_CALLBACK,
			SCROLL_CALLBACK,
			WINDOW_CLOSE_CALLBACK,
			WINDOW_FOCUS_CALLBACK,
			WINDOW_POS_CALLBACK,
			WINDOW_SIZE_CALLBACK,
			CALLBACK_COUNT
		};

		inline WindowCallback(EnumCallback callbackType) : mCALLBACK_TYPE(callbackType) {};

		virtual EnumCallback getCallbackType() { return mCALLBACK_TYPE; };

	private:
		const EnumCallback mCALLBACK_TYPE;
	};

	struct CursorPosCallback : public WindowCallback
	{
		CursorPosCallback(CursorPosFunc func) : WindowCallback(CURSOR_POS_CALLBACK), mCALLBACK_FUNC(func) {};

		const CursorPosFunc mCALLBACK_FUNC;
	};

	struct FramebufferSizeCallback : public WindowCallback
	{
		FramebufferSizeCallback(FramebufferSizeFunc func) : WindowCallback(FRAMEBUFFER_SIZE_CALLBACK), mCALLBACK_FUNC(func) {};

		const FramebufferSizeFunc mCALLBACK_FUNC;
	};

	struct KeyboardCallback : public WindowCallback
	{
		KeyboardCallback(KeyboardFunc func) : WindowCallback(KEYBOARD_CALLBACK), mCALLBACK_FUNC(func) {};

		const KeyboardFunc mCALLBACK_FUNC;
	};

	struct MouseButtonCallback : public WindowCallback
	{
		MouseButtonCallback(MouseButtonFunc func) : WindowCallback(MOUSE_BUTTON_CALLBACK), mCALLBACK_FUNC(func) {};

		const MouseButtonFunc mCALLBACK_FUNC;
	};

	struct ScrollCallback : public WindowCallback
	{
		ScrollCallback(ScrollFunc func) : WindowCallback(SCROLL_CALLBACK), mCALLBACK_FUNC(func) {};

		const ScrollFunc mCALLBACK_FUNC;
	};

	struct WindowCloseCallback : public WindowCallback
	{
		WindowCloseCallback(WindowCloseFunc func) : WindowCallback(WINDOW_CLOSE_CALLBACK), mCALLBACK_FUNC(func) {};

		const WindowCloseFunc mCALLBACK_FUNC;
	};

	struct WindowFocusCallback : public WindowCallback
	{
		WindowFocusCallback(WindowFocusFunc func) : WindowCallback(WINDOW_FOCUS_CALLBACK), mCALLBACK_FUNC(func) {};

		const WindowFocusFunc mCALLBACK_FUNC;
	};

	struct WindowPosCallback : public WindowCallback
	{
		WindowPosCallback(WindowPosFunc func) : WindowCallback(WINDOW_POS_CALLBACK), mCALLBACK_FUNC(func) {};

		const WindowPosFunc mCALLBACK_FUNC;
	};

	struct WindowSizeCallback : public WindowCallback
	{
		WindowSizeCallback(WindowSizeFunc func) : WindowCallback(WINDOW_SIZE_CALLBACK), mCALLBACK_FUNC(func) {};

		const WindowSizeFunc mCALLBACK_FUNC;
	};
}

#endif