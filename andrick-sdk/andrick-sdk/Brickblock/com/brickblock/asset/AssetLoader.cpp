#include "AssetLoader.h"
#include <andrick/asset/AssetManager.h>
#include <andrick/logger/LoggerMaster.h>

#include <andrick/filesystem/path/directory/DirectoryLocation.h>

#include "ShaderAssetPack.h"
#include "MeshAssetPack.h"

#include <set>

namespace bb
{
	const std::string AssetLoader::msCLASS_NAME = "AssetLoader";
	AssetLoader* AssetLoader::mspInstance = nullptr;

	GLboolean AssetLoader::init()
	{
		if (!mspInstance)
		{
			mspInstance = new AssetLoader();

		}

		return (mspInstance != nullptr);
	}

	void AssetLoader::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	AssetLoader::AssetLoader() : mIsLoaded(GL_FALSE)
	{

	}

	void AssetLoader::initAssets() const
	{
		if (mIsLoaded)
		{
			andrick::LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "Assets are already loaded!");
		}
		else
		{
			andrick::AssetManager::registerAssetPack(new ShaderAssetPack());
			andrick::AssetManager::registerAssetPack(new MeshAssetPack());
			//andrick::AssetManager::registerAssetPack(new BlockModelList());
		}
	}
}