#ifndef ANDRICK_KEYBINDING_H_
#define ANDRICK_KEYBINDING_H_

#include "../memory/TrackableObject.h"
#include "../setting/KeySetting.h"
#include <glad/glad.h>

namespace andrick
{
	//An andrick keybinding is not tightly bound to a specific key on the key board. It is bound to a key setting. Depending on
	//what the key setting's data is, that is what this keybinding goes by for it being pressed or not.
	class AndrickKeyBinding : public TrackableObject
	{
		friend class InputProcessor;

	public:
		AndrickKeyBinding(KeySetting* keySetting);
		virtual ~AndrickKeyBinding();

		const GLboolean& isPressed() const;
		void setPressed(GLboolean isPressed);

		void update(const GLdouble& deltaTime);

		const GLdouble& getTimePressed() const { return mTimePressed; };

	protected:
		//Do not delete, memory managed in InputProcessor.
		KeySetting* mKeySetting;
		GLboolean mIsPressed;
		GLdouble mTimePressed;

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif