#include "BooleanSetting.h"
#include "SettingsProcessor.h"
#include "../logger/LoggerMaster.h"

namespace andrick
{
	const std::string BooleanSetting::msCLASS_NAME = "IntegerSetting";

	BooleanSetting::BooleanSetting(EnumSetting settingID, const std::string& settingName, GLboolean boolean) :
		GameSetting(settingID, settingName), mDefaultBoolean(boolean), mCustomBoolean(boolean)
	{
		LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Creating booleansetting \'" + mSETTING_NAME + "\': " + toReadableString());
	}

	BooleanSetting::~BooleanSetting()
	{
		LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Deleting booleansetting \'" + mSETTING_NAME + "\': " + toReadableString());
	}

	std::string BooleanSetting::toReadableString() const
	{
		return mSETTING_NAME + " = " + std::to_string(mCustomBoolean);
	}

	std::string BooleanSetting::toFileString() const
	{
		return mSETTING_NAME + SettingsProcessor::msFILE_DELIMITER + std::to_string(mCustomBoolean);
	}

	void BooleanSetting::loadFromString(const std::string& settingInFile)
	{
		try
		{
			mCustomBoolean = std::stoi(settingInFile);
			return;
		}
		catch (const std::invalid_argument&)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Could not convert data to boolean. Invalid argument. Returning default value.");
		}
		catch (const std::out_of_range&)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Could not convert data to boolean. Out of range. Returning default value.");
		}
		catch (...)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Could not convert data to boolean. Returning default value.");
		}

		resetCustomValue();
	}

	GLboolean BooleanSetting::isModified() const
	{
		return (mDefaultBoolean != mCustomBoolean);
	}

	void BooleanSetting::resetCustomValue()
	{
		mCustomBoolean = mDefaultBoolean;
	}
}