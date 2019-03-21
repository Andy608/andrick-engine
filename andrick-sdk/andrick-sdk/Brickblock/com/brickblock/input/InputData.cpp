#include <andrick/logger/LoggerMaster.h>
#include <andrick/input/InputProcessor.h>
#include <andrick/setting/SettingsProcessor.h>
#include <andrick/event/AndrickEventQueue.h>
#include "InputData.h"
#include "../setting/SettingsData.h"

namespace bb
{
	InputData* InputData::mspInstance = nullptr;
	const std::string InputData::msCLASS_NAME = "InputData";

	GLboolean InputData::init()
	{
		if (!mspInstance)
		{
			try
			{
				mspInstance = new InputData();
			}
			catch (const std::invalid_argument& e)
			{
				andrick::LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, e.what());
				mspInstance = nullptr;
			}
		}

		return (mspInstance != nullptr);
	}

	void InputData::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	InputData::InputData()
	{
		//1. Check InputProcessor exists.
		if (!andrick::InputProcessor::get())
		{
			std::string err = "InputProcessor is not initialized. It must be instantiated before using.";
			throw std::invalid_argument(err);
		}

		andrick::KeySetting* settingHelper;

		//Forward Keybinding
		settingHelper = SettingsData::mspInstance->getSetting<andrick::KeySetting*>(SettingsData::EnumGameSetting::CAMERA_FORWARD_KEYBINDING);
		mForwardKeyBinding = new andrick::AndrickKeyBinding(settingHelper);

		//Backward Keybinding
		settingHelper = SettingsData::mspInstance->getSetting<andrick::KeySetting*>(SettingsData::EnumGameSetting::CAMERA_BACKWARD_KEYBINDING);
		mBackwardKeyBinding = new andrick::AndrickKeyBinding(settingHelper);

		//Left Keybinding
		settingHelper = SettingsData::mspInstance->getSetting<andrick::KeySetting*>(SettingsData::EnumGameSetting::CAMERA_LEFT_KEYBINDING);
		mLeftKeyBinding = new andrick::AndrickKeyBinding(settingHelper);

		//Right Keybinding
		settingHelper = SettingsData::mspInstance->getSetting<andrick::KeySetting*>(SettingsData::EnumGameSetting::CAMERA_RIGHT_KEYBINDING);
		mRightKeyBinding = new andrick::AndrickKeyBinding(settingHelper);

		//Up Keybinding
		settingHelper = SettingsData::mspInstance->getSetting<andrick::KeySetting*>(SettingsData::EnumGameSetting::CAMERA_UP_KEYBINDING);
		mUpKeyBinding = new andrick::AndrickKeyBinding(settingHelper);

		//Down Keybinding
		settingHelper = SettingsData::mspInstance->getSetting<andrick::KeySetting*>(SettingsData::EnumGameSetting::CAMERA_DOWN_KEYBINDING);
		mDownKeyBinding = new andrick::AndrickKeyBinding(settingHelper);

		//Quit Keybinding
		settingHelper = SettingsData::mspInstance->getSetting<andrick::KeySetting*>(SettingsData::EnumGameSetting::QUIT_KEYBINDING);
		mQuitKeyBinding = new andrick::AndrickKeyBinding(settingHelper);

		//Register Keybindings
		andrick::InputProcessor::get()->registerKeyBinding(mForwardKeyBinding);
		andrick::InputProcessor::get()->registerKeyBinding(mBackwardKeyBinding);
		andrick::InputProcessor::get()->registerKeyBinding(mLeftKeyBinding);
		andrick::InputProcessor::get()->registerKeyBinding(mRightKeyBinding);
		andrick::InputProcessor::get()->registerKeyBinding(mUpKeyBinding);
		andrick::InputProcessor::get()->registerKeyBinding(mDownKeyBinding);

		andrick::InputProcessor::get()->registerKeyBinding(mQuitKeyBinding);
	}

	InputData::~InputData()
	{

	}

	void InputData::update(const GLdouble& deltaTime)
	{
		if (mQuitKeyBinding->isPressed())
		{
			andrick::AndrickEventQueue::addEventToQueue(new andrick::QuitEvent());
		}

		andrick::InputProcessor::get()->update(deltaTime);
	}

	//Convenience method so you don't have to write that monster line every time you want a keybinding.
	const andrick::AndrickKeyBinding* InputData::getKeyBinding(SettingsData::EnumGameSetting settingType)
	{
		return andrick::InputProcessor::get()->getKeyBinding(static_cast<andrick::GameSetting::EnumSetting>(settingType));
	}
}