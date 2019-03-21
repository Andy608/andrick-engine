#include "AndrickCore.h"
#include "../filesystem/FileSystem.h"
#include "../logger/LoggerMaster.h"
//#include "../window/GLARWindow.h"
//#include "../event/EventQueue.h"
//#include "../input/InputProcessor.h"
//#include "../asset/AssetManager.h"
//#include "../render/RenderManager.h"
//#include "../setting/SettingsProcessor.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image/stb_image.h>
#include <string>

using namespace andrick;

const std::string AndrickCore::msCLASS_NAME = "GLAR";
GLboolean AndrickCore::smIsInitialized = false;

GLboolean AndrickCore::initAndrick()
{
	GLboolean success = GL_TRUE;

	if (!smIsInitialized)
	{
		//Eventually this could be in a nice initialization handler class
		//with queues and error handling, but for now this is fine.

		//Pre-init
		//Foundation of GLAR.
		ObjectTracker::init();

		if (!FileSystem::init())
		{
			success = GL_FALSE;
		}

		//Init
		//Logger needs to be initialized for other things.
		if (!success || !LoggerMaster::init())
		{
			success = GL_FALSE;
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Failed to init " + LoggerMaster::msCLASS_NAME);
		}

		/*if (!success || !EventQueue::init())
		{
			success = GL_FALSE;
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Failed to init " + EventQueue::msCLASS_NAME);
		}

		if (!success || !InputProcessor::init())
		{
			success = GL_FALSE;
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Failed to init " + InputProcessor::msCLASS_NAME);
		}

		if (!success || !GLARWindow::init())
		{
			success = GL_FALSE;
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Failed to init " + GLARWindow::msCLASS_NAME);
		}

		if (!success || !AssetManager::init())
		{
			success = GL_FALSE;
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Failed to init " + AssetManager::msCLASS_NAME);
		}

		if (!success || !RenderManager::init())
		{
			success = GL_FALSE;
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Failed to init " + RenderManager::msCLASS_NAME);
		}

		if (!success || !SettingsProcessor::init())
		{
			success = GL_FALSE;
			LoggerMaster::getUniversalLogger().logCritical(msCLASS_NAME, "Failed to init " + SettingsProcessor::msCLASS_NAME);
		}*/
	}

	if (!success)
	{
		cleanupAndrick();
	}

	return success;
}

GLboolean AndrickCore::cleanupAndrick()
{
	////Cleanup SettingsProcessor
	//SettingsProcessor::cleanup();

	////Cleanup MeshRenderer
	//RenderManager::cleanup();

	////Cleanup AssetManager
	//AssetManager::cleanup();

	////Cleanup GLFW
	//GLARWindow::cleanup();

	////Cleanup Input Processor
	//InputProcessor::cleanup();

	////Cleanup Event Queue
	//EventQueue::cleanup();

	//Cleanup File System
	FileSystem::cleanup();

	//Cleanup Memory Tracker
	ObjectTracker::smpObjectTracker->printRecords(LoggerMaster::getUniversalLogger());
	ObjectTracker::cleanup();

	LoggerMaster::cleanup();

	return GL_FALSE;
}
