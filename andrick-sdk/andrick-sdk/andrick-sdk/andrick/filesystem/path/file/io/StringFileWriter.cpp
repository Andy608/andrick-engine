#include "StringFileWriter.h"
#include "../FileLocation.h"
#include "../../../../logger/LoggerMaster.h"

namespace andrick
{
	const std::string StringFileWriter::msCLASS_NAME = "StringFileWriter";

	StringFileWriter::StringFileWriter() :
		mWriteStream(std::make_unique<std::ofstream>())
	{

	}

	GLboolean StringFileWriter::writeLinesInFile(const FileLocation& FILE, const std::vector<std::string> &lines)
	{
		GLboolean success = GL_FALSE;
		mWriteStream->open(FILE.getPath(), std::fstream::trunc);

		if (mWriteStream->good())
		{
			if (!lines.empty())
			{
				*mWriteStream << lines.at(0);

				GLuint i;
				for (i = 1; i < lines.size(); ++i)
				{
					*mWriteStream << std::endl << lines.at(i);
				}

				success = GL_TRUE;
				LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Successfuly wrote to file: " + FILE.getPath());
			}
			else
			{
				LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Lines vector is empty. Not writing anything to file: " + FILE.getPath());
			}
		}
		else
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Failed to open file: " + FILE.getPath());
		}

		mWriteStream->close();
		return success;
	}
}