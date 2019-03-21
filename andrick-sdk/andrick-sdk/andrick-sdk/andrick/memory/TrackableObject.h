#ifndef ANDRICK_OBJECT_H_
#define ANDRICK_OBJECT_H_

#include <iostream>
#include <string>

namespace andrick
{
	class TrackableObject
	{
	public:
		inline TrackableObject() {};
		inline virtual ~TrackableObject() {};

		inline void* operator new(std::size_t size) { return createMemory(size); };
		inline void operator delete(void* ptr) { freeMemory(ptr); };
		inline void* operator new[](std::size_t size) { return createMemory(size); };
		inline void operator delete[](void* ptr) { freeMemory(ptr); };

		inline void* operator new(std::size_t size, void* ptr) { return ptr; };
		inline void operator delete(void* ptr, void* ptr2) {};
		inline void* operator new[](std::size_t size, void* ptr) { return ptr; };
		inline void operator delete[](void* ptr, void* ptr2) {};

	private:
		static void* createMemory(std::size_t size);
		static void freeMemory(void* ptr);
	};
}

#endif