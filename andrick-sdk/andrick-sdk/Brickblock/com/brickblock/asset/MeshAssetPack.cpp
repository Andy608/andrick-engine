#include "MeshAssetPack.h"

namespace bb
{
	andrick::Mesh* MeshAssetPack::mspTestMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspBarrelMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspQuadMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspSuzanneMesh = nullptr;

	andrick::Texture* MeshAssetPack::mspBarrelTexture = nullptr;
	andrick::Texture* MeshAssetPack::mspLoveTexture = nullptr;
	andrick::Texture* MeshAssetPack::mspDefaultTexture = nullptr;

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
		mspSuzanneMesh = new andrick::Mesh("suzanne_mesh", andrick::FileLocation(msMESH_DIR, "suzanne", andrick::FileLocation::EnumExtensionType::OBJ_EXT));

		mspBarrelTexture = new andrick::Texture("barrel_texture", andrick::FileLocation("assets/textures", "model_barrel", andrick::FileLocation::EnumPathType::RELATIVE_PATH, andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspLoveTexture = new andrick::Texture("love_texture", andrick::FileLocation("assets/textures", "test_img", andrick::FileLocation::EnumPathType::RELATIVE_PATH, andrick::FileLocation::EnumExtensionType::PNG_EXT));
		mspDefaultTexture = new andrick::Texture("default_texture", andrick::FileLocation("assets/textures", "default", andrick::FileLocation::EnumPathType::RELATIVE_PATH, andrick::FileLocation::EnumExtensionType::PNG_EXT));

		registerAsset(mspTestMesh);
		registerAsset(mspBarrelMesh);
		registerAsset(mspQuadMesh);
		registerAsset(mspSuzanneMesh);

		registerAsset(mspBarrelTexture);
		registerAsset(mspLoveTexture);
		registerAsset(mspDefaultTexture);

		return AssetPack::load();
	}
}