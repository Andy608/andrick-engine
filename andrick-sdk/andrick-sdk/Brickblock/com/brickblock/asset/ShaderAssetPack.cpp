#include "ShaderAssetPack.h"

namespace bb
{
	andrick::Shader* ShaderAssetPack::mspTestVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspTestFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspTestProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspLightSourceVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspLightSourceFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspLightSourceProgram = nullptr;

	andrick::Mesh* ShaderAssetPack::mspTestMesh = nullptr;

	const andrick::DirectoryLocation ShaderAssetPack::msSHADER_DIR = andrick::DirectoryLocation("assets", "shaders", andrick::PathLocation::EnumPathType::RELATIVE_PATH);

	ShaderAssetPack::ShaderAssetPack() : AssetPack("shader_asset_pack")
	{

	}

	GLboolean ShaderAssetPack::load()
	{
		if (mIsLoaded)
		{
			return mIsLoaded;
		}

		mspTestVS = new andrick::Shader("test_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msSHADER_DIR, "test_vs", andrick::FileLocation::EnumExtensionType::VS_EXT));
		mspTestFS = new andrick::Shader("test_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msSHADER_DIR, "test_fs", andrick::FileLocation::EnumExtensionType::FS_EXT));
		mspTestProgram = new andrick::ShaderProgram("test_shaderprogram");
		mspTestProgram->addShader(*mspTestVS);
		mspTestProgram->addShader(*mspTestFS);

		mspLightSourceVS = new andrick::Shader("light_source_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msSHADER_DIR, "light_source", andrick::FileLocation::EnumExtensionType::VS_EXT));
		mspLightSourceFS = new andrick::Shader("light_source_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msSHADER_DIR, "light_source", andrick::FileLocation::EnumExtensionType::FS_EXT));
		mspLightSourceProgram = new andrick::ShaderProgram("light_source_shaderprogram");
		mspLightSourceProgram->addShader(*mspLightSourceVS);
		mspLightSourceProgram->addShader(*mspLightSourceFS);

		mspTestMesh = new andrick::Mesh("test_mesh", andrick::FileLocation("assets/meshes", "test_mesh", andrick::FileLocation::EnumPathType::RELATIVE_PATH, andrick::FileLocation::EnumExtensionType::OBJ_EXT));

		registerAsset(mspTestVS);
		registerAsset(mspTestFS);
		registerAsset(mspTestProgram);

		registerAsset(mspLightSourceVS);
		registerAsset(mspLightSourceFS);
		registerAsset(mspLightSourceProgram);

		registerAsset(mspTestMesh);

		return AssetPack::load();
	}
}