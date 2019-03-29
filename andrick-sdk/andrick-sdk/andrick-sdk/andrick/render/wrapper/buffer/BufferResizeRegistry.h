#ifndef ANDRICK_BUFFER_RESIZE_REGISTRY_H_
#define ANDRICK_BUFFER_RESIZE_REGISTRY_H_

#include "../buffer/fbo/FBOWrapper.h"
#include "../../../memory/TrackableObject.h"
#include "../../../memory/NonCopyable.h"
#include <set>

namespace andrick
{
	//Not responsible for memory management. Only responsible for keeping textures the size of the screen.
	class BufferResizeRegistry : public TrackableObject, NonCopyable
	{
	public:
		friend class AndrickCore;

		static inline GLboolean isInitialized() { return (mspInstance != nullptr); };

		static void resizeBuffers(const GLint& width, const GLint& height);
		static void addFBO(FBOWrapper* fbo);
		static void removeFBO(FBOWrapper* fbo);

	private:
		static const std::string msCLASS_NAME;

		static GLboolean init();
		static void cleanup();

		static BufferResizeRegistry* mspInstance;

		BufferResizeRegistry();
		virtual ~BufferResizeRegistry();

		std::set<FBOWrapper*> mFBOs;

		static GLboolean isInitWithWarn();
	};
}

#endif