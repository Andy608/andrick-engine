#include "LoggerMaster.h"
#include "../filesystem/FileSystem.h"
#include "AndrickSinks.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/ansicolor_sink.h>

using namespace andrick;

const std::string LoggerMaster::msCLASS_NAME = "LoggerMaster";
GLboolean LoggerMaster::mIsInitialized = false;
LoggerMaster* LoggerMaster::smpLoggerMaster = nullptr;

GLboolean LoggerMaster::init()
{
	if (!mIsInitialized)
	{
		smpLoggerMaster = new LoggerMaster();

		auto stdOutSink = spdlog::sinks::stdout_sink_mt::instance();
#if defined (_WIN32)
		auto coloredStdOutSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#else
		auto coloredStdOutSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#endif
		smpLoggerMaster->mUniversalLogger.addSink(coloredStdOutSink);

		//Create the main log directory
		if (!FileSystem::getFS()->isDirectoryCreated(smpLoggerMaster->mMainLogDirectory))
		{
			FileSystem::getFS()->createDirectory(smpLoggerMaster->mMainLogDirectory);
		}

		//Create the general log dump directory
		if (smpLoggerMaster->registerFileOutput(smpLoggerMaster->mGeneralLogDumpFile))
		{
			auto fileSink = smpLoggerMaster->getFileOutputSink(smpLoggerMaster->mGeneralLogDumpFile);
			smpLoggerMaster->mUniversalLogger.addSink(fileSink);
		}

		//Create the log dump directories for each log level
		for (auto fileIter : smpLoggerMaster->mLogDumpByLevelFileMap)
		{
			//Register file output with the file location, the level, and if it is only 1 level
			if (smpLoggerMaster->registerFileOutput(fileIter.second, fileIter.first, GL_TRUE))
			{
				auto fileSink = smpLoggerMaster->getFileOutputSink(fileIter.second);
				smpLoggerMaster->mUniversalLogger.addSink(fileSink);
			}
		}

		smpLoggerMaster->mUniversalLogger.registerLogger();

		mIsInitialized = true;
	}

	return mIsInitialized;
}

void LoggerMaster::cleanup()
{
	if (mIsInitialized)
	{
		delete smpLoggerMaster;
		smpLoggerMaster = nullptr;
		mIsInitialized = false;
	}
}

void LoggerMaster::addConsoleSink(std::string loggerID, std::string outputFormat)
{
	Logger* desiredLogger = smpLoggerMaster->registerAndReturnLogger(loggerID, outputFormat);

	//Add console sink
	auto stdOutSink = spdlog::sinks::stdout_sink_mt::instance();

#if defined (_WIN32)
	auto coloredStdOutSink = std::make_shared<spdlog::sinks::wincolor_stdout_sink_mt>();
#else
	auto coloredStdOutSink = std::make_shared<spdlog::sinks::ansicolor_stdout_sink_mt>();
#endif

	desiredLogger->addSink(coloredStdOutSink);
}

void LoggerMaster::addBasicFileSink(std::string loggerID, const FileLocation& outputLocation, std::string outputFormat)
{
	Logger* desiredLogger = smpLoggerMaster->registerAndReturnLogger(loggerID, outputFormat);

	try
	{
		//Add basic file sink
		auto fileSink = smpLoggerMaster->getFileOutputSink(outputLocation);
		desiredLogger->addSink(fileSink);
	}
	catch (const std::exception& e)
	{
		smpLoggerMaster->mUniversalLogger.logError("LoggerMaster", std::string("Could not add basic file sink. Reasons: ") + e.what());
	}
}

Logger* LoggerMaster::getLogger(std::string loggerID)
{
	if (!smpLoggerMaster->isLoggerInList(loggerID))
	{
		addConsoleSink(loggerID);
		smpLoggerMaster->registerLogger(loggerID);
	}

	return smpLoggerMaster->mLoggerMap.find(loggerID)->second;
}

LoggerMaster::LoggerMaster() :
	mUniversalLogger(Logger("Universal Logger")),
	mMainLogDirectory(DirectoryLocation("", "logs", PathLocation::EnumPathType::RELATIVE_PATH)),
	mGeneralLogDumpDir(DirectoryLocation(mMainLogDirectory, "ALL_log_dump")),
	mGeneralLogDumpFile(FileLocation(mGeneralLogDumpDir, "ALL_log_dump")),
	mLogDumpByLevelDirMap(std::map<Logger::EnumLoggerLevel, DirectoryLocation>()),
	mLogDumpByLevelFileMap(std::map<Logger::EnumLoggerLevel, FileLocation>()),
	mFileSinkMap(std::map<std::string, spdlog::sink_ptr>())
{
	for (int i = 0; i < Logger::EnumLoggerLevel::LEVEL_COUNT; ++i)
	{
		mLogDumpByLevelDirMap.insert(std::make_pair(Logger::LOGGER_LEVELS[i], DirectoryLocation(mMainLogDirectory, Logger::LEVEL_STRINGS[i] + "_log_dump")));
	}

	for (auto dirIter : mLogDumpByLevelDirMap)
	{
		mLogDumpByLevelFileMap.insert(std::make_pair(dirIter.first, FileLocation(dirIter.second, Logger::LEVEL_STRINGS[dirIter.first] + "_log_dump")));
	}
}

