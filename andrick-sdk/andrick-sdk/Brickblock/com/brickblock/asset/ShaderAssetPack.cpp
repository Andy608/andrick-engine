#include "ShaderAssetPack.h"

namespace bb
{
	andrick::Shader* ShaderAssetPack::mspTestVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspTestFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspTestProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspLightSourceVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspLightSourceFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspLightSourceProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspJuliaFractalVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspJuliaFractalFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspJuliaFractalProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspMandlebrotFractalVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspMandlebrotFractalFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspMandlebrotFractalProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspPhongShadingVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspPhongShadingFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspPhongShadingProgram = nullptr;

	andrick::Shader* ShaderAssetPack::mspTextureVS = nullptr;
	andrick::Shader* ShaderAssetPack::mspTextureFS = nullptr;
	andrick::ShaderProgram* ShaderAssetPack::mspTextureProgram = nullptr;

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

		mspJuliaFractalVS = new andrick::Shader("julia_fractal_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msVS_DIR, "juliaFractal_vs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspJuliaFractalFS = new andrick::Shader("julia_fractal_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msFS_DIR, "juliaFractal_fs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspJuliaFractalProgram = new andrick::ShaderProgram("julia_fractal_shaderprogram");
		mspJuliaFractalProgram->addShader(*mspJuliaFractalVS);
		mspJuliaFractalProgram->addShader(*mspJuliaFractalFS);

		mspMandlebrotFractalVS = new andrick::Shader("mandlebrot_fractal_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msVS_DIR, "mandlebrotFractal_vs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspMandlebrotFractalFS = new andrick::Shader("mandlebrot_fractal_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msFS_DIR, "mandlebrotFractal_fs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspMandlebrotFractalProgram = new andrick::ShaderProgram("mandlebrot_fractal_shaderprogram");
		mspMandlebrotFractalProgram->addShader(*mspMandlebrotFractalVS);
		mspMandlebrotFractalProgram->addShader(*mspMandlebrotFractalFS);

		mspPhongShadingVS = new andrick::Shader("phong_shading_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msVS_DIR, "phong_shading_vs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspPhongShadingFS = new andrick::Shader("phong_shading_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msFS_DIR, "phong_shading_fs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspPhongShadingProgram = new andrick::ShaderProgram("phong_shading_shaderprogram");
		mspPhongShadingProgram->addShader(*mspPhongShadingVS);
		mspPhongShadingProgram->addShader(*mspPhongShadingFS);

		mspTextureVS = new andrick::Shader("texture_vertex_shader", andrick::Shader::EnumShaderType::VERTEX, andrick::FileLocation(msVS_DIR, "texture_vs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspTextureFS = new andrick::Shader("texture_fragment_shader", andrick::Shader::EnumShaderType::FRAGMENT, andrick::FileLocation(msFS_DIR, "texture_fs", andrick::FileLocation::EnumExtensionType::GLSL_EXT));
		mspTextureProgram = new andrick::ShaderProgram("texture_shaderprogram");
		mspTextureProgram->addShader(*mspTextureVS);
		mspTextureProgram->addShader(*mspTextureFS);

		registerAsset(mspTestVS);
		registerAsset(mspTestFS);
		registerAsset(mspTestProgram);

		registerAsset(mspLightSourceVS);
		registerAsset(mspLightSourceFS);
		registerAsset(mspLightSourceProgram);

		registerAsset(mspJuliaFractalVS);
		registerAsset(mspJuliaFractalFS);
		registerAsset(mspJuliaFractalProgram);

		registerAsset(mspMandlebrotFractalVS);
		registerAsset(mspMandlebrotFractalFS);
		registerAsset(mspMandlebrotFractalProgram);

		registerAsset(mspPhongShadingVS);
		registerAsset(mspPhongShadingFS);
		registerAsset(mspPhongShadingProgram);

		registerAsset(mspTextureVS);
		registerAsset(mspTextureFS);
		registerAsset(mspTextureProgram);

		return AssetPack::load();
	}
}