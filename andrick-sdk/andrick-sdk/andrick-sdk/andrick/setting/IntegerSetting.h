#ifndef INTEGER_SETTING_H_
#define INTEGER_SETTING_H_

#include "GameSetting.h"

namespace andrick
{
	class IntegerSetting : public GameSetting
	{
	public:
		IntegerSetting(EnumSetting settingID, const std::string& settingName, GLint integer);
		virtual ~IntegerSetting();

		virtual std::string toReadableString() const override;						//Nice name to print in console.
		virtual std::string toFileString() const override;							//How to print it in a file.
		virtual void loadFromString(const std::string& settingInFile) override;		//Load setting from string data
		virtual GLboolean isModified() const override;								//Does the setting have custom values.
		virtual void resetCustomValue() override;									//Reset the setting to it's defaults.

		inline const GLint getCustomInteger() const { return mCustomInteger; };

	protected:
		GLint mDefaultInteger;
		GLint mCustomInteger;

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif