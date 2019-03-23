#ifndef ANDRICK_SHADER_H_
#define ANDRICK_SHADER_H_

#include "../Asset.h"
#include "../../filesystem/path/file/FileLocation.h"

namespace andrick
{
	class Shader : public Asset
	{
		friend class ShaderProgram;

	public:
		enum class EnumShaderType : GLuint
		{
			VERTEX,
			GEOMETRY,
			FRAGMENT
		};

		Shader(const std::string& assetID, const EnumShaderType& shaderType, FileLocation shaderLocation);
		virtual ~Shader();

		virtual GLboolean load() override;
		virtual GLboolean unload() override;

		inline const EnumShaderType& getShaderType() const { return mSHADER_TYPE; };
		inline const FileLocation& getShaderLocation() const { return mShaderLocation; };

	private:
		static const std::string msCLASS_NAME;

		const EnumShaderType& mSHADER_TYPE;
		FileLocation mShaderLocation;
		std::string mShaderCode;
		GLint mShaderID;

		GLboolean extractSourceFromFile();
		void compile();
	};
}

#endif