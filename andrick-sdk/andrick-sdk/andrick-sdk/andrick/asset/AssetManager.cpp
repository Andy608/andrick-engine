#include "AssetManager.h"
#include "../logger/LoggerMaster.h"

namespace andrick
{
	const std::string AssetManager::msCLASS_NAME = "AssetManager";
	AssetManager* AssetManager::mspInstance = nullptr;

	GLboolean AssetManager::registerAssetPack(AssetPack* container)
	{
		GLboolean success;

		if (!mspInstance)
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, msCLASS_NAME + " is not initialized yet! Did you forget to call init?");
			success = GL_FALSE;
		}
		else
		{
			auto iter = mspInstance->mAssetPacks.begin();
			for (; iter != mspInstance->mAssetPacks.end(); ++iter)
			{
				if ((*iter)->getID() == container->getID())
				{
					LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "AssetPack with ID: \'" + container->getID() + "\' is already registered.");
					success = GL_FALSE;
					return success;
				}
			}

			mspInstance->mAssetPacks.push_back(container);
			success = GL_TRUE;
		}

		return success;
	}

	GLboolean AssetManager::init()
	{
		GLboolean success;

		if (mspInstance)
		{
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Unable to initialize AssetManager.");
			success = GL_FALSE;
		}
		else
		{
			mspInstance = new AssetManager();
			LoggerMaster::getUniversalLogger().logInfo(msCLASS_NAME, "Initializing AssetManager.");
			success = GL_TRUE;
		}

		return success;
	}

	void AssetManager::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	AssetManager::AssetManager()
	{

	}

	AssetManager::~AssetManager()
	{
		auto iter = mspInstance->mAssetPacks.begin();
		for (; iter != mspInstance->mAssetPacks.end(); ++iter)
		{
			delete *iter;
		}

		mspInstance->mAssetPacks.clear();
	}

	void AssetManager::loadAssets()
	{
		if (mspInstance)
		{
			auto iter = mspInstance->mAssetPacks.begin();
			for (; iter != mspInstance->mAssetPacks.end(); ++iter)
			{
				(*iter)->load();
			}
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, msCLASS_NAME + " is not initialized yet! Did you forget to call init?");
		}
	}

	void AssetManager::unloadAssets()
	{
		if (mspInstance)
		{
			auto iter = mspInstance->mAssetPacks.begin();
			for (; iter != mspInstance->mAssetPacks.end(); ++iter)
			{
				(*iter)->unload();
			}
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, msCLASS_NAME + " is not initialized yet! Did you forget to call init?");
		}
	}
}