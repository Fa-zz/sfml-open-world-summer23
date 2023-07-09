#pragma once

#include <iostream>

namespace DataSettings {
    // ENGINE DATA
    inline const float videoModeWidth = 1920;
    inline const float videoModeHeight = 1080;
    inline const float frameRateLimit = 144;

    inline const float gameWorldSizeX = 12000.f;
    inline const float gameWorldSizeY = 12000.f;

    inline const float playerMoveSpeedWalk = 2.f;
    inline const float playerRadiusDefault = 25.f;

    inline const float lightRangeFull = 600.f;
    inline const float lightRangeOff = 200.f;

    // GENERATING OBJECTS DATA
    inline const int numTrees = 900;
    inline const int numFallenTrees = 70;
    inline const int numRocks = 2000;
    inline const int numMudPatches = 10;
    inline const int numBushes = 30;
    inline const int numShrubs = 800;

    // GENERATING ITEMS DATA
    inline const int numBatteries = 20;
    inline const int numHolySymbols = 20;
    inline const int numMushrooms = 10;

    // MESSAGE LOG DATA
    inline const std::string useBatteryString = "Your flashlight flickers more strongly.";
    inline const std::string useHolySymbolString1 = "You feel more optimistic.";
    inline const std::string useHolySymbolString2 = "You feel healed, in both dimensions.";

}