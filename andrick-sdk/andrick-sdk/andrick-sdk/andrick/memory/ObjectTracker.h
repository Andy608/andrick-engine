#ifndef ANDRICK_OBJECT_TRACKER_H_
#define ANDRICK_OBJECT_TRACKER_H_

#include <map>
#include <glad/glad.h>
#include "../logger/Logger.h"

namespace andrick
{
	struct MemoryRecord
	{
		inline MemoryRecord(GLuint id, size_t memorySize) : mId(id), mMemorySize(memorySize) {};

		GLuint mId;
		size_t mMemorySize;
	};

	class ObjectTracker
	{
		friend class AndrickCore;
		friend class TrackableObject;

	public:
		void addRecord(void* ptr, size_t memorySize);
		void removeRecord(void* ptr);

		void printRecords(const Logger& logger);

	private:
		static ObjectTracker* smpObjectTracker;
		static GLuint smNextId;

		static void init();
		static void cleanup();

		std::map<void*, MemoryRecord> mRecords;

		ObjectTracker();
		inline virtual ~ObjectTracker();
	};
}

#endif