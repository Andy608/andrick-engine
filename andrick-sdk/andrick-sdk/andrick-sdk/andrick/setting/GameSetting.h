#ifndef ANDRICK_GAME_SETTING_H_
#define ANDRICK_GAME_SETTING_H_

#include "../memory/TrackableObject.h"
#include <glad/glad.h>
#include <string>

namespace andrick
{
	class GameSetting : public TrackableObject
	{
	public:
		enum EnumSetting : GLuint
		{
			NUM_SETTING_TYPES
		};

		inline GameSetting(EnumSetting settingID, const std::string& settingName) : mSETTING_ID(settingID), mSETTING_NAME(settingName) {};
		inline virtual ~GameSetting() {};

		EnumSetting getSettingID() const { return mSETTING_ID; };
		const std::string& getSettingName() const { return mSETTING_NAME; };

		virtual std::string toReadableString() const = 0;						//Nice name to print in console.
		virtual std::string toFileString() const = 0;							//How to print it in a file.
		virtual void loadFromString(const std::string& settingInFile) = 0;		//Load setting from string data
		virtual GLboolean isModified() const = 0;								//Does the setting have custom values.
		virtual void resetCustomValue() = 0;									//Reset the setting to it's defaults.

		template<typename T>
		GLboolean is()
		{
			return (dynamic_cast<T>(this) != nullptr);
		}

	protected:
		EnumSetting mSETTING_ID;
		const std::string mSETTING_NAME;
	};
}

#endif