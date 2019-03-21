#ifndef BOOLEAN_SETTING_H_
#define BOOLEAN_SETTING_H_

#include "GameSetting.h"

namespace andrick
{
	class BooleanSetting : public GameSetting
	{
	public:
		BooleanSetting(EnumSetting settingID, const std::string& settingName, GLboolean boolean);
		virtual ~BooleanSetting();

		virtual std::string toReadableString() const override;						//Nice name to print in console.
		virtual std::string toFileString() const override;							//How to print it in a file.
		virtual void loadFromString(const std::string& settingInFile) override;		//Load setting from string data
		virtual GLboolean isModified() const override;								//Does the setting have custom values.
		virtual void resetCustomValue() override;									//Reset the setting to it's defaults.

		inline const GLboolean getCustomInteger() const { return mCustomBoolean; };

	protected:
		GLboolean mDefaultBoolean;
		GLboolean mCustomBoolean;

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif