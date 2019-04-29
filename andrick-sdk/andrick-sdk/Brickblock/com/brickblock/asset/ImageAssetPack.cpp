#include "ImageAssetPack.h"

namespace bb
{
	andrick::Image* ImageAssetPack::mspBarrelImage = nullptr;
	andrick::Image* ImageAssetPack::mspLoveImage = nullptr;
	andrick::Image* ImageAssetPack::mspColorRampImage = nullptr;
	andrick::Image* ImageAssetPack::mspDefaultImage = nullptr;

	andrick::Image* ImageAssetPack::mspStoneImage = nullptr;
	andrick::Image* ImageAssetPack::mspStoneHeightMap = nullptr;
	andrick::Image* ImageAssetPack::mspStoneNormalMap = nullptr;

	andrick::Image* ImageAssetPack::mspMetalPlateHeightMap = nullptr;
	andrick::Image* ImageAssetPack::mspMetalPlateNormalMap = nullptr;

	andrick::Image* ImageAssetPack::mspMetalGrillHeightMap = nullptr;
	andrick::Image* ImageAssetPack::mspMetalGrillNormalMap = nullptr;

	andrick::Image* ImageAssetPack::mspBrickworkHeightMap = nullptr;
	andrick::Image* ImageAssetPack::mspBrickworkNormalMap = nullptr;

	andrick::Image* ImageAssetPack::mspConcreteHeightMap = nullptr;
	andrick::Image* ImageAssetPack::mspConcreteNormalMap = nullptr;

	std::array<andrick::Image*, 6> ImageAssetPack::mspNebulaCubeMapImages = std::array<andrick::Image*, 6>();
	std::array<andrick::Image*, 6> ImageAssetPack::mspCraterLakeCubeMapImages = std::array<andrick::Image*, 6>();
	std::array<andrick::Image*, 6> ImageAssetPack::mspDebugCubeMapImages = std::array<andrick::Image*, 6>();

	const andrick::DirectoryLocation ImageAssetPack::msIMAGE_DIR = andrick::DirectoryLocation("assets", "images", andrick::PathLocation::EnumPathType::RELATIVE_PATH);
	const andrick::DirectoryLocation ImageAssetPack::msCUBE_MAP_DIR = andrick::DirectoryLocation(msIMAGE_DIR, "cubemaps");

	ImageAssetPack::ImageAssetPack() : AssetPack("image_asset_pack")
	{

	}

