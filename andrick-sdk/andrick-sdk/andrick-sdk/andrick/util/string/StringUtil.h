#ifndef ANDRICK_STRING_UTIL_H_
#define ANDRICK_STRING_UTIL_H_

#include <string>
#include <set>
#include <vector>
#include <glad/glad.h>
#include "../../logger/LoggerMaster.h"

namespace andrick
{
	struct StringUtil
	{
		static std::string wtos(const std::wstring& wstr);
		static std::wstring stow(const std::string& str);

		static void split(const char* str, char delimiter, bool addDoubleDimiliterSpace, std::vector<std::string>& result);
		static std::vector<std::string> split(const char* str, char delimiter, bool addDoubleDimiliterSpace = GL_FALSE);

		static std::string arrayToString(const std::string *array, GLuint size);
		static std::string vectorToString(const std::vector<std::string> &array);

		template <typename T>
		static std::string setToString(const std::set<T> &set);

		template <typename T>
		static std::string arrayToString(const T *array, GLuint size);

	private:
		static const std::string msCLASS_NAME;
	};

	template <typename T>
	static std::string StringUtil::setToString(const std::set<T> &set)
	{
		std::string str;

		if (set.empty())
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "The set is empty. Return empty string.");
			str = "";
		}
		else
		{
			str = std::to_string(*set.begin());

			typename std::set<T>::iterator it;

			for (it = ++set.begin(); it != set.end(); ++it)
			{
				str += " " + std::to_string(*it);
			}
		}

		return str;
	}

	template <typename T>
	static std::string StringUtil::arrayToString(const T *array, GLuint size)
	{
		std::string str;

		if (!array || size == 0)
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "The array is null or empty. Return empty string.");
			str = "";
		}
		else
		{
			str = std::to_string(array[0]);

			GLuint i;
			for (i = 1; i < size; ++i)
			{
				str += " " + std::to_string(array[i]);
			}
		}

		return str;
	}
}

#endif