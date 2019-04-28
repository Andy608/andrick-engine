#ifndef BB_SHADER_ASSET_PACK_H_
#define BB_SHADER_ASSET_PACK_H_

#include <andrick/asset/pack/AssetPack.h>
#include <andrick/asset/shader/Shader.h>
#include <andrick/asset/shader/ShaderProgram.h>

namespace bb
{
	class ShaderAssetPack : public andrick::AssetPack
	{
		friend class AssetLoader;

	public:
		static andrick::Shader* mspTestVS;
		static andrick::Shader* mspTestFS;
		static andrick::ShaderProgram* mspTestProgram;

		static andrick::Shader* mspLightSourceVS;
		static andrick::Shader* mspLightSourceFS;
		static andrick::ShaderProgram* mspLightSourceProgram;

		static andrick::Shader* mspJuliaFractalVS;
		static andrick::Shader* mspJuliaFractalFS;
		static andrick::ShaderProgram* mspJuliaFractalProgram;

		static andrick::Shader* mspMandlebrotFractalVS;
		static andrick::Shader* mspMandlebrotFractalFS;
		static andrick::ShaderProgram* mspMandlebrotFractalProgram;

		static andrick::Shader* mspPhongShadingVS;
		static andrick::Shader* mspPhongShadingFS;
		static andrick::ShaderProgram* mspPhongShadingProgram;

		static andrick::Shader* mspTextureVS;
		static andrick::Shader* mspTextureFS;
		static andrick::ShaderProgram* mspTextureProgram;

		static andrick::Shader* mspCubeMapVS;
		static andrick::Shader* mspCubeMapFS;
		static andrick::ShaderProgram* mspCubeMapProgram;

		static andrick::Shader* mspSkyboxVS;
		static andrick::Shader* mspSkyboxFS;
		static andrick::ShaderProgram* mspSkyboxProgram;

		static andrick::Shader* mspPomVS;
		static andrick::Shader* mspPomFS;
		static andrick::ShaderProgram* mspPomProgram;

	protected:
		virtual GLboolean load() override;

	private:
		//In the future have dictionary class that holds all the directory locations
		static const andrick::DirectoryLocation msSHADER_DIR;
		static const andrick::DirectoryLocation msVS_DIR;
		static const andrick::DirectoryLocation msGS_DIR;
		static const andrick::DirectoryLocation msFS_DIR;

		ShaderAssetPack();
		inline virtual ~ShaderAssetPack() {};
	};
}

#endif