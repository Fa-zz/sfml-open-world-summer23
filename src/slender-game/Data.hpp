#pragma once

namespace DataSettings {
    // ENGINE DATA
    inline const float videoModeWidth = 1920;
    inline const float videoModeHeight = 1080;
    inline const float frameRateLimit = 144;

    inline const float gameWorldSizeX = 12000.f;
    inline const float gameWorldSizeY = 12000.f;

    inline const float playerMoveSpeedWalk = 1.5f;
    inline const float playerRadiusDefault = 25.f;

    inline const float lightRangeFull = 600.f;
    inline const float lightRangeOff = 200.f;


    // GENERATING OBJECTS DATA
    inline const int numTrees = 800;
    inline const int numFallenTrees = 60;
    inline const int numRocks = 1000;
    inline const int numMudPatches = 10;
    inline const int numBushes = 30;
    inline const int numShrubs = 700;

    // GENERATING ITEMS DATA
    inline const int numBatteries = 20;

}

class Data {
private:
    int playerSanity;

    // Init functions
    void initPlayerData();
public:
    Data();
    int getPlayerSanity();
    void setPlayerSanity(int newSanity);
};