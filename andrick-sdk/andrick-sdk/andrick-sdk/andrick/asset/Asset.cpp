#include "Asset.h"
#include "../logger/LoggerMaster.h"

namespace andrick
{
	const std::string Asset::msCLASS_NAME = "Asset";

	Asset::Asset(const std::string& assetID) :
		mASSET_ID(assetID),
		mIsLoaded(GL_FALSE),
		mIsRegistered(GL_FALSE)
	{

	}

	Asset::~Asset()
	{
		if (mIsLoaded)
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Uh oh, the asset: \'" + mASSET_ID + "\' was never unloaded. :o");
		}
		else
		{
			LoggerMaster::getUniversalLogger().logTrace(msCLASS_NAME, "Deleting Asset: \'" + mASSET_ID + "\'");
		}
	}
}