#ifndef BB_MESH_ASSET_PACK_H_
#define BB_MESH_ASSET_PACK_H_

#include <andrick/asset/pack/AssetPack.h>
#include <andrick/asset/mesh/Mesh.h>

//For now adding texture here
#include <andrick/asset/texture/Texture.h>

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

		//This will be in a TextureAssetPack
		static andrick::Texture* mspBarrelTexture;
		static andrick::Texture* mspLoveTexture;
		static andrick::Texture* mspDefaultTexture;

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