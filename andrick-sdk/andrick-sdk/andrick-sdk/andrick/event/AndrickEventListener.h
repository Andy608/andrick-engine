#ifndef ANDRICK_EVENT_LISTENER_H_
#define ANDRICK_EVENT_LISTENER_H_

#include "../memory/TrackableObject.h"

namespace andrick
{
	struct AndrickEvent;

	class AndrickEventListener : public TrackableObject
	{
	public:
		inline AndrickEventListener() {};
		~AndrickEventListener();

		virtual void handleEvent(const AndrickEvent& theEvent) = 0;
	};
}

#endif