#include "IntegerSetting.h"
#include "SettingsProcessor.h"
#include "../logger/LoggerMaster.h"

namespace andrick
{
	const std::string IntegerSetting::msCLASS_NAME = "IntegerSetting";

	IntegerSetting::IntegerSetting(EnumSetting settingID, const std::string& settingName, GLint integer) :
		GameSetting(settingID, settingName), mDefaultInteger(integer), mCustomInteger(integer)
	{
		LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Creating integersetting \'" + mSETTING_NAME + "\': " + toReadableString());
	}

	IntegerSetting::~IntegerSetting()
	{
		LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Deleting integersetting \'" + mSETTING_NAME + "\': " + toReadableString());
	}

	std::string IntegerSetting::toReadableString() const
	{
		return mSETTING_NAME + " = " + std::to_string(mCustomInteger);
	}

	std::string IntegerSetting::toFileString() const
	{
		return mSETTING_NAME + SettingsProcessor::msFILE_DELIMITER + std::to_string(mCustomInteger);
	}

	void IntegerSetting::loadFromString(const std::string& settingInFile)
	{
		try
		{
			mCustomInteger = std::stoi(settingInFile);
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

	GLboolean IntegerSetting::isModified() const
	{
		return (mDefaultInteger != mCustomInteger);
	}

	void IntegerSetting::resetCustomValue()
	{
		mCustomInteger = mDefaultInteger;
	}
}