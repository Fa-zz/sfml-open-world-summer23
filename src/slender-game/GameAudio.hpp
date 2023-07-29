#pragma once

#include <iostream>

#include <SFML/Audio.hpp>

class GameAudio {
private:
    void initMusic();
    int loadSounds();
    void initSounds();

    sf::Music ambience;
    sf::SoundBuffer fCBuffer;
    sf::Sound flashlightClick;
    sf::SoundBuffer aMBuffer;
    sf::Sound appearanceMusic;
    sf::SoundBuffer gWBuffer;
    sf::Sound ghostlyWhispers;
public:
    GameAudio();
    void playLoopingAmbience();
    void playFlashlightClick();
    void playAppearanceMusic();
    void playGhostlyWhispers();

    sf::Sound::Status getAppearanceMusicStatus();
    sf::Sound::Status getGhostlyWhispersStatus();
};