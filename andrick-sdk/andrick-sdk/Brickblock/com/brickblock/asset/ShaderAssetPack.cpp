#include "ShaderAssetPack.h"

namespace bb
{
	andrick::Shader* ShaderAssetPack::mspTestVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspTestFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspTestProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspLightSourceVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspLightSourceFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspLightSourceProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspFractalVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspFractalFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspFractalProgram = nullptr;

	const andrick::DirectoryLocation ShaderAssetPack::msSHADER_DIR = andrick::DirectoryLocation("assets", "shaders", andrick::PathLocation::EnumPathType::RELATIVE_PATH);
	const andrick::DirectoryLocation ShaderAssetPack::msVS_DIR = andrick::DirectoryLocation(msSHADER_DIR, "vs");
	const andrick::DirectoryLocation ShaderAssetPack::msGS_DIR = andrick::DirectoryLocation(msSHADER_DIR, "gs");
	const andrick::DirectoryLocation ShaderAssetPack::msFS_DIR = andrick::DirectoryLocation(msSHADER_DIR, "fs");

	ShaderAssetPack::ShaderAssetPack() : AssetPack("shader_asset_pack")
	{

	}

	GLboolean ShaderAssetPack::load()
	{
		if (mIsLoaded)
		{
			return mIsLoaded;
		}

		mspTestVS = new andrick::Shader("test_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msVS_DIR, "test_vs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspTestFS = new andrick::Shader("test_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msFS_DIR, "test_fs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspTestProgram = new andrick::ShaderProgram("test_shaderprogram");
		mspTestProgram->addShader(*mspTestVS);
		mspTestProgram->addShader(*mspTestFS);

		mspLightSourceVS = new andrick::Shader("light_source_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msVS_DIR, "light_source_vs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspLightSourceFS = new andrick::Shader("light_source_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msFS_DIR, "light_source_fs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspLightSourceProgram = new andrick::ShaderProgram("light_source_shaderprogram");
		mspLightSourceProgram->addShader(*mspLightSourceVS);
		mspLightSourceProgram->addShader(*mspLightSourceFS);

		mspFractalVS = new andrick::Shader("fractal_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msVS_DIR, "fractal_vs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspFractalFS = new andrick::Shader("fractal_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msFS_DIR, "fractal_fs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspFractalProgram = new andrick::ShaderProgram("fractal_shaderprogram");
		mspFractalProgram->addShader(*mspFractalVS);
		mspFractalProgram->addShader(*mspFractalFS);

		registerAsset(mspTestVS);
		registerAsset(mspTestFS);
		registerAsset(mspTestProgram);

		registerAsset(mspLightSourceVS);
		registerAsset(mspLightSourceFS);
		registerAsset(mspLightSourceProgram);

		registerAsset(mspFractalVS);
		registerAsset(mspFractalFS);
		registerAsset(mspFractalProgram);

		return AssetPack::load();
	}
}