#ifndef ANDRICK_TIMER_H_
#define ANDRICK_TIMER_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace andrick
{
	struct Timer
	{
		static inline GLdouble getCurrentTime()
		{
			return glfwGetTime();
		}
	};
}

#endif