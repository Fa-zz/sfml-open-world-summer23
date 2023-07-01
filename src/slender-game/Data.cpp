#include "Data.hpp"

void Data::initPlayerData() {
    playerSanity = 100;
}

Data::Data() {
    initPlayerData();
}

int Data::getPlayerSanity() {
    return playerSanity;
}

void Data::setPlayerSanity(int newSanity) {
    playerSanity = newSanity;
}