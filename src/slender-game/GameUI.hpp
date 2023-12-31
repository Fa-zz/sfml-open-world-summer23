#pragma once

#include <iostream>
#include <string>

#include "Data.hpp"
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
    sf::Text notesFoundText;
    sf::Text monsterText;

    // Status texts
    sf::Text overHideableText;
    sf::Text overItemText;

    sf::Text meditatingText;
    sf::Text hidingText;

    sf::Text activityText;

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
    void drawNotesFoundText();
    void drawMonsterText();

    sf::Vector2f getBarCurrent(std::string bar);

    void setSanityBar(int sanity);
    void setStatusMeditating(bool meditating);

    void setOverHideableText(bool over);
    void setOverItem(bool over);
    void setStatusHiding(bool hiding);

    void setBreathBar(int breathChange);
    void setDisplayBreathBar(bool display);

    void setActivity(std::string activity);

    void setHealthBar(int healthChange);

    void setBattery(std::string battery, sf::Color color);

    void setLogMessage(bool display, std::string message, sf::Color color=sf::Color::White);

    void setNotesFound(int numNotesFound);

    void setMonsterText(bool appearance, bool found);

    GameUI();

    void renderUI(sf::RenderTarget& target);
};