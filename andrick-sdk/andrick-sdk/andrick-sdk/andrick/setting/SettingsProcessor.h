#ifndef SETTINGS_PROCESSOR_H_
#define SETTINGS_PROCESSOR_H_

#include "../memory/TrackableObject.h"
#include "../memory/NonCopyable.h"
#include "../filesystem/path/directory/DirectoryLocation.h"
#include "../filesystem/path/file/FileLocation.h"
#include "KeySetting.h"
#include <set>

namespace andrick
{
	class SettingsProcessor : public TrackableObject, NonCopyable
	{
		friend class AndrickCore;

	public:
		static const GLchar msFILE_DELIMITER;
		static inline SettingsProcessor* getInstance() { return mspInstance; }

		GLboolean registerSetting(GameSetting* setting);
		GameSetting* getGameSetting(GameSetting::EnumSetting settingType);

		//Maybe this in the future. For now you can change the setting in the txt file though.
		//GLboolean changeSetting(EnumSetting settingType, GameSetting* setting);

		//Saves settings to file.
		void saveSettings();

		//Loads settings from file.
		void loadSettings();

	private:
		static const DirectoryLocation msSETTINGS_DIR;
		static const std::string msCLASS_NAME;
		static SettingsProcessor* mspInstance;

		static GLboolean init();
		static void cleanup();

		std::set<GameSetting*> mSettings;

		FileLocation mSettingsFile;

		SettingsProcessor();
		~SettingsProcessor();
	};
}

#endif