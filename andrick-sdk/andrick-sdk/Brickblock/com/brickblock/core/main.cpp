#include <iostream>
#include <andrick\core\AndrickCore.h>
#include <andrick\logger\LoggerMaster.h>

int main()
{
	andrick::AndrickCore::initAndrick();
	andrick::LoggerMaster::getUniversalLogger().logWarn("main", "Hello andrick-sdk!");
	std::cin.get();

	andrick::AndrickCore::cleanupAndrick();

	return 0;
}
