#ifndef ANDRICK_STRING_FILE_WRITER_H_
#define ANDRICK_STRING_FILE_WRITER_H_

#include <fstream>
#include <vector>
#include <string>
#include <memory>
#include <glad/glad.h>
#include "../../../../../memory/TrackableObject.h"
#include "../../../../../memory/NonCopyable.h"

namespace andrick
{
	class FileLocation;
	class StringFileWriter : public TrackableObject, NonCopyable
	{
	public:
		static StringFileWriter& getInstance()
		{
			static StringFileWriter instance;
			return instance;
		}

		GLboolean writeLinesInFile(const FileLocation& FILE, const std::vector<std::string> &lines);

	private:
		static const std::string msCLASS_NAME;
		std::unique_ptr<std::ofstream> mWriteStream;

		StringFileWriter();
		inline ~StringFileWriter() {};
	};
}

#endif