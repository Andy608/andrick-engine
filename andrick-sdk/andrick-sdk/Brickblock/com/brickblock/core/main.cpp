#include <iostream>
#include <andrick/core/AndrickCore.h>
#include <andrick/logger/LoggerMaster.h>
#include "Brickblock.h"

int main()
{

	if (andrick::AndrickCore::initAndrick())
	{
		andrick::LoggerMaster::getUniversalLogger().logWarn("main", "Hello andrick-sdk!");
		bb::Brickblock::initGame();
		bb::Brickblock::runGame();
		bb::Brickblock::cleanupGame();
		andrick::AndrickCore::cleanupAndrick();
	}

	std::cin.get();

	return 0;
}
