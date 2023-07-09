#include "GameAudio.hpp"

void GameAudio::initMusic() {
    if (!ambience.openFromFile("audiomass-free-night-sounds.ogg"))
        std::cout << "Error opening ambience music file!" << std::endl;
    ambience.setVolume(50);
}

sf::Sound GameAudio::loadSounds(std::string filename) {
    buffer.loadFromFile(filename);
    return sf::Sound(buffer);
    
}

void GameAudio::initSounds() {
    flashlightClick = loadSounds("flashlight-click-sfx.ogg");
    flashlightClick.setVolume(25);
}

GameAudio::GameAudio() {
    initMusic();
    initSounds();
}

void GameAudio::playLoopingAmbience() {
    ambience.play();
    ambience.setLoop(true);
}

void GameAudio::playFlashlightClick() {
    flashlightClick.play();
}