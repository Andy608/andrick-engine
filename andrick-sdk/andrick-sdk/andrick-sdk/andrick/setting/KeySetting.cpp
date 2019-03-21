#include "KeySetting.h"
#include "../logger/LoggerMaster.h"
#include "../util/string/StringUtil.h"
#include "SettingsProcessor.h"

namespace andrick
{
	const std::string KeySetting::msCLASS_NAME = "KeySetting";
	const GLchar KeySetting::msKEY_DELIMITER = ',';

	KeySetting::KeySetting(GameSetting::EnumSetting settingID, const std::string settingName, const std::set<GLuint> defaultKeys) :
		GameSetting(settingID, settingName), mDEFAULT_KEYS(defaultKeys)
	{
		setCustomKeyBinding(mDEFAULT_KEYS);
		LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Creating keysetting \'" + mSETTING_NAME + "\': " + toReadableString());
	}

	KeySetting::~KeySetting()
	{
		LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Deleting keysetting \'" + mSETTING_NAME + "\': " + toReadableString());
	}

	std::string KeySetting::toReadableString() const
	{
		std::string readableString = mSETTING_NAME + " | Default Keybinding:";
		auto iter = mDEFAULT_KEYS.begin();
		for (; iter != mDEFAULT_KEYS.end(); ++iter)
		{
			readableString += " " + std::to_string(*iter);
		}

		readableString += " | Custom Keybinding:";

		iter = mCustomKeys.begin();
		for (; iter != mCustomKeys.end(); ++iter)
		{
			readableString += " " + std::to_string(*iter);
		}

		return readableString;
	}

	std::string KeySetting::toFileString() const
	{
		std::string fileString = mSETTING_NAME + SettingsProcessor::msFILE_DELIMITER;

		auto iter = mCustomKeys.begin();

		if (iter != mCustomKeys.end())
		{
			fileString += std::to_string(*iter);
			++iter;

			for (; iter != mCustomKeys.end(); ++iter)
			{
				fileString += msKEY_DELIMITER + std::to_string(*iter);
			}
		}

		return fileString;
	}
	
	void KeySetting::loadFromString(const std::string& settingInFile)
	{
		std::vector<std::string> stringData = StringUtil::split(settingInFile.c_str(), msKEY_DELIMITER);

		try
		{
			std::set<GLuint> customKeys;

			auto iter = stringData.begin();
			for (; iter != stringData.end(); ++iter)
			{
				customKeys.insert(std::stoi(*iter));
			}

			setCustomKeyBinding(customKeys);
			return;
		}
		catch (const std::invalid_argument&)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Could not convert data to integer. Invalid argument. Returning default value.");
		}
		catch (const std::out_of_range&)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Could not convert data to integer. Out of range. Returning default value.");
		}
		catch (...)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Could not convert data to integer. Returning default value.");
		}

		resetCustomValue();
	}

	GLboolean KeySetting::isModified() const
	{
		return mDEFAULT_KEYS == mCustomKeys;
	}

	void KeySetting::resetCustomValue()
	{
		setCustomKeyBinding(mDEFAULT_KEYS);
	}

	void KeySetting::setCustomKeyBinding(const std::set<GLuint>& customKeys)
	{
		mCustomKeys.clear();
		auto iter = customKeys.begin();
		for (; iter != customKeys.end(); ++iter)
		{
			mCustomKeys.insert(*iter);
		}
	}

	const GLuint KeySetting::getDefaultBindingLength() const
	{
		return static_cast<const GLuint>(mDEFAULT_KEYS.size());
	}

	const GLuint KeySetting::getCustomBindingLength() const
	{
		return static_cast<const GLuint>(mCustomKeys.size());
	}
}