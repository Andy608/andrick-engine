#ifndef ANDRICK_STRING_FILE_READER_H_
#define ANDRICK_STRING_FILE_READER_H_

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <glad/glad.h>
#include "../../../../../memory/TrackableObject.h"
#include "../../../../../memory/NonCopyable.h"

namespace andrick
{
	class FileLocation;
	class StringFileReader : public TrackableObject, NonCopyable
	{
	public:
		static StringFileReader& getInstance()
		{
			static StringFileReader instance;
			return instance;
		}

		GLboolean getContents(const FileLocation& FILE, std::string& fileContents);
		GLboolean getContentsByLine(const FileLocation& FILE, std::vector<std::string>& fileContents);

	private:
		static const std::string msCLASS_NAME;
		std::unique_ptr<std::ifstream> mReadStream;
		std::unique_ptr<std::stringstream> mStringStream;

		StringFileReader();
		inline ~StringFileReader() {};
	};
}

#endif