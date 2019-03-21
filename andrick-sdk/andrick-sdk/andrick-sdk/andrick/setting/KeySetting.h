#ifndef KEY_SETTING_H_
#define KEY_SETTING_H_

#include "GameSetting.h"
#include <set>

namespace andrick
{
	class KeySetting : public GameSetting
	{
		friend class InputProcessor;
	public:
		KeySetting(GameSetting::EnumSetting settingID, const std::string settingName, const std::set<GLuint> defaultKeys);
		virtual ~KeySetting();

		virtual std::string toReadableString() const override;						//Nice name to print in console.
		virtual std::string toFileString() const override;							//How to print it in a file.
		virtual void loadFromString(const std::string& settingInFile) override;		//Load setting from string data
		virtual GLboolean isModified() const override;								//Does the setting have custom values.
		virtual void resetCustomValue() override;									//Reset the setting to it's defaults.

		void setCustomKeyBinding(const std::set<GLuint>& customKeys);

		const GLuint getDefaultBindingLength() const;
		const GLuint getCustomBindingLength() const;

	protected:
		const std::set<GLuint> mDEFAULT_KEYS;
		std::set<GLuint> mCustomKeys;

	private:
		static const std::string msCLASS_NAME;
		static const GLchar msKEY_DELIMITER;
	};
}

#endif