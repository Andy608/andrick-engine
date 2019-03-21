#include "TrackableObject.h"
#include "ObjectTracker.h"
using namespace andrick;

void* TrackableObject::createMemory(std::size_t size)
{
	void* ptr = malloc(size);
	ObjectTracker::smpObjectTracker->addRecord(ptr, size);
	return ptr;
}

void TrackableObject::freeMemory(void* ptr)
{
	ObjectTracker::smpObjectTracker->removeRecord(ptr);
	free(ptr);
}