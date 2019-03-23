#include "Shader.h"
#include "../../filesystem/path/file/io/string/StringFileReader.h"
#include "../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string Shader::msCLASS_NAME = "Shader";

	Shader::Shader(const std::string& assetID, const EnumShaderType& shaderType, FileLocation shaderLocation) :
		Asset(assetID), mSHADER_TYPE(shaderType), mShaderLocation(shaderLocation)
	{

	}

	Shader::~Shader()
	{
		if (isLoaded())
		{
			unload();
		}
	}

	GLboolean Shader::load()
	{
		if (!isLoaded())
		{
			if (extractSourceFromFile())
			{
				compile();
				mIsLoaded = GL_TRUE;
			}
			else
			{
				LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Could not compile shader with id \'" + mASSET_ID + "\' since the source was not found.");
			}
		}

		return mIsLoaded;
	}

	GLboolean Shader::unload()
	{
		if (isLoaded())
		{
			glDeleteShader(mShaderID);
			mIsLoaded = GL_FALSE;
		}

		return (mIsLoaded == GL_FALSE);
	}

	GLboolean Shader::extractSourceFromFile()
	{
		return StringFileReader::getInstance().getContents(mShaderLocation, mShaderCode);
	}

	void Shader::compile()
	{
		switch (mSHADER_TYPE)
		{
		case Shader::EnumShaderType::VERTEX:
			mShaderID = glCreateShader(GL_VERTEX_SHADER);
			break;
		case Shader::EnumShaderType::GEOMETRY:
			mShaderID = glCreateShader(GL_GEOMETRY_SHADER);
			break;
		case Shader::EnumShaderType::FRAGMENT:
			mShaderID = glCreateShader(GL_FRAGMENT_SHADER);
			break;
		}

		const GLint ERROR_LOG_SIZE = 512;
		const GLchar* shaderCode = mShaderCode.c_str();
		GLint compiled;
		GLchar errorLog[ERROR_LOG_SIZE];

		glShaderSource(mShaderID, 1, &shaderCode, NULL);
		glCompileShader(mShaderID);
		glGetShaderiv(mShaderID, GL_COMPILE_STATUS, &compiled);

		if (!compiled)
		{
			glGetShaderInfoLog(mShaderID, ERROR_LOG_SIZE, NULL, errorLog);
			LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Could not compile shader with id \'" + mASSET_ID + "\'. Error:\n" + std::string(errorLog));
		}
		else
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Successfully compiled shader with id \'" + mASSET_ID + "\'.");
		}
	}
}