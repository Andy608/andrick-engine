#include "ShaderProgram.h"
#include "../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string ShaderProgram::msCLASS_NAME = "ShaderProgram";

	ShaderProgram::ShaderProgram(const std::string& assetID) :
		Asset(assetID),
		mProgramID(0)
	{

	}

	ShaderProgram::~ShaderProgram()
	{
		if (mIsLoaded)
		{
			unload();
		}
	}

	GLboolean ShaderProgram::load()
	{
		if (!mIsLoaded)
		{
			compile();
			mIsLoaded = GL_TRUE;
		}

		return mIsLoaded;
	}

	GLboolean ShaderProgram::unload()
	{
		if (mIsLoaded)
		{
			glDeleteProgram(mProgramID);
			mActiveShaders.clear();
			mIsLoaded = GL_FALSE;
		}

		return (mIsLoaded == GL_FALSE);
	}

	void ShaderProgram::use() const
	{
		glUseProgram(mProgramID);
	}

	void ShaderProgram::addShader(Shader& shader)
	{
		mActiveShaders.push_back(&shader);
	}

	GLuint ShaderProgram::getUniformID(std::string uniformName) const
	{
		return glGetUniformLocation(mProgramID, uniformName.c_str());
	}

	void ShaderProgram::loadInt(const std::string& uniformName, GLint data) const
	{
		glUniform1i(getUniformID(uniformName), data);
	}

	void ShaderProgram::loadFloat(const std::string& uniformName, GLfloat data) const
	{
		glUniform1f(getUniformID(uniformName), data);
	}

	void ShaderProgram::loadVec2(const std::string& uniformName, const glm::vec2& vec2) const
	{
		glUniform2f(getUniformID(uniformName), vec2.x, vec2.y);
	}

	void ShaderProgram::loadVec2(const std::string& uniformName, const GLfloat& x, const GLfloat& y) const
	{
		glUniform2f(getUniformID(uniformName), x, y);
	}

	void ShaderProgram::loadVec3(const std::string& uniformName, const glm::vec3& vec3) const
	{
		glUniform3f(getUniformID(uniformName), vec3.x, vec3.y, vec3.z);
	}

	void ShaderProgram::loadVec3(const std::string& uniformName, const GLfloat& x, const GLfloat& y, const GLfloat& z) const
	{
		glUniform3f(getUniformID(uniformName), x, y, z);
	}

	void ShaderProgram::loadMat3(const std::string& uniformName, GLboolean transposeMatrix, const glm::mat3& matrix) const
	{
		glUniformMatrix3fv(getUniformID(uniformName), 1, transposeMatrix, glm::value_ptr(matrix));
	}

	void ShaderProgram::loadMat4(const std::string& uniformName, GLboolean transposeMatrix, const glm::mat4& matrix) const
	{
		glUniformMatrix4fv(getUniformID(uniformName), 1, transposeMatrix, glm::value_ptr(matrix));
	}

	void ShaderProgram::compile()
	{
		if (mIsLoaded)
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "The shader program with id: \'" + mASSET_ID + "\' is already loaded.");
			return;
		}
		else
		{
			mProgramID = glCreateProgram();

			auto iter = mActiveShaders.begin();
			for (; iter != mActiveShaders.end(); ++iter)
			{
				LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Attaching shader: " + (*iter)->getShaderLocation().getNameAndExt());
				glAttachShader(mProgramID, (*iter)->mShaderID);
			}

			glLinkProgram(mProgramID);

			const static GLint ERROR_LOG_SIZE = 512;
			GLint compiled;
			GLchar errorLog[ERROR_LOG_SIZE];

			glGetProgramiv(mProgramID, GL_LINK_STATUS, &compiled);

			if (!compiled)
			{
				glGetProgramInfoLog(mProgramID, ERROR_LOG_SIZE, NULL, errorLog);
			}
			else
			{
				LoggerMaster::getUniversalLogger().logInfo(msCLASS_NAME, "Successfully compiled shader program: \'" + mASSET_ID + "\'.");
			}
		}
	}
}