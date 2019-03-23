#ifndef ANDRICK_ASSET_PACK_H_
#define ANDRICK_ASSET_PACK_H_

#include "../Asset.h"
#include "../../filesystem/path/directory/DirectoryLocation.h"
#include <vector>
#include <memory>

namespace andrick
{
	class AssetPack : public Asset
	{
		friend class AssetManager;

	public:
		AssetPack(std::string assetID);
		virtual ~AssetPack();

		void registerAsset(Asset* asset);

	protected:
		virtual GLboolean load() override;
		virtual GLboolean unload() override;

	private:
		static const std::string msCLASS_NAME;
		std::vector<Asset*> mAssets;
	};
}

#endif