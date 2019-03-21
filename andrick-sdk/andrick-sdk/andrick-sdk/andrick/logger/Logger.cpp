#include "Logger.h"
#include "LoggerMaster.h"
using namespace andrick;

const std::string Logger::msCLASS_NAME = "Logger";
const std::string Logger::DEFAULT_FORMAT = "[%x %r] %l (%n) %v";
const Logger::EnumLoggerLevel Logger::LOGGER_LEVELS[] = { LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_CRITICAL };
const std::string Logger::LEVEL_STRINGS[] = { "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "CRITICAL" };

Logger::Logger(const std::string loggerID, std::string outputFormat, Logger::EnumLoggerLevel minimumLevel) :
	mLOGGER_ID(loggerID), mIsRegistered(GL_FALSE), mFormat(outputFormat), mMinimumLevel(minimumLevel)
{

}

Logger::~Logger()
{

}

std::string Logger::getFormattedMessage(const std::string& className, std::string message) const
{
	return "[" + className + ".cpp] - " + message;
}

void Logger::log(EnumLoggerLevel level, const std::string& className, std::string message) const
{
	if (!LoggerMaster::isInitialized)
	{
		std::cout << "Logger is not initialized! Did you forget to initialize Andrick?" << std::endl;
		return;
	}

	std::string formattedMessage = getFormattedMessage(className, message);

	switch (level)
	{
	case EnumLoggerLevel::LOG_TRACE:
		mLogger->trace(formattedMessage);
		break;
	case EnumLoggerLevel::LOG_DEBUG:
		mLogger->debug(formattedMessage);
		break;
	case EnumLoggerLevel::LOG_INFO:
		mLogger->info(formattedMessage);
		break;
	case EnumLoggerLevel::LOG_WARN:
		mLogger->warn(formattedMessage);
		break;
	case EnumLoggerLevel::LOG_ERROR:
		mLogger->error(formattedMessage);
		break;
	case EnumLoggerLevel::LOG_CRITICAL:
		mLogger->critical(formattedMessage);
		break;
	}

	mLogger->flush();
}

void Logger::logTrace(const std::string& className, std::string message) const
{
	log(EnumLoggerLevel::LOG_TRACE, className, message);
}

void Logger::logDebug(const std::string& className, std::string message) const
{
	log(EnumLoggerLevel::LOG_DEBUG, className, message);
}

void Logger::logInfo(const std::string& className, std::string message) const
{
	log(EnumLoggerLevel::LOG_INFO, className, message);
}

void Logger::logWarn(const std::string& className, std::string message) const
{
	log(EnumLoggerLevel::LOG_WARN, className, message);
}

void Logger::logError(const std::string& className, std::string message) const
{
	log(EnumLoggerLevel::LOG_ERROR, className, message);
}

void Logger::logCritical(const std::string& className, std::string message) const
{
	log(EnumLoggerLevel::LOG_CRITICAL, className, message);
}

void Logger::registerLogger()
{
	if (!mIsRegistered)
	{
		if (mSinks.empty())
		{
			LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Cannot register logger with no output locations (sinks).");
			return;
		}

		mLogger = std::make_shared<spdlog::logger>(mLOGGER_ID, std::begin(mSinks), std::end(mSinks));
		mLogger->set_level(static_cast<spdlog::level::level_enum>(mMinimumLevel));
		mLogger->set_pattern(mFormat);

		spdlog::register_logger(mLogger);
		mIsRegistered = GL_TRUE;
	}
}