//#include <andrick/asset/AssetManager.h>
#include <andrick/input/InputProcessor.h>
#include <andrick/logger/LoggerMaster.h>
#include <andrick/util/Timer.h>
#include <andrick/util/math/MathHelper.h>

#include "Brickblock.h"
//#include "../asset/AssetLoader.h"
//#include "../block/util/BlockList.h"
#include "../input/InputData.h"
#include "../setting/SettingsData.h"

#include <chrono>
#include <thread>

namespace bb
{
	const std::string Brickblock::msCLASS_NAME = "Brickblock";
	const std::string Brickblock::msLOGGER_ID = msCLASS_NAME + " Logger";
	Brickblock* Brickblock::mspInstance = nullptr;

	GLboolean Brickblock::initGame(/*command arguments can go here in the future*/)
	{
		if (!mspInstance)
		{
			mspInstance = new Brickblock();
		}
		else
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logCritical(msCLASS_NAME, msCLASS_NAME + " is already initialized.");
			return GL_FALSE;
		}

		//We need to create a fancy init here to handle everything.

		SettingsData::init();//Register the settings.
		InputData::init();//Bind settings to input.

		if (!MainDisplay::initInstance())
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logCritical(msCLASS_NAME, "Error initializing Window.");
			cleanupGame();
			return GL_FALSE;
		}

		//Load the resources.
		//AssetLoader::init();
		//AssetLoader::mspInstance->initAssets();
		//andrick::AssetManager::loadAssets();

		//BlockList::init();
		//BlockList::mspInstance->loadBlocks();
		//BlockList::mspInstance->registerBlocks();

		//Move this somewhere else
		///andrick::AndrickWindow::disableCursor(MainDisplay::mspInstance->mpWindow);
		//mspInstance->mpUniverse = new Universe("Test World");

		/////////////////////

		return GL_TRUE;
	}

	void Brickblock::cleanupGame()
	{
		MainDisplay::cleanupInstance();

		if (mspInstance)
		{
			//Move these to an initialization handler in the future.
			SettingsData::cleanup();
			InputData::cleanup();
			//AssetLoader::cleanup();
			//BlockList::cleanup();

			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	GLboolean Brickblock::runGame()
	{
		if (!mspInstance)
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logWarn(msCLASS_NAME, msCLASS_NAME + " is NOT initialized. Cannot start game.");
			return GL_FALSE;
		}
		else if (mspInstance->mIsRunning)
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logWarn(msCLASS_NAME, msCLASS_NAME + " is already running.");
			return GL_FALSE;
		}
		else
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logWarn(msCLASS_NAME, "Starting " + msCLASS_NAME + "!");

			mspInstance->loop();

			//This isn't going to be called until the very end because the loop is going to run for the duration of the game.
			return GL_TRUE;
		}
	}

	Brickblock::Brickblock() : mIsRunning(GL_FALSE)
	{

	}

	Brickblock::~Brickblock()
	{
		andrick::LoggerMaster::getLogger(msLOGGER_ID)->logTrace(msCLASS_NAME, "Destroying " + msCLASS_NAME + ".");

		//Temporary Variables
		//delete mpUniverse;
		//mpUniverse = nullptr;
	}

	void Brickblock::loop()
	{
		if (mIsRunning)
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logWarn(msCLASS_NAME, "The game loop is already running!");
		}
		else
		{
			mIsRunning = GL_TRUE;

			GLdouble lastTime = andrick::Timer::getCurrentTime();
			GLdouble currentTime = 0.0f;
			GLdouble elapsedTime = 0.0f;
			GLdouble lagTime = 0.0f;

			//For now, stop the game when the window should close
			while (!andrick::AndrickWindow::shouldClose(MainDisplay::mspInstance->mpWindow))
			{
				currentTime = andrick::Timer::getCurrentTime();
				elapsedTime = currentTime - lastTime;
				lastTime = currentTime;
				lagTime += elapsedTime;

				while (lagTime >= mTIME_SLICE)
				{
					//Move this to the AndrickWindow class in the GLAR library.
					update(mTIME_SLICE);
					lagTime -= mTIME_SLICE;
				}

				render(lagTime / mTIME_SLICE);

				if (SettingsData::getSetting<andrick::BooleanSetting*>(SettingsData::V_SYNC))
				{
					//TODO: Sleep until we reach the end of the time slice.
					//std::this_thread::sleep_for(std::chrono::seconds(double(mTIME_SLICE - (andrick::Timer::getCurrentTime() - lastTime))));
				}
			}

			mIsRunning = GL_FALSE;
		}
	}

	static int ticks = 0;
	static int frames = 0;

	static float sinFun;
	static float cosFun;

	void Brickblock::update(const GLdouble& deltaTime)
	{
		//Poll for input and update the event queue
		InputData::mspInstance->update(deltaTime);

		MainDisplay::mspInstance->mpWindow->update(deltaTime);
		//mpUniverse->update(deltaTime);

		ticks++;

		if (ticks % mTICKS_PER_SECOND == 0)
		{
			andrick::LoggerMaster::getLogger(msLOGGER_ID)->logTrace(msCLASS_NAME, "Ticks: " + std::to_string(mTICKS_PER_SECOND) + " | FPS: " + std::to_string(frames));
			frames = 0;
		}

		if (ticks % mTICKS_PER_SECOND == 360)
		{
			ticks = 0;
		}

		sinFun = sin(andrick::MathHelper::toRadians(ticks)) * 0.5f + 0.5f;
		cosFun = cos(andrick::MathHelper::toRadians(ticks)) * 0.5f + 0.5f;
	}

	void Brickblock::render(const GLdouble& alpha)
	{
		frames++;

		MainDisplay::mspInstance->mpWindow->clearColor(sinFun, sinFun + cosFun, cosFun, 1.0f);
		//MainDisplay::mspInstance->mpWindow->render(alpha);

		//mpUniverse->render(alpha);

		MainDisplay::mspInstance->mpWindow->flip();
	}
}