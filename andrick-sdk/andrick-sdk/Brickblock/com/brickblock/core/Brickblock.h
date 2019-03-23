#ifndef BB_BRICKBLOCK_H_
#define BB_BRICKBLOCK_H_

#include <andrick/memory/TrackableObject.h>
#include <andrick/memory/NonCopyable.h>

#include "../display/MainDisplay.h"
#include "../world/Playground.h"

namespace bb
{
	class Brickblock : public andrick::TrackableObject, andrick::NonCopyable
	{
	public:
		static GLboolean initGame();
		static void cleanupGame();

		static GLboolean runGame();

		static const std::string msLOGGER_ID;

	private:
		static const std::string msCLASS_NAME;

		static Brickblock* mspInstance;

		const GLint mTICKS_PER_SECOND = 60;
		const GLfloat mTIME_SLICE = 1.0f / static_cast<GLfloat>(mTICKS_PER_SECOND);

		GLboolean mIsRunning;

		void loop();
		void update(const GLdouble& deltaTime);
		void render(const GLdouble& alpha);

		Brickblock();
		virtual ~Brickblock();

		//Temporary Variables
		Playground* mpPlayground;
	};
}

#endif