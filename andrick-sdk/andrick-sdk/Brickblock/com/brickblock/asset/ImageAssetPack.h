#ifndef BB_IMAGE_ASSET_PACK_H_
#define BB_IMAGE_ASSET_PACK_H_

#include <andrick/asset/pack/AssetPack.h>
#include <andrick/asset/image/Image.h>
#include <array>

namespace bb
{
	class ImageAssetPack : public andrick::AssetPack
	{
		friend class AssetLoader;

	public:
		static andrick::Image* mspBarrelImage;
		static andrick::Image* mspLoveImage;
		static andrick::Image* mspColorRampImage;
		static andrick::Image* mspDefaultImage;

		static andrick::Image* mspStoneImage;
		static andrick::Image* mspStoneHeightMap;
		static andrick::Image* mspStoneNormalMap;

		static std::array<andrick::Image*, 6> mspNebulaCubeMapImages;
		static std::array<andrick::Image*, 6> mspCraterLakeCubeMapImages;
		static std::array<andrick::Image*, 6> mspDebugCubeMapImages;

	protected:
		virtual GLboolean load() override;

	private:
		//In the future have dictionary class that holds all the directory locations
		static const andrick::DirectoryLocation msIMAGE_DIR;
		static const andrick::DirectoryLocation msCUBE_MAP_DIR;

		ImageAssetPack();
		inline virtual ~ImageAssetPack() {};

		void initCubeMap(std::array<andrick::Image*, 6>& cubeMapImages, const andrick::DirectoryLocation& dir, const std::string& baseName, const andrick::FileLocation::EnumExtensionType& extensionType);
		void registerCubeMap(const std::array<andrick::Image*, 6>& cubeMapImages);
	};
}

#endif