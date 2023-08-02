#pragma once

#include <iostream>

namespace DataSettings {
    // ENGINE DATA
    inline const float videoModeWidth = 1920;
    inline const float videoModeHeight = 1080;
    inline const float frameRateLimit = 144;

    // inline const float gameWorldSizeX = 24000.f;
    inline const float gameWorldSizeX = 12000.f;
    inline const float gameWorldSizeY = 12000.f;

    inline const float playerMoveSpeedWalk = 2.f;
    inline const float playerRadiusDefault = 25.f;

    inline const float lightRangeFull = 600.f;
    inline const float lightRangeOff = 200.f;

    // UI DATA
    inline const int barSizeDefaultX = 300;
    inline const int barSizeDefaultY = 40;

    // MONSTER DATA
    inline const int lowerBound = 80; //80
    inline const int upperBound = 100; //100

    // GENERATING OBJECTS DATA
    inline const int numTrees = (900)*1;
    inline const int numFallenTrees = (50)*1;
    inline const int numRocks = (2000)*0.5;
    inline const int numMudPatches = (10)*1;
    inline const int numBushes = (30)*1;
    inline const int numShrubs = (800)*1;

    // GENERATING ITEMS DATA
    inline const int numBatteries = (20)*2;
    inline const int numHolySymbols = (20)*1;
    inline const int numMushrooms = (10)*2;
    inline const int numNotes = 5;
    inline int numTotalItems = numBatteries+numHolySymbols+numMushrooms;

    // MESSAGE LOG DATA
    inline const std::string useBatteryString = "Your flashlight flickers more strongly.";
    inline const std::string useHolySymbolString1 = "You feel more optimistic.";
    inline const std::string useHolySymbolString2 = "You feel healed, mentally and physically.";
    inline const std::string outOfBoundsString = "Stay within the forest until you have found the notes.";
    inline const std::string appearanceString = "You should hide.";
}