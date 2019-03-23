#include "StringFileReader.h"
#include "../../../../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string StringFileReader::msCLASS_NAME = "StringFileReader";

	StringFileReader::StringFileReader() :
		mReadStream(std::make_unique<std::ifstream>()),
		mStringStream(std::make_unique<std::stringstream>())
	{

	}

	GLboolean StringFileReader::getContents(const FileLocation& file, std::string& fileContents)
	{
		GLboolean success = GL_FALSE;

		mReadStream->open(file.getPath(), std::ifstream::in);

		if (mReadStream->is_open())
		{
			mStringStream->str(std::string());
			*mStringStream << mReadStream->rdbuf();
			fileContents = mStringStream->str();
			success = GL_TRUE;
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "Unable to read file: \'" + file.getPath() + "\'.");
		}

		mReadStream->close();
		return success;
	}

	GLboolean StringFileReader::getContentsByLine(const FileLocation& file, std::vector<std::string>& fileContents)
	{
		GLboolean success = GL_FALSE;
		mReadStream->open(file.getPath(), std::ifstream::in);

		if (mReadStream->is_open())
		{
			fileContents.clear();
			std::string line;

			while (std::getline(*mReadStream, line))
			{
				fileContents.push_back(line);
			}

			success = GL_TRUE;
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "Unable to read file: \'" + file.getPath() + "\'.");
		}

		mReadStream->close();
		return success;
	}
}