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

    // Health bar var
    sf::RectangleShape healthBarTop;
    sf::RectangleShape healthBarBottom;

    // Sanity bar
    sf::RectangleShape sanityBarTop;
    sf::RectangleShape sanityBarBottom;

public:
    void drawHealthBar();
    void drawSanityBar();
    void setSanityBar(int sanityChange);

    GameUI();

    void renderUI(sf::RenderTarget& target);
};