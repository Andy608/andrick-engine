#include "AndrickEventListener.h"
#include "AndrickEventQueue.h"

namespace andrick
{
	AndrickEventListener::~AndrickEventListener()
	{
		AndrickEventQueue::removeListenerFromAllEvents(this);
	};
}