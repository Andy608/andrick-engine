#ifndef ANDRICK_SINGLE_LEVEL_SINK_H_
#define ANDRICK_SINGLE_LEVEL_SINK_H_

#include <spdlog/sinks/base_sink.h>
#include <spdlog/sinks/file_sinks.h>

namespace andrick
{
	struct FileSinkNameGenerator
	{
		// Generates a filename like: logfile_YYYY-MM-DD_hh-mm-ss.txt
		static spdlog::filename_t generateFileName(const spdlog::filename_t& basename, const spdlog::filename_t& ext)
		{
			std::tm tm = spdlog::details::os::localtime();
			std::conditional<std::is_same<spdlog::filename_t::value_type, char>::value, fmt::MemoryWriter, fmt::WMemoryWriter>::type w;
			w.write(SPDLOG_FILENAME_T("{}_{:04d}-{:02d}-{:02d}_{:02d}-{:02d}-{:02d}{}"), basename, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec, ext);
			return w.str();
		}
	};

	/*template<typename Mutex, typename FileNameGen = FileSinkNameGenerator>
	class SecondlyFileSink : public spdlog::sinks::base_sink<Mutex>
	{
	public:
	explicit SecondlyFileSink(const spdlog::filename_t& fileName, const spdlog::filename_t& ext) : mFileName(fileName), mFileExt(ext) {}

	protected:
	void _sink_it(const spdlog::details::log_msg& message) override
	{
	mFileHelper.open(FileNameGen::generateFileName(mFileName, mFileExt));
	mFileHelper.write(message);
	}

	void _flush() override
	{
	mFileHelper.flush();
	}

	spdlog::filename_t mFileName;
	spdlog::filename_t mFileExt;
	spdlog::details::file_helper mFileHelper;
	};

	typedef SecondlyFileSink<std::mutex> SecondlyFileSink_mt;*/

	template<typename Mutex, typename FileNameGen = FileSinkNameGenerator>
	class PerSessionFileSink : public spdlog::sinks::base_sink<Mutex>
	{
	public:
		explicit PerSessionFileSink(const spdlog::filename_t& fileNameBase, const spdlog::filename_t& ext) : mFileNameBase(fileNameBase), mFileExt(ext)\
		{
			mGeneratedFileName = FileNameGen::generateFileName(mFileNameBase, mFileExt);
		}

	protected:
		void _sink_it(const spdlog::details::log_msg& message) override
		{
			mFileHelper.open(mGeneratedFileName);
			mFileHelper.write(message);
		}

		void _flush() override
		{
			mFileHelper.flush();
		}

		spdlog::filename_t mFileNameBase;
		spdlog::filename_t mFileExt;
		spdlog::filename_t mGeneratedFileName;
		spdlog::details::file_helper mFileHelper;
	};

	typedef PerSessionFileSink<std::mutex> PerSessionFileSink_mt;

	//A file sink that only prints out the specified log level.
	class SingleLevelFileSink : public PerSessionFileSink_mt
	{
	public:
		explicit SingleLevelFileSink(const spdlog::filename_t& baseFileName, const spdlog::filename_t& ext) : PerSessionFileSink_mt(baseFileName, ext)
		{

		}

		bool should_log(spdlog::level::level_enum messageLevel) const override
		{
			return messageLevel == _level.load(std::memory_order_relaxed);
		}
	};
}

#endif