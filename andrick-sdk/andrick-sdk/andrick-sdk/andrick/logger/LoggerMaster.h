#ifndef ANDRICK_LOGGER_MASTER_H_
#define ANDRICK_LOGGER_MASTER_H_

#include <map>
#include <string>
#include <glad/glad.h>
#include "../memory/TrackableObject.h"
#include "../memory/NonCopyable.h"
#include "../filesystem/path/directory/DirectoryLocation.h"
#include "../filesystem/path/file/FileLocation.h"
#include "Logger.h"

namespace andrick
{
	class LoggerMaster : private NonCopyable
	{
		friend class AndrickCore;

	public:
		static inline GLboolean isInitialized() { return msIsInitialized; };

		GLboolean registerLogger(std::string loggerID);
		GLboolean registerFileOutput(const FileLocation& fileOutputLocation, Logger::EnumLoggerLevel level = Logger::EnumLoggerLevel::LOG_TRACE, GLboolean isSingleLevel = GL_FALSE);

		static void addConsoleSink(std::string loggerID, std::string outputFormat = Logger::DEFAULT_FORMAT);
		static void addBasicFileSink(std::string loggerID, const FileLocation& outputLocation, std::string outputFormat = Logger::DEFAULT_FORMAT);

		static Logger* getLogger(std::string loggerID);
		static const Logger& getUniversalLogger();

	private:
		static const std::string msCLASS_NAME;

		static GLboolean init();
		static void cleanup();

		static GLboolean msIsInitialized;
		static LoggerMaster* mspLoggerMaster;

		Logger mUniversalLogger;
		std::map<std::string, Logger*> mLoggerMap;
		DirectoryLocation mMainLogDirectory;
		DirectoryLocation mGeneralLogDumpDir;
		FileLocation mGeneralLogDumpFile;
		std::map<Logger::EnumLoggerLevel, DirectoryLocation> mLogDumpByLevelDirMap;
		std::map<Logger::EnumLoggerLevel, FileLocation> mLogDumpByLevelFileMap;
		std::map<std::string, spdlog::sink_ptr> mFileSinkMap;

		LoggerMaster();
		virtual ~LoggerMaster();

		GLboolean isLoggerInList(std::string loggerID);
		Logger* registerAndReturnLogger(std::string loggerID, std::string outputFormat = Logger::DEFAULT_FORMAT);
		spdlog::sink_ptr getFileOutputSink(const FileLocation& fileOutputLocation);
	};
}

#endif
