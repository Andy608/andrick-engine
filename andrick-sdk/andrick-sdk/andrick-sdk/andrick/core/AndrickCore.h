#ifndef ANDRICK_H_
#define ANDRICK_H_

#include <glad/glad.h>
#include "../memory/ObjectTracker.h"
#include "../memory/NonCopyable.h"

namespace andrick
{
	class AndrickCore : private NonCopyable
	{
	public:
		static GLboolean initAndrick();
		static GLboolean cleanupAndrick();

	private:
		static const std::string msCLASS_NAME;
		static GLboolean smIsInitialized;

		inline AndrickCore() {};
		inline ~AndrickCore() {};
	};
}

#endif