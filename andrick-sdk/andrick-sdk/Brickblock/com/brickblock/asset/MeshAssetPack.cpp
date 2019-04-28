#include "MeshAssetPack.h"

namespace bb
{
	andrick::Mesh* MeshAssetPack::mspTestMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspBarrelMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspQuadMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspSuzanneMesh = nullptr;
	andrick::Mesh* MeshAssetPack::mspCubeMesh = nullptr;

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
		mspCubeMesh = new andrick::Mesh("cube_mesh", andrick::FileLocation(msMESH_DIR, "cube_mesh", andrick::FileLocation::EnumExtensionType::OBJ_EXT));

		//registerAsset(mspTestMesh);
		//registerAsset(mspBarrelMesh);
		registerAsset(mspQuadMesh);
		//registerAsset(mspSuzanneMesh);
		//registerAsset(mspCubeMesh);

		return AssetPack::load();
	}
}