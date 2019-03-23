#include "AssetPack.h"
#include "../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string AssetPack::msCLASS_NAME = "AssetPack";

	AssetPack::AssetPack(std::string assetID) :
		Asset(assetID)
	{

	}

	AssetPack::~AssetPack()
	{
		if (mIsLoaded)
		{
			auto iter = mAssets.begin();
			for (; iter != mAssets.end(); ++iter)
			{
				delete *iter;
			}

			mAssets.clear();
			mIsLoaded = GL_FALSE;
		}
	}

	void AssetPack::registerAsset(Asset* asset)
	{
		if (asset->isRegistered())
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "Resource is already registered.");
		}
		else
		{
			//Add resource to pack.
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Registering: " + asset->getID());
			mAssets.push_back(asset);

			//Set the resource to be registered.
			asset->mIsRegistered = GL_TRUE;
		}
	}

	GLboolean AssetPack::load()
	{
		auto iter = mAssets.begin();
		for (; iter != mAssets.end(); ++iter)
		{
			(*iter)->load();
		}

		mIsLoaded = GL_TRUE;
		return mIsLoaded;//For now
	}

	GLboolean AssetPack::unload()
	{
		auto iter = mAssets.begin();
		for (; iter != mAssets.end(); ++iter)
		{
			(*iter)->unload();
		}

		mIsLoaded = GL_FALSE;
		return mIsLoaded;//For now
	}
}