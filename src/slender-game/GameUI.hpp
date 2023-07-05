#pragma once

#include <iostream>

#include "CustomColors.hpp"

#include <SFML/Graphics.hpp>

class GameUI {
private:

    // Init font
    void initFont();

    //Init vars
    void initVars();

    // Font/text var
    sf:: Font font;
    sf::Text healthBarText;
    sf::Text sanityBarText;

    // Status texts
    sf::Text overHideableText;

    sf::Text statusMeditatingText;
    sf::Text statusHidingText;

    sf::Text breathBarText;

    // Health bar var
    sf::RectangleShape healthBarTop;
    sf::RectangleShape healthBarBottom;

    // Sanity bar
    sf::RectangleShape sanityBarTop;
    sf::RectangleShape sanityBarBottom;

    // Breath bar
    sf::RectangleShape breathBarTop;
    sf::RectangleShape breathBarBottom;

    // Meditating, hiding, still, holding breath
    bool isMeditating, isHiding;
    bool overHideable;
    bool renderHideableText;
    bool renderBreathBar;

public:
    void drawOverHideableText(int hideable);
    void drawStatusTexts();
    void drawHealthBar();
    void drawSanityBar();
    void drawBreathBar();

    sf::Vector2f getBarCurrent(std::string bar);

    void setSanityBar(int sanityChange);
    void setStatusMeditating(bool meditating);

    void setOverHideable(bool over);
    void setStatusHiding(bool hiding);

    void setBreathBar(int breathChange);
    void setDisplayBreathBar(bool display);

    void setHealthBar(int healthChange);

    GameUI();

    void renderUI(sf::RenderTarget& target);
};