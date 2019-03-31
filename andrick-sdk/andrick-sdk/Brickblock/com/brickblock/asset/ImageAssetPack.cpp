#include "ImageAssetPack.h"

namespace bb
{
	andrick::Image* ImageAssetPack::mspBarrelImage = nullptr;
	andrick::Image* ImageAssetPack::mspLoveImage = nullptr;
	andrick::Image* ImageAssetPack::mspColorRampImage = nullptr;
	andrick::Image* ImageAssetPack::mspDefaultImage = nullptr;

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

		initCubeMap(mspNebulaCubeMapImages, andrick::DirectoryLocation(msCUBE_MAP_DIR, "nebula"), "nebula", andrick::FileLocation::EnumExtensionType::TGA_EXT);
		initCubeMap(mspCraterLakeCubeMapImages, andrick::DirectoryLocation(msCUBE_MAP_DIR, "craterlake"), "craterlake", andrick::FileLocation::EnumExtensionType::TGA_EXT);
		initCubeMap(mspDebugCubeMapImages, andrick::DirectoryLocation(msCUBE_MAP_DIR, "debug"), "debug", andrick::FileLocation::EnumExtensionType::PNG_EXT);

		registerAsset(mspBarrelImage);
		registerAsset(mspLoveImage);
		registerAsset(mspColorRampImage);
		registerAsset(mspDefaultImage);
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