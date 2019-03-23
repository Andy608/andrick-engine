#ifndef ANDRICK_ASSET_H_
#define ANDRICK_ASSET_H_

#include <glad/glad.h>
#include "../memory/TrackableObject.h"
#include "../memory/NonCopyable.h"

namespace andrick
{
	class Asset : public TrackableObject, public NonCopyable
	{
		friend class AssetPack;

	public:
		Asset(const std::string& assetID);
		virtual ~Asset();

		inline GLboolean isLoaded() const { return mIsLoaded; };
		inline GLboolean isRegistered() const { return mIsRegistered; };
		inline const std::string& getID() const { return mASSET_ID; };

		virtual GLboolean load() = 0;
		virtual GLboolean unload() = 0;

	protected:
		const std::string mASSET_ID;
		GLboolean mIsLoaded;
		GLboolean mIsRegistered;

	private:
		static const std::string msCLASS_NAME;
	};
}

#endif