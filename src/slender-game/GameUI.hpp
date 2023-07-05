#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>

class GameUI {
private:

    // Init font
    void initFont();

    // Font/text var
    sf:: Font font;
    sf::Text healthBarText;
    sf::Text sanityBarText;
    sf::Text statusMeditatingText;


    // Health bar var
    sf::RectangleShape healthBarTop;
    sf::RectangleShape healthBarBottom;

    // Sanity bar
    sf::RectangleShape sanityBarTop;
    sf::RectangleShape sanityBarBottom;

    // Meditating, hiding, still, holding breath
    bool isMeditating;

public:
    void drawHealthBar();
    void drawSanityBar();
    void drawStatusTexts();

    void setSanityBar(int sanityChange);
    void setStatusMeditating(bool meditating);

    GameUI();

    void renderUI(sf::RenderTarget& target);
};