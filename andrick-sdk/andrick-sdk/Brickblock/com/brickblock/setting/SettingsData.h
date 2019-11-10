#ifndef BB_SETTINGS_DATA_H_
#define BB_SETTINGS_DATA_H_

#include <andrick/memory/TrackableObject.h>
#include <andrick/memory/NonCopyable.h>
#include <andrick/setting/KeySetting.h>
#include <andrick/setting/IntegerSetting.h>
#include <andrick/setting/BooleanSetting.h>
#include <andrick/logger/LoggerMaster.h>
#include <glad/glad.h>

namespace bb
{
	class SettingsData : public andrick::TrackableObject, andrick::NonCopyable
	{
		friend class Brickblock;
		friend class InputData;

	public:
		enum EnumGameSetting : GLuint
		{
			//Keybindings
			QUIT_KEYBINDING = andrick::GameSetting::EnumSetting::NUM_SETTING_TYPES + 1,
			//PAUSE_KEYBINDING,
			CAMERA_FORWARD_KEYBINDING,
			CAMERA_BACKWARD_KEYBINDING,
			CAMERA_LEFT_KEYBINDING,
			CAMERA_RIGHT_KEYBINDING,
			CAMERA_UP_KEYBINDING,
			CAMERA_DOWN_KEYBINDING,

			//Other settings
			MOUSE_SENSITIVITY,
			V_SYNC
		};

		static andrick::GameSetting::EnumSetting convertSetting(EnumGameSetting gameSetting);
		
		//andrick::KeySetting* getKeySetting(EnumGameSetting settingType);
		
		template <typename T>
		static T getSetting(EnumGameSetting settingType)
		{
			andrick::GameSetting* setting = andrick::SettingsProcessor::getInstance()->getGameSetting(SettingsData::convertSetting(settingType));

			if (setting->is<T>())
			{
				return static_cast<T>(setting);
			}
			else
			{
				andrick::LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, "Could not cast the setting to specified type. Returning null.");
				return nullptr;
			}
		}

	private:
		//Implement this class. Move Settings from InputTranslator to here. Move Save and Load from InputTranslator to here too.
		static GLboolean init();
		static void cleanup();

		static SettingsData* mspInstance;
		static const std::string msCLASS_NAME;

		andrick::KeySetting* mMoveForwardSetting;
		andrick::KeySetting* mMoveBackwardSetting;
		andrick::KeySetting* mMoveLeftSetting;
		andrick::KeySetting* mMoveRightSetting;
		andrick::KeySetting* mMoveUpSetting;
		andrick::KeySetting* mMoveDownSetting;

		andrick::GameSetting* mPauseSetting;
		andrick::GameSetting* mQuitSetting;

		andrick::IntegerSetting* mMouseSensitivity;
		andrick::BooleanSetting* mVerticalSync;

		SettingsData();
		~SettingsData();
	};
}

#endif