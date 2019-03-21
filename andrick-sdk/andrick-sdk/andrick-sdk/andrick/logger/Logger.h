#ifndef ANDRICK_LOGGER_H_
#define ANDRICK_LOGGER_H_

#include <string>
#include <glad/glad.h>
#include <spdlog/spdlog.h>
#include "../memory/NonCopyable.h"

namespace andrick
{
	class Logger
	{
		friend class LoggerMaster;

	public:
		enum EnumLoggerLevel : GLuint
		{
			LOG_TRACE, LOG_DEBUG, LOG_INFO, LOG_WARN, LOG_ERROR, LOG_CRITICAL, LEVEL_COUNT
		};

		static const std::string DEFAULT_FORMAT;
		static const std::string LEVEL_STRINGS[];
		static const EnumLoggerLevel LOGGER_LEVELS[];

		virtual ~Logger();

		void log(EnumLoggerLevel level, const std::string& className, std::string message) const;

		//Convenience methods
		void	logTrace(const std::string& className, std::string message) const;
		void	logDebug(const std::string& className, std::string message) const;
		void	 logInfo(const std::string& className, std::string message) const;
		void	 logWarn(const std::string& className, std::string message) const;
		void	logError(const std::string& className, std::string message) const;
		void logCritical(const std::string& className, std::string message) const;

	private:
		static const std::string msCLASS_NAME;
		const std::string mLOGGER_ID;
		GLboolean mIsRegistered;
		std::string mFormat;
		EnumLoggerLevel mMinimumLevel;

		std::vector<spdlog::sink_ptr> mSinks;
		std::shared_ptr<spdlog::logger> mLogger;

		Logger(const std::string loggerID, std::string outputFormat = Logger::DEFAULT_FORMAT, Logger::EnumLoggerLevel minimumLevel = Logger::EnumLoggerLevel::LOG_TRACE);

		inline void addSink(spdlog::sink_ptr sink) { mSinks.push_back(sink); };
		void registerLogger();

		std::string getFormattedMessage(const std::string& className, std::string message) const;
	};
}

#endif
