#include "SettingsData.h"
#include <andrick/input/InputProcessor.h>
#include <andrick/setting/SettingsProcessor.h>

namespace bb
{
	SettingsData* SettingsData::mspInstance = nullptr;
	const std::string SettingsData::msCLASS_NAME = "SettingsData";
	
	GLboolean SettingsData::init()
	{
		if (!mspInstance)
		{
			try
			{
				mspInstance = new SettingsData();
			}
			catch (const std::invalid_argument& e)
			{
				andrick::LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, e.what());
				mspInstance = nullptr;
			}
		}

		return (mspInstance != nullptr);
	}

	void SettingsData::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	SettingsData::SettingsData()
	{
		//1. Check datastore exists.
		if (!andrick::SettingsProcessor::getInstance())
		{
			std::string err = "SettingsDatastore is closed for the day. It must be instantiated before using.";
			throw std::invalid_argument(err);
		}

		//2. Create all of the default settings.
		std::set<GLuint> keySetHelper;

		//MoveForward default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_W);
		mMoveForwardSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::CAMERA_FORWARD_KEYBINDING), "move_forward", keySetHelper);
		keySetHelper.clear();

		//MoveBackward default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_S);
		mMoveBackwardSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::CAMERA_BACKWARD_KEYBINDING), "move_backward", keySetHelper);
		keySetHelper.clear();

		//MoveLeft default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_A);
		mMoveLeftSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::CAMERA_LEFT_KEYBINDING), "move_left", keySetHelper);
		keySetHelper.clear();

		//MoveRight default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_D);
		mMoveRightSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::CAMERA_RIGHT_KEYBINDING), "move_right", keySetHelper);
		keySetHelper.clear();

		//MoveUp default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_SPACE);
		mMoveUpSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::CAMERA_UP_KEYBINDING), "move_up", keySetHelper);
		keySetHelper.clear();

		//MoveDown default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_LEFT_SHIFT);
		mMoveDownSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::CAMERA_DOWN_KEYBINDING), "move_down", keySetHelper);
		keySetHelper.clear();

		//Quit default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_TAB);
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_ESCAPE);
		mQuitSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::QUIT_KEYBINDING), "quit", keySetHelper);
		keySetHelper.clear();

		//Pause default setting
		keySetHelper.insert(andrick::EnumInput::ANDRICK_KEY_ESCAPE);
		mPauseSetting = new andrick::KeySetting(convertSetting(EnumGameSetting::PAUSE_KEYBINDING), "pause", keySetHelper);
		keySetHelper.clear();

		//Mouse sensitivity default setting
		mMouseSensitivity = new andrick::IntegerSetting(convertSetting(EnumGameSetting::MOUSE_SENSITIVITY), "mouse_sensitivity", 12);

		//Vertical sync default setting
		mVerticalSync = new andrick::BooleanSetting(convertSetting(EnumGameSetting::V_SYNC), "v_sync", GL_FALSE);

		//3. Register the settings with the datastore.
		andrick::SettingsProcessor::getInstance()->registerSetting(mMoveForwardSetting);
		andrick::SettingsProcessor::getInstance()->registerSetting(mMoveBackwardSetting);
		andrick::SettingsProcessor::getInstance()->registerSetting(mMoveLeftSetting);
		andrick::SettingsProcessor::getInstance()->registerSetting(mMoveRightSetting);
		andrick::SettingsProcessor::getInstance()->registerSetting(mMoveUpSetting);
		andrick::SettingsProcessor::getInstance()->registerSetting(mMoveDownSetting);

		andrick::SettingsProcessor::getInstance()->registerSetting(mQuitSetting);
		andrick::SettingsProcessor::getInstance()->registerSetting(mPauseSetting);

		andrick::SettingsProcessor::getInstance()->registerSetting(mMouseSensitivity);
		andrick::SettingsProcessor::getInstance()->registerSetting(mVerticalSync);

		//4. Load the custom settings from the settings file.
		andrick::SettingsProcessor::getInstance()->loadSettings();
	}

	SettingsData::~SettingsData()
	{
		//5. Save the settings to the settings file.
		andrick::SettingsProcessor::getInstance()->saveSettings();
	}

	andrick::GameSetting::EnumSetting SettingsData::convertSetting(EnumGameSetting gameSetting)
	{
		return static_cast<andrick::GameSetting::EnumSetting>(gameSetting);
	}
}