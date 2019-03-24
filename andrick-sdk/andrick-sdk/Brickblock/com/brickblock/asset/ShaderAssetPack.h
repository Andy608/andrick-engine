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

	protected:
		virtual GLboolean load() override;

	private:
		//In the future have dictionary class that holds all the directory locations
		static const andrick::DirectoryLocation msSHADER_DIR;

		ShaderAssetPack();
		inline virtual ~ShaderAssetPack() {};
	};
}

#endif