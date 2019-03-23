#ifndef ANDRICK_SHADER_PROGRAM_H_
#define ANDRICK_SHADER_PROGRAM_H_

#include "../Asset.h"
#include "Shader.h"

namespace andrick
{
	class ShaderProgram : public Asset
	{
	public:
		ShaderProgram(const std::string& assetID);
		~ShaderProgram();

		inline const ShaderProgram& operator=(const ShaderProgram& another) { return another; };

		virtual GLboolean load() override;
		virtual GLboolean unload() override;

		void use() const;
		void addShader(Shader& shader);

		void loadInt(const std::string& uniformName, GLint data) const;
		void loadFloat(const std::string& uniformName, GLfloat data) const;
		void loadMat4(const std::string& uniformName, GLboolean transposeMatrix, const GLfloat* matrixPtr) const;

	private:
		static const std::string msCLASS_NAME;
		GLint mProgramID;
		std::vector<Shader*> mActiveShaders;

		GLuint getUniformID(std::string uniformName) const;
		void compile();
	};
}

#endif