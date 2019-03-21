#ifndef ANDRICK_EVENT_QUEUE_H_
#define ANDRICK_EVENT_QUEUE_H_

#include <glad/glad.h>
#include <map>
#include <queue>
#include "../memory/TrackableObject.h"
#include "../memory/NonCopyable.h"
#include "AndrickEvent.h"

namespace andrick
{
	class AndrickEventListener;

	class AndrickEventQueue : public TrackableObject, NonCopyable
	{
		friend class AndrickCore;
		friend class InputProcessor;

	public:
		static void addEventToQueue(AndrickEvent* theEvent);
		static void addListener(EnumAndrickEvent eventType, AndrickEventListener* pListener);
		static void removeListener(EnumAndrickEvent eventType, AndrickEventListener* pListener);
		static void removeListenerFromAllEvents(AndrickEventListener* pListener);

	private:
		static const std::string msCLASS_NAME;

		static GLboolean init();
		static void cleanup();
		static void update(const GLdouble& deltaTime);

		static AndrickEventQueue* mspInstance;
		std::multimap<EnumAndrickEvent, AndrickEventListener*> mListenerList;

		std::queue<AndrickEvent*> mEventQueue;

		inline AndrickEventQueue() {};
		virtual ~AndrickEventQueue();
	};
}

#endif