#include "ObjectTracker.h"
using namespace andrick;

GLuint ObjectTracker::smNextId = 0;
ObjectTracker* ObjectTracker::smpObjectTracker = nullptr;

void ObjectTracker::init()
{
	if (!smpObjectTracker)
	{
		smpObjectTracker = new ObjectTracker();
	}
}

void ObjectTracker::cleanup()
{
	if (smpObjectTracker)
	{
		delete smpObjectTracker;
		smpObjectTracker = nullptr;
	}
}

ObjectTracker::ObjectTracker()
{

}

ObjectTracker::~ObjectTracker()
{

}

void ObjectTracker::addRecord(void *ptr, size_t memorySize)
{
	auto iter = mRecords.find(ptr);

	if (iter == mRecords.end())
	{
		MemoryRecord record = MemoryRecord(smNextId, memorySize);
		mRecords.insert(std::make_pair(ptr, record));
		++smNextId;
	}
}

void ObjectTracker::removeRecord(void *ptr)
{
	auto iter = mRecords.find(ptr);
	if (iter != mRecords.end())
	{
		mRecords.erase(iter);
	}
}

void ObjectTracker::printRecords(const Logger& logger)
{
	static std::string className = "ObjectTracker";
	logger.logTrace(className, "Remaining Memory Allocations:\n");

	std::map<void*, MemoryRecord>::iterator iter = mRecords.begin();
	for (; iter != mRecords.end(); ++iter)
	{
		logger.logTrace(className, "Id: " + std::to_string(iter->second.mId) + " Size: " + std::to_string(iter->second.mMemorySize));
	}
}