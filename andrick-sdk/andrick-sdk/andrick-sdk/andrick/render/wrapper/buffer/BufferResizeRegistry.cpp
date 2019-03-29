#include "BufferResizeRegistry.h"
#include "../../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string BufferResizeRegistry::msCLASS_NAME = "BufferResizeRegistry";
	BufferResizeRegistry* BufferResizeRegistry::mspInstance = nullptr;

	BufferResizeRegistry::BufferResizeRegistry() :
		mFBOs(std::set<FBOWrapper*>())
	{

	}

	BufferResizeRegistry::~BufferResizeRegistry()
	{
		mFBOs.clear();
	}

	GLboolean BufferResizeRegistry::init()
	{
		GLboolean success = GL_FALSE;

		if (!mspInstance)
		{
			mspInstance = new BufferResizeRegistry();
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Initializing " + msCLASS_NAME + ".");
			success = (mspInstance != nullptr);
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, msCLASS_NAME + " is already initialized.");
		}

		return success;
	}

	void BufferResizeRegistry::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	void BufferResizeRegistry::resizeBuffers(const GLint& width, const GLint& height)
	{
		if (!isInitWithWarn())
		{
			return;
		}

		auto iter = mspInstance->mFBOs.begin();
		for (; iter != mspInstance->mFBOs.end(); ++iter)
		{
			(*iter)->resizeBuffers(width, height);
		}
	}

	void BufferResizeRegistry::addFBO(FBOWrapper* fbo)
	{
		if (!isInitWithWarn())
		{
			return;
		}

		//In the future use binary search with vector to add texture by id
		mspInstance->mFBOs.insert(fbo);
	}

	void BufferResizeRegistry::removeFBO(FBOWrapper* fbo)
	{
		if (isInitWithWarn())
		{
			return;
		}

		//In the future use binary search with vector to remove texture by id
		auto iter = mspInstance->mFBOs.begin();
		for (; iter != mspInstance->mFBOs.end(); ++iter)
		{
			if ((*iter)->getID() == fbo->getID())
			{
				mspInstance->mFBOs.erase(iter);
				break;
			}
		}
	}

	GLboolean BufferResizeRegistry::isInitWithWarn()
	{
		GLboolean success = GL_TRUE;

		if (!mspInstance)
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, msCLASS_NAME + " is not initialized. Cannot resize textures.");
			success = GL_FALSE;
		}
		
		return success;
	}
}