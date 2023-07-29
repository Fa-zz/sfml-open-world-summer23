#include "GameAudio.hpp"

void GameAudio::initMusic() {
    if (!ambience.openFromFile("audiomass-free-night-sounds.ogg"))
        std::cout << "Error opening ambience music file!" << std::endl;
    ambience.setVolume(50);
}

int GameAudio::loadSounds() {
    if (!fCBuffer.loadFromFile("flashlight-click-sfx.ogg") || 
    !aMBuffer.loadFromFile("dark-piano-tension.ogg") ||
    !gWBuffer.loadFromFile("ghostly-whispers-longer.ogg")) {
        // Handle loading error
        std::cout << "Cannot load from file" << std::endl;
        return -1;
    }
    
}

void GameAudio::initSounds() {
    flashlightClick.setBuffer(fCBuffer);
    flashlightClick.setVolume(25);

    appearanceMusic.setBuffer(aMBuffer);

    ghostlyWhispers.setBuffer(gWBuffer);
    ghostlyWhispers.setPitch(-15.f);
}

GameAudio::GameAudio() {
    loadSounds();
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

void GameAudio::playAppearanceMusic() {
    appearanceMusic.play();
    if (appearanceMusic.getStatus() == sf::Music::Status::Stopped) {
        ghostlyWhispers.play();
    }
}

void GameAudio::playGhostlyWhispers() {
    ghostlyWhispers.play();
}

sf::Sound::Status GameAudio::getAppearanceMusicStatus() {
    return appearanceMusic.getStatus();
}
sf::Sound::Status GameAudio::getGhostlyWhispersStatus() {
    return ghostlyWhispers.getStatus();
}