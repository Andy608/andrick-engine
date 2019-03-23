#ifndef ANDRICK_ASSET_MANAGER_H_
#define ANDRICK_ASSET_MANAGER_H_

#include <glad/glad.h>
#include "../memory/TrackableObject.h"
#include "../memory/NonCopyable.h"
#include "pack/AssetPack.h"
#include "Asset.h"

namespace andrick
{
	class AssetManager : public TrackableObject, NonCopyable
	{
		friend class AndrickCore;

	public:
		//static GLboolean addAssetContainer(std::shared_ptr<AssetContainer> container);
		static GLboolean registerAssetPack(AssetPack* assetPack);

		//static Asset* getAsset(std::string containerID, std::string assetID);

		//In the future maybe load/unload by containerID
		//Also in the future maybe this gets called in a loop and runs in a different thread.
		//This way the main thread can ask for the percentage the loading is at.
		static void loadAssets();
		static void unloadAssets();

	private:
		static const std::string msCLASS_NAME;
		static AssetManager* mspInstance;


		static GLboolean init();
		static void cleanup();

		AssetManager();
		~AssetManager();

		//Maps dont keep order of insertion :(
		//Maybe have a map for faster look up in the future if needed
		//std::map<std::string, std::shared_ptr<AssetContainer>> mAssetContainerMap;
		std::vector<AssetPack*> mAssetPacks;
	};
}

#endif