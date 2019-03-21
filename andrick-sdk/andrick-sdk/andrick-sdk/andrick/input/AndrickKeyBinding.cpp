#include "AndrickKeyBinding.h"

namespace andrick
{
	const std::string AndrickKeyBinding::msCLASS_NAME = "AndrickKeyBinding";

	AndrickKeyBinding::AndrickKeyBinding(KeySetting* keySetting) :
		mKeySetting(keySetting)
	{

	}

	AndrickKeyBinding::~AndrickKeyBinding()
	{

	}

	const GLboolean& AndrickKeyBinding::isPressed() const
	{
		return mIsPressed;
	}

	void AndrickKeyBinding::setPressed(GLboolean isPressed)
	{
		mIsPressed = isPressed;
	}

	void AndrickKeyBinding::update(const GLdouble& deltaTime)
	{
		//Might be a better way to do this instead of in update(). But we can look into that in the future.
		mIsPressed ? mTimePressed += deltaTime : mTimePressed = 0;
	}
}