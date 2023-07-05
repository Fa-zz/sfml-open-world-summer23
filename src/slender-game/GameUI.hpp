#pragma once

#include <iostream>

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
    sf::Text statusMeditatingText;

    // Hiding text
    sf::Text statusHidingText;
    sf::Text overHideableText;

    // Health bar var
    sf::RectangleShape healthBarTop;
    sf::RectangleShape healthBarBottom;

    // Sanity bar
    sf::RectangleShape sanityBarTop;
    sf::RectangleShape sanityBarBottom;

    // Meditating, hiding, still, holding breath
    bool isMeditating, isHiding;
    bool overHideable;
    bool renderHideableText;

public:
    void drawOverHideableText(int hideable);
    void drawStatusTexts();
    void drawHealthBar();
    void drawSanityBar();

    sf::Vector2f getSanityBarCurrent();

    void setSanityBar(int sanityChange);
    void setStatusMeditating(bool meditating);
    void setOverHideable(bool over);
    void setStatusHiding(bool hiding);

    GameUI();

    void renderUI(sf::RenderTarget& target);
};