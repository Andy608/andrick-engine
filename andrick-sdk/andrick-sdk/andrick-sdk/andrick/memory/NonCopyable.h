#ifndef ANDRICK_NONCOPYABLE_H_
#define ANDRICK_NONCOPYABLE_H_

namespace andrick
{
	class NonCopyable
	{
	public:
		inline NonCopyable() {};
		inline virtual ~NonCopyable() {};
		NonCopyable(const NonCopyable&) = delete;
		void operator=(const NonCopyable&) = delete;
	};
}

#endif