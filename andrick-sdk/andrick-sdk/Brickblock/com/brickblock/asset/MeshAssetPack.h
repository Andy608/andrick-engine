#ifndef BB_MESH_ASSET_PACK_H_
#define BB_MESH_ASSET_PACK_H_

#include <andrick/asset/pack/AssetPack.h>
#include <andrick/asset/mesh/Mesh.h>

namespace bb
{
	class MeshAssetPack : public andrick::AssetPack
	{
		friend class AssetLoader;

	public:
		static andrick::Mesh* mspTestMesh;
		static andrick::Mesh* mspBarrelMesh;
		static andrick::Mesh* mspQuadMesh;
		static andrick::Mesh* mspSuzanneMesh;

		//Only used for cubemaps right now so this mesh doesn't have normals or texcoords cuz I'm lazy.
		static andrick::Mesh* mspCubeMesh;

	protected:
		virtual GLboolean load() override;

	private:
		//In the future have dictionary class that holds all the directory locations
		static const andrick::DirectoryLocation msMESH_DIR;

		MeshAssetPack();
		inline virtual ~MeshAssetPack() {};
	};
}

#endif