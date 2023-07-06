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
    sf::Text breathBarText;
    sf::Text batteryText;
    sf::Text logText;

    // Status texts
    sf::Text overHideableText;
    sf::Text overItemText;

    sf::Text statusMeditatingText;
    sf::Text statusHidingText;

    sf::Text statusActivityLevelText;

    // BAR VARS
    float barSizeDefaultX, barSizeDefaultY;
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
    bool overItem;
    bool renderHideableText;
    bool renderBreathBar;

    // Log
    bool displayToLog;

public:
    void drawOverHideableText(int hideable);
    void drawOverItemText(std::string itemType);
    void drawHealthBar();
    void drawSanityBar();
    void drawBreathBar();
    void drawStatusTexts();
    void drawBatteryText();
    void drawLogText();

    sf::Vector2f getBarCurrent(std::string bar);

    void setSanityBar(int sanityChange);
    void setStatusMeditating(bool meditating);

    void setOverHideable(bool over);
    void setOverItem(bool over);
    void setStatusHiding(bool hiding);

    void setBreathBar(int breathChange);
    void setDisplayBreathBar(bool display);

    void setStatusActivityLevel(std::string level);

    void setHealthBar(int healthChange);

    void setBattery(std::string battery, sf::Color color);

    void setLogMessage(bool display, std::string message, sf::Color color=sf::Color::White);

    GameUI();

    void renderUI(sf::RenderTarget& target);
};