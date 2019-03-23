#include "SettingsProcessor.h"
#include "../filesystem/FileSystem.h"
#include "../logger/LoggerMaster.h"
#include "../filesystem/path/file/io/string/StringFileReader.h"
#include "../filesystem/path/file/io/string/StringFileWriter.h"

namespace andrick
{
	const DirectoryLocation SettingsProcessor::msSETTINGS_DIR = DirectoryLocation("", "settings", PathLocation::EnumPathType::RELATIVE_PATH);
	const std::string SettingsProcessor::msCLASS_NAME = "SettingsProcessor";
	SettingsProcessor* SettingsProcessor::mspInstance = nullptr;
	const GLchar SettingsProcessor::msFILE_DELIMITER = '=';

	GLboolean SettingsProcessor::init()
	{
		if (!mspInstance)
		{
			/*try
			{
				mspInstance = new SettingsProcessor();
				LoggerMaster::getUniversalLogger().logTrace(mspInstance->msCLASS_NAME, "Initializing the SettingsProcessor.");
			}
			catch (const std::invalid_argument& e)
			{
				LoggerMaster::getUniversalLogger().logError(msCLASS_NAME, e.what());
				mspInstance = nullptr;
			}*/

			GLboolean success = GL_FALSE;

			if (!mspInstance)
			{
				mspInstance = new SettingsProcessor();
				LoggerMaster::getUniversalLogger().logInfo(mspInstance->msCLASS_NAME, "Initializing the SettingsProcessor.");
				success = (mspInstance != nullptr);
			}
			else
			{
				LoggerMaster::getUniversalLogger().logWarn(mspInstance->msCLASS_NAME, "The SettingsProcessor is already initialized.");
			}
		}

		return (mspInstance != nullptr);
	}

	void SettingsProcessor::cleanup()
	{
		if (mspInstance)
		{
			delete mspInstance;
			mspInstance = nullptr;
		}
	}

	GLboolean SettingsProcessor::registerSetting(GameSetting* setting)
	{
		auto iter = mSettings.insert(setting);

		if (!iter.second)
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "SettingID: " + (*iter.first)->getSettingName() + " is already registered to enum. Cannot register new SettingID: " + setting->getSettingName() + ". Deleting.");
			delete setting;
		}

		return iter.second;
	}

	SettingsProcessor::SettingsProcessor() : 
		mSettingsFile(FileLocation(msSETTINGS_DIR, "settings"))
	{
		if (!FileSystem::getFS()->isDirectoryCreated(msSETTINGS_DIR) && !FileSystem::getFS()->createDirectory(msSETTINGS_DIR))
		{
			std::string err = "Unable to create Settings directory at: " + msSETTINGS_DIR.getPath();
			throw std::invalid_argument(err);
		}
		else if (FileSystem::getFS()->isFileCreated(mSettingsFile))
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Settings file exists: " + mSettingsFile.getPath());
		}
		else if (FileSystem::getFS()->createFile(mSettingsFile))
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Successfully created file at: " + mSettingsFile.getPath());
		}
		else
		{
			std::string err = "Unable to create Game Settings file at: " + mSettingsFile.getPath();
			throw std::invalid_argument(err);
		}
	}

	SettingsProcessor::~SettingsProcessor()
	{
		auto iter = mSettings.begin();
		for (; iter != mSettings.end(); ++iter)
		{
			delete *iter;
		}
		
		mSettings.clear();
	}

	void SettingsProcessor::saveSettings()
	{
		auto iter = mSettings.begin();
		std::vector<std::string> settings;

		for (; iter != mSettings.end(); ++iter)
		{
			settings.push_back((*iter)->toFileString());
		}

		StringFileWriter::getInstance().writeLinesInFile(mSettingsFile, settings);
	}

	void SettingsProcessor::loadSettings()
	{
		if (FileSystem::getFS()->isFileCreated(mSettingsFile))
		{
			std::vector<std::string> fileLines;
			StringFileReader::getInstance().getContentsByLine(mSettingsFile, fileLines);

			std::string currentLine;
			std::string settingName;
			std::string settingAttrib;
			GLboolean found;

			GLuint i;
			GLuint j;
			for (i = 0; i < fileLines.size(); ++i)
			{
				currentLine = fileLines.at(i);
				for (j = 0; j < currentLine.size(); ++j)
				{
					if (currentLine.at(j) == msFILE_DELIMITER)
					{
						settingName = currentLine.substr(0, j);
						settingAttrib = currentLine.substr(j + 1);

						auto iter = mSettings.begin();
						found = GL_FALSE;

						for (; iter != mSettings.end(); ++iter)
						{
							if (settingName.compare((*iter)->getSettingName()) == 0)
							{
								found = GL_TRUE;
								(*iter)->loadFromString(settingAttrib);
								break;
							}
						}

						if (!found)
						{
							LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "Skipping unknown setting: \'" + currentLine + "\'");
						}
					}
				}
			}
		}
		else
		{
			LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "No settings file to load from. Using default settings.");
		}
	}

	GameSetting* SettingsProcessor::getGameSetting(GameSetting::EnumSetting settingType)
	{
		auto iter = mSettings.begin();

		for (; iter != mSettings.end(); ++iter)
		{
			if ((*iter)->getSettingID() == settingType)
			{
				return *iter;
			}
		}

		LoggerMaster::getUniversalLogger().logWarn(msCLASS_NAME, "Could not find setting type. Returning null.");
		return nullptr;
	}
}