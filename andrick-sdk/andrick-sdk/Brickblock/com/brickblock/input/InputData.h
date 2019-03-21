#ifndef BB_INPUT_DATA_H_
#define BB_INPUT_DATA_H_

#include <andrick/memory/TrackableObject.h>
#include <andrick/memory/NonCopyable.h>
#include <andrick/input/InputProcessor.h>
#include <map>
#include <string>
#include "../setting/SettingsData.h"

namespace bb
{
	class InputData : public andrick::TrackableObject, andrick::NonCopyable
	{
		friend class Brickblock;

	public:
		static const andrick::AndrickKeyBinding* getKeyBinding(SettingsData::EnumGameSetting settingType);
		static inline const glm::vec2 getMousePosition() { return andrick::InputProcessor::get()->getMousePosition(); };
		static inline const glm::vec2 getMouseDelta() { return andrick::InputProcessor::get()->getMouseDelta(); };

		void update(const GLdouble& deltaTime);

	private:
		static InputData* mspInstance;
		static const std::string msCLASS_NAME;

		static GLboolean init();
		static void cleanup();

		//These are registered/deleted in the InputProcessor class.
		andrick::AndrickKeyBinding* mForwardKeyBinding;
		andrick::AndrickKeyBinding* mBackwardKeyBinding;
		andrick::AndrickKeyBinding* mLeftKeyBinding;
		andrick::AndrickKeyBinding* mRightKeyBinding;
		andrick::AndrickKeyBinding* mUpKeyBinding;
		andrick::AndrickKeyBinding* mDownKeyBinding;

		andrick::AndrickKeyBinding* mQuitKeyBinding;


		InputData();
		~InputData();

	};
}

#endif