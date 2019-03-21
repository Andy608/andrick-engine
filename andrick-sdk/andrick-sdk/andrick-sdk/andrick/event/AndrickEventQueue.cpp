#include "AndrickEventQueue.h"
#include "AndrickEventListener.h"
#include "../logger/LoggerMaster.h"

namespace andrick
{
	AndrickEventQueue* AndrickEventQueue::mspInstance = nullptr;
	const std::string AndrickEventQueue::msCLASS_NAME = "AndrickEventQueue";

	GLboolean AndrickEventQueue::init()
	{
		GLboolean success = GL_FALSE;

		if (!mspInstance)
		{
			mspInstance = new AndrickEventQueue();
			LoggerMaster::getUniversalLogger().logInfo(mspInstance->msCLASS_NAME, "Initializing the EventQueue.");
			success = (mspInstance != nullptr);
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(mspInstance->msCLASS_NAME, "The EventQueue is already initialized.");
		}

		return success;
	}

	void AndrickEventQueue::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	void AndrickEventQueue::addEventToQueue(AndrickEvent* theEvent)
	{
		mspInstance->mEventQueue.push(theEvent);
	}

	void AndrickEventQueue::addListener(EnumAndrickEvent eventType, AndrickEventListener* pListener)
	{
		mspInstance->mListenerList.insert(std::pair<EnumAndrickEvent, AndrickEventListener*>(eventType, pListener));
	}

	void AndrickEventQueue::removeListener(EnumAndrickEvent eventType, AndrickEventListener* pListener)
	{
		//Removes the listener that is listening for a specific event.

		std::pair<std::multimap<EnumAndrickEvent, AndrickEventListener*>::iterator, std::multimap<EnumAndrickEvent, AndrickEventListener*>::iterator> range;
		range = mspInstance->mListenerList.equal_range(eventType);

		std::multimap<EnumAndrickEvent, AndrickEventListener*>::iterator iter;

		for (iter = range.first; iter != range.second; ++iter)
		{
			if (iter->second == pListener)
			{
				mspInstance->mListenerList.erase(iter);
				break;//Prevents using invalid iterator after erasing.
			}
		}
	}

	void AndrickEventQueue::removeListenerFromAllEvents(AndrickEventListener* pListener)
	{
		std::multimap<EnumAndrickEvent, AndrickEventListener*>::iterator iter;
		GLboolean iteratedWholeList = false;

		while (!iteratedWholeList)
		{
			iteratedWholeList = true;

			for (iter = mspInstance->mListenerList.begin(); iter != mspInstance->mListenerList.end(); ++iter)
			{
				if (iter->second == pListener)
				{
					mspInstance->mListenerList.erase(iter);
					iteratedWholeList = false;//Didn't make it through the entire list, so set false.
					break;//Prevents using invalid iterator after erasing.
				}
			}
		}
	}

	AndrickEventQueue::~AndrickEventQueue()
	{
		mListenerList.clear();
	}

	void AndrickEventQueue::update(const GLdouble& deltaTime)
	{
		while (!mspInstance->mEventQueue.empty())
		{
			const AndrickEvent* nextEvent = mspInstance->mEventQueue.front();
			mspInstance->mEventQueue.pop();

			//Pair of lower and upper bounds represented as iterators.
			std::pair<std::multimap<EnumAndrickEvent, AndrickEventListener*>::iterator, std::multimap<EnumAndrickEvent, AndrickEventListener*>::iterator> range;
			range = mspInstance->mListenerList.equal_range(nextEvent->getEventType());

			std::multimap<EnumAndrickEvent, AndrickEventListener*>::iterator iter;
			for (iter = range.first; iter != range.second; ++iter)
			{
				if (iter->second)
				{
					iter->second->handleEvent(*nextEvent);
				}
				else
				{
					LoggerMaster::getUniversalLogger().logWarn(mspInstance->msCLASS_NAME, "The listener is null! Can't send this listener the event.");
				}
			}

			//Use object pool in the future.
			delete nextEvent;
			nextEvent = nullptr;
		}
	}
}