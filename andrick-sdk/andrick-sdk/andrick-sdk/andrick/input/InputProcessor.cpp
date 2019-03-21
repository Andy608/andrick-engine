#include "InputProcessor.h"
#include "../logger/LoggerMaster.h"
#include "../event/AndrickEventQueue.h"
#include "../window/AndrickWindow.h"
#include <GLFW/glfw3.h>

namespace andrick
{
	InputProcessor* InputProcessor::mspInstance = nullptr;
	const std::string InputProcessor::msCLASS_NAME = "InputProcessor";
	GLuint InputProcessor::msMAX_KEYS_DOWN = 6;

	GLboolean InputProcessor::init()
	{
		GLboolean success = GL_FALSE;

		if (!mspInstance)
		{
			mspInstance = new InputProcessor();
			LoggerMaster::getUniversalLogger().logInfo(mspInstance->msCLASS_NAME, "Initializing the InputProcessor.");
			success = (mspInstance != nullptr);
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(mspInstance->msCLASS_NAME, "The InputProcessor is already initialized.");
		}

		return success;
	}

	void InputProcessor::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	InputProcessor::InputProcessor() :
		mMousePosition(glm::ivec2()),
		mMouseDelta(glm::ivec2())
	{
		AndrickEventQueue::addListener(EnumAndrickEvent::KEYBOARD_EVENT, this);
		AndrickEventQueue::addListener(EnumAndrickEvent::MOUSE_MOVE_EVENT, this);
	}

	InputProcessor::~InputProcessor()
	{
		auto iter = mKeyBindings.begin();
		for (; iter != mKeyBindings.end(); ++iter)
		{
			delete *iter;
		}

		mKeyBindings.clear();
	}

	void InputProcessor::update(const GLdouble& deltaTime)
	{
		//Update glfw events
		AndrickWindow::pollEvents();

		//Update key bindings
		auto iter = mKeyBindings.begin();
		for (; iter != mKeyBindings.end(); ++iter)
		{
			(*iter)->update(deltaTime);
		}

		mMouseDelta.x = 0.0f;
		mMouseDelta.y = 0.0f;

		/*
		* Since we can't access glfw's event queue,
		* we will add new events to the event queue
		* in the callbacks and then here we will update
		* the queue and process them accordingly.
		*/
		AndrickEventQueue::update(deltaTime);
	}

	void InputProcessor::handleEvent(const AndrickEvent& theEvent)
	{
		if (theEvent.getEventType() == EnumAndrickEvent::KEYBOARD_EVENT)
		{
			const KeyboardEvent& keyboardEvent = static_cast<const KeyboardEvent&>(theEvent);

			keyboardEvent.isDown ? addKeyPressed(keyboardEvent.inputCode) : removeKeyPressed(keyboardEvent.inputCode);
			updateKeyBindingPresses();
		}
		else if (theEvent.getEventType() == EnumAndrickEvent::MOUSE_MOVE_EVENT)
		{
			const MouseMoveEvent& mouseMoveEvent = static_cast<const MouseMoveEvent&>(theEvent);

			mMousePosition.x = static_cast<GLfloat>(mouseMoveEvent.newX);
			mMousePosition.y = static_cast<GLfloat>(mouseMoveEvent.newY);

			mMouseDelta.x = static_cast<GLfloat>(mouseMoveEvent.newX - mouseMoveEvent.previousX);
			mMouseDelta.y = static_cast<GLfloat>(mouseMoveEvent.newY - mouseMoveEvent.previousY);

			/*LoggerMaster::getUniversalLogger().logWarn("InputProcessor",
			"New X: " + std::to_string(mouseMoveEvent.newX) + ", " +
			"New Y: " + std::to_string(mouseMoveEvent.newY) + ", " +
			"Old X: " + std::to_string(mouseMoveEvent.previousX) + ", " +
			"Old Y: " + std::to_string(mouseMoveEvent.previousY) + ", " +
			"Delta X: " + std::to_string(mMouseDelta.x) + ", " +
			"Delta Y: " + std::to_string(mMouseDelta.y));*/
		}
	}

	//If a keybinding matches the keysdown, set it to pressed.
	void InputProcessor::updateKeyBindingPresses()
	{
		GLuint currentDownCount;

		auto keyBindingsIter = mKeyBindings.begin();
		for (; keyBindingsIter != mKeyBindings.end(); ++keyBindingsIter)
		{
			//The custom keys from the current keybinding.
			const std::set<GLuint>& customKeySetting = (*keyBindingsIter)->mKeySetting->mCustomKeys;
			currentDownCount = 0;

			auto customKeysIter = customKeySetting.begin();
			for (; customKeysIter != customKeySetting.end(); ++customKeysIter)
			{
				if (mKeysDown.find(*customKeysIter) != mKeysDown.end())
				{
					++currentDownCount;
				}
			}

			(*keyBindingsIter)->setPressed(currentDownCount == customKeySetting.size());
		}
	}

	void InputProcessor::addKeyPressed(GLuint asciiValue)
	{
		if (mKeysDown.size() < msMAX_KEYS_DOWN)
		{
			auto iter = mKeysDown.insert(asciiValue);
			//printPressedKeys();
		}
	}

	void InputProcessor::removeKeyPressed(GLuint asciiValue)
	{
		mKeysDown.erase(asciiValue);
		//printPressedKeys();
	}

	GLboolean InputProcessor::isKeyBindingPressed(AndrickKeyBinding* key)
	{
		auto iter = mKeyBindings.find(key);
		return (iter != mKeyBindings.end() && (*iter)->isPressed());
	}

	void InputProcessor::printPressedKeys() const
	{
		std::string keyList = "Active Keys: ";
		std::set<GLuint>::iterator it;

		if (mKeysDown.size() > 0)
		{
			keyList += std::to_string(*mKeysDown.begin());

			for (it = ++mKeysDown.begin(); it != mKeysDown.end(); ++it)
			{
				keyList += ", " + std::to_string(*it);
			}
		}

		LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, keyList);
	}

	const AndrickKeyBinding* InputProcessor::getKeyBinding(GameSetting::EnumSetting settingType)
	{
		auto iter = mKeyBindings.begin();
		for (; iter != mKeyBindings.end(); ++iter)
		{
			if ((*iter)->mKeySetting->getSettingID() == settingType)
			{
				return *iter;
			}
		}

		LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "No keybinding with that setting type. Returning null.");
		return nullptr;
	}
}