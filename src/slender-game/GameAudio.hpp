#pragma once

#include <iostream>

#include <SFML/Audio.hpp>

class GameAudio {
private:
    void initMusic();
    sf::Sound loadSounds(std::string filename);
    void initSounds();

    sf::Music ambience;
    sf::SoundBuffer buffer;
    sf::Sound flashlightClick;
public:
    GameAudio();
    void playLoopingAmbience();
    void playFlashlightClick();
};