	GLboolean ImageAssetPack::load()
	{
		if (mIsLoaded)
		{
			return mIsLoaded;
		}

		mspBarrelImage = new andrick::Image("barrel_image", andrick::FileLocation(msIMAGE_DIR, "model_barrel", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspLoveImage = new andrick::Image("love_image", andrick::FileLocation(msIMAGE_DIR, "test_img", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspColorRampImage = new andrick::Image("color_ramp_image", andrick::FileLocation(msIMAGE_DIR, "colRamp", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspDefaultImage = new andrick::Image("default_image", andrick::FileLocation(msIMAGE_DIR, "default", andrick::FileLocation::EnumExtensionType::PNG_EXT));

		mspStoneImage = new andrick::Image("stone_image", andrick::FileLocation(msIMAGE_DIR, "stone", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspStoneHeightMap = new andrick::Image("stone_height_map", andrick::FileLocation(msIMAGE_DIR, "stone_hm", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspStoneNormalMap = new andrick::Image("stone_normal_map", andrick::FileLocation(msIMAGE_DIR, "stone_nm", andrick::FileLocation::EnumExtensionType::PNG_EXT));

		mspMetalPlateHeightMap = new andrick::Image("metal_height_map", andrick::FileLocation(msIMAGE_DIR, "MetalPlate_hm", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspMetalPlateNormalMap = new andrick::Image("metal_normal_map", andrick::FileLocation(msIMAGE_DIR, "MetalPlate_nm", andrick::FileLocation::EnumExtensionType::PNG_EXT));

		mspMetalGrillHeightMap = new andrick::Image("metalgrill_height_map", andrick::FileLocation(msIMAGE_DIR, "MetalGrill_hm", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspMetalGrillNormalMap = new andrick::Image("metalgrill_normal_map", andrick::FileLocation(msIMAGE_DIR, "MetalGrill_nm", andrick::FileLocation::EnumExtensionType::PNG_EXT));

		mspBrickworkHeightMap = new andrick::Image("brick_height_map", andrick::FileLocation(msIMAGE_DIR, "brickwork_hm", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspBrickworkNormalMap = new andrick::Image("brick_normal_map", andrick::FileLocation(msIMAGE_DIR, "brickwork_nm", andrick::FileLocation::EnumExtensionType::PNG_EXT));

		mspConcreteHeightMap = new andrick::Image("concrete_height_map", andrick::FileLocation(msIMAGE_DIR, "Concrete_hm", andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspConcreteNormalMap = new andrick::Image("concrete_normal_map", andrick::FileLocation(msIMAGE_DIR, "Concrete_nm", andrick::FileLocation::EnumExtensionType::PNG_EXT));

		initCubeMap(mspNebulaCubeMapImages, andrick::DirectoryLocation(msCUBE_MAP_DIR, "nebula"), "nebula", andrick::FileLocation::EnumExtensionType::TGA_EXT);
		initCubeMap(mspCraterLakeCubeMapImages, andrick::DirectoryLocation(msCUBE_MAP_DIR, "craterlake"), "craterlake", andrick::FileLocation::EnumExtensionType::TGA_EXT);
		initCubeMap(mspDebugCubeMapImages, andrick::DirectoryLocation(msCUBE_MAP_DIR, "cube_debug"), "debug", andrick::FileLocation::EnumExtensionType::PNG_EXT);

		registerAsset(mspBarrelImage);
		registerAsset(mspLoveImage);
		registerAsset(mspColorRampImage);
		registerAsset(mspDefaultImage);
		registerAsset(mspStoneImage);
		registerAsset(mspStoneHeightMap);
		registerAsset(mspStoneNormalMap);
		registerAsset(mspMetalPlateHeightMap);
		registerAsset(mspMetalPlateNormalMap);
		registerAsset(mspMetalGrillHeightMap);
		registerAsset(mspMetalGrillNormalMap);
		registerAsset(mspBrickworkHeightMap);
		registerAsset(mspBrickworkNormalMap);
		registerAsset(mspConcreteHeightMap);
		registerAsset(mspConcreteNormalMap);


		registerCubeMap(mspNebulaCubeMapImages);
		registerCubeMap(mspCraterLakeCubeMapImages);
		registerCubeMap(mspDebugCubeMapImages);

		return AssetPack::load();
	}

	//The order goes: RIGHT, LEFT, TOP, BOTTOM, BACK, FRONT
	void ImageAssetPack::initCubeMap(std::array<andrick::Image*, 6>& cubeMapImages, const andrick::DirectoryLocation& dir, const std::string& baseName, 
		const andrick::FileLocation::EnumExtensionType& extensionType)
	{
		/*auto iter = cubeMapImages.begin();
		for (; iter != cubeMapImages.end(); ++iter)
		{
		}*/

		std::string fileName;

		GLuint i;
		for (i = 0; i < 6; ++i)
		{
			fileName = baseName + "_" + std::to_string(i);
			cubeMapImages[i] = new andrick::Image(fileName, andrick::FileLocation(dir, fileName, extensionType), andrick::EnumInternalFormatType::RGB);
		}
	}

	void ImageAssetPack::registerCubeMap(const std::array<andrick::Image*, 6>& cubeMapImages)
	{
		auto iter = cubeMapImages.begin();
		for (; iter != cubeMapImages.end(); ++iter)
		{
			registerAsset(*iter);
		}
	}
}