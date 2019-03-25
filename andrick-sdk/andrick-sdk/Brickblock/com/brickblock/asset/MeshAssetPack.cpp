#include "MeshAssetPack.h"

namespace bb
{
	andrick::Mesh* MeshAssetPack::mspTestMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspBarrelMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspQuadMesh = nullptr;

	andrick::Texture* MeshAssetPack::mspBarrelTexture = nullptr;
	andrick::Texture* MeshAssetPack::mspLoveTexture = nullptr;
	andrick::Texture* MeshAssetPack::mspColorRampTexture = nullptr;


	const andrick::DirectoryLocation MeshAssetPack::msMESH_DIR = andrick::DirectoryLocation("assets", "meshes", andrick::PathLocation::EnumPathType::RELATIVE_PATH);

	MeshAssetPack::MeshAssetPack() : AssetPack("mesh_asset_pack")
	{

	}

	GLboolean MeshAssetPack::load()
	{
		if (mIsLoaded)
		{
			return mIsLoaded;
		}

		mspTestMesh = new andrick::Mesh("test_mesh", andrick::FileLocation(msMESH_DIR, "test_mesh", andrick::FileLocation::EnumExtensionType::OBJ_EXT));
		mspBarrelMesh = new andrick::Mesh("barrel_mesh", andrick::FileLocation(msMESH_DIR, "barrel", andrick::FileLocation::EnumExtensionType::OBJ_EXT));
		mspQuadMesh = new andrick::Mesh("quad_mesh", andrick::FileLocation(msMESH_DIR, "test_plane", andrick::FileLocation::EnumExtensionType::OBJ_EXT));

		mspBarrelTexture = new andrick::Texture("barrel_texture", andrick::FileLocation("assets/textures", "model_barrel", andrick::FileLocation::EnumPathType::RELATIVE_PATH, andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspLoveTexture = new andrick::Texture("love_texture", andrick::FileLocation("assets/textures", "test_img", andrick::FileLocation::EnumPathType::RELATIVE_PATH, andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspColorRampTexture = new andrick::Texture("color_ramp_texture", andrick::FileLocation("assets/textures", "colRamp", andrick::FileLocation::EnumPathType::RELATIVE_PATH, andrick::FileLocation::EnumExtensionType::PNG_EXT));

		registerAsset(mspTestMesh);
		registerAsset(mspBarrelMesh);
		registerAsset(mspQuadMesh);

		registerAsset(mspBarrelTexture);
		registerAsset(mspLoveTexture);
		registerAsset(mspColorRampTexture);

		return AssetPack::load();
	}
}