LoggerMaster::~LoggerMaster()
{
	auto iter = mLoggerMap.begin();
	for (; iter != mLoggerMap.end(); ++iter)
	{
		delete iter->second;
	}

	mLoggerMap.clear();
}

const Logger& LoggerMaster::getUniversalLogger()
{
	return smpLoggerMaster->mUniversalLogger;
}

GLboolean LoggerMaster::isLoggerInList(std::string loggerID)
{
	auto loggerEntry = mLoggerMap.find(loggerID);
	GLboolean loggerFound = GL_FALSE;

	if (loggerEntry != mLoggerMap.end())
	{
		loggerFound = GL_TRUE;
	}

	return loggerFound;
}

Logger* LoggerMaster::registerAndReturnLogger(std::string loggerID, std::string outputFormat)
{
	auto loggerMap = mLoggerMap;
	auto loggerEntry = loggerMap.find(loggerID);
	Logger* desiredLogger = nullptr;

	if (loggerEntry == loggerMap.end())
	{
		desiredLogger = new Logger(loggerID, outputFormat);
		mLoggerMap.insert(std::make_pair(loggerID, desiredLogger));
		mUniversalLogger.logInfo(msCLASS_NAME, "Creating logger: \"" + loggerID + "\" and initializing.");
	}
	else
	{
		desiredLogger = loggerEntry->second;
	}

	return desiredLogger;
}

GLboolean LoggerMaster::registerLogger(std::string loggerID)
{
	GLboolean success;
	auto loggerIter = smpLoggerMaster->mLoggerMap.find(loggerID);

	if (loggerIter != smpLoggerMaster->mLoggerMap.end())
	{
		Logger* desiredLogger = loggerIter->second;
		addBasicFileSink(loggerID, mGeneralLogDumpFile);

		for (auto fileIter : mLogDumpByLevelFileMap)
		{
			addBasicFileSink(loggerID, fileIter.second);
		}

		desiredLogger->registerLogger();
		success = GL_TRUE;
	}
	else
	{
		mUniversalLogger.logWarn(msCLASS_NAME, "Cannot register logger. Unknown logger ID: \"" + loggerID + "\".");
		success = GL_FALSE;
	}

	return success;
}

GLboolean LoggerMaster::registerFileOutput(const FileLocation& fileOutputLocation, Logger::EnumLoggerLevel level, GLboolean isSingleLevel)
{
	if (mFileSinkMap.find(fileOutputLocation.getPath()) != mFileSinkMap.end())
	{
		mUniversalLogger.logWarn(msCLASS_NAME, "Output file: \"" + fileOutputLocation.getPath() + "\" is already registered.");
		return GL_FALSE;
	}

	GLboolean isDirCreated = GL_TRUE;

	if (!FileSystem::getFS()->isDirectoryCreated(fileOutputLocation.getParentPath()))
	{
		isDirCreated = FileSystem::getFS()->createDirectory(fileOutputLocation.getParentPath());
	}

	if (isDirCreated)
	{
		if (isSingleLevel)
		{
			auto sharedFileSink = std::make_shared<SingleLevelFileSink>(fileOutputLocation.getPathNoExt(), fileOutputLocation.getExtAsString());
			sharedFileSink->set_level(static_cast<spdlog::level::level_enum>(level));
			mFileSinkMap.insert(std::make_pair(fileOutputLocation.getPath(), sharedFileSink));
		}
		else
		{
			auto sharedFileSink = std::make_shared<PerSessionFileSink_mt>(fileOutputLocation.getPathNoExt(), fileOutputLocation.getExtAsString());
			sharedFileSink->set_level(static_cast<spdlog::level::level_enum>(level));
			mFileSinkMap.insert(std::make_pair(fileOutputLocation.getPath(), sharedFileSink));
		}
	}
	else if (smpLoggerMaster->isInitialized())
	{
		mUniversalLogger.logWarn(msCLASS_NAME, "Unable to register output file location: \"" + fileOutputLocation.getPath() + "\". This path does not exist.");
	}
	else
	{
		std::cout << std::string("Unable to register output file location: \"" + fileOutputLocation.getPath() + "\". This path does not exist.") << std::endl;
	}

	return isDirCreated;
}

spdlog::sink_ptr LoggerMaster::getFileOutputSink(const FileLocation& fileOutputLocation)
{
	auto fileSinkIter = mFileSinkMap.find(fileOutputLocation.getPath());

	if (fileSinkIter == mFileSinkMap.end())
	{
		mUniversalLogger.logWarn(msCLASS_NAME, "File location is not registered yet. Registering now...");
		if (registerFileOutput(fileOutputLocation))
		{
			fileSinkIter = mFileSinkMap.find(fileOutputLocation.getPath());
		}
		else
		{
			throw std::runtime_error("Cannot obtain file at path: \"" + fileOutputLocation.getPath() + "\".");
		}
	}

	return fileSinkIter->second;
}
