#ifndef BB_ASSET_LOADER_H_
#define BB_ASSET_LOADER_H_

#include <glad/glad.h>
#include <andrick/memory/TrackableObject.h>
#include <andrick/memory/NonCopyable.h>
#include <andrick/filesystem/path/directory/DirectoryLocation.h>

namespace bb
{
	class AssetLoader : public andrick::TrackableObject, public andrick::NonCopyable
	{
		friend class Brickblock;

	private:
		static const std::string msCLASS_NAME;
		static AssetLoader* mspInstance;

		static GLboolean init();
		static void cleanup();

		GLboolean mIsLoaded;

		AssetLoader();
		inline ~AssetLoader() {};

		void initAssets() const;
	};
}

#endif