#include "GameUI.hpp"

void GameUI::initVars() {
    bool isMeditating = false;
    bool isHiding = false;
    bool overHideable = false;
    bool renderHideableText = false;
    bool renderBreathBar = false;
}

void GameUI::initFont() {
    if (!font.loadFromFile("./subway-ticker.regular.ttf")) {
        std::cout << "Did Not Load Font" << std::endl;
    } else {
        healthBarText.setFont(font);
        sanityBarText.setFont(font);
        breathBarText.setFont(font);
        statusMeditatingText.setFont(font);
        statusHidingText.setFont(font);
        overHideableText.setFont(font);
        statusActivityLevelText.setFont(font);
        batteryText.setFont(font);
    }
}

void GameUI::drawHealthBar() {
    // Player hitpoints = 100. So 1 hp damage = 3 px removed from health bar
    // If I have 100 health, I should have a 300px bar as 100*3=300
    // Similarly if I have 56 health, I should have 56*3 px bar
    // Top bar's size will be modified
    healthBarTop.setSize(sf::Vector2f(300.f,40.f));
    healthBarTop.setPosition(sf::Vector2f(1550.f,60.f));
    healthBarTop.setFillColor(sf::Color::Green);
    // healthBarTop.setOutlineColor(sf::Color::Black);
    // healthBarTop.setOutlineThickness(5.f);

    healthBarBottom.setSize(sf::Vector2f(300.f,40.f));
    healthBarBottom.setPosition(sf::Vector2f(1550.f,60.f));
    healthBarBottom.setFillColor(sf::Color::Red);
    healthBarBottom.setOutlineColor(sf::Color::Black);
    healthBarBottom.setOutlineThickness(5.f);

    healthBarText.setString("Health");
    healthBarText.setCharacterSize(40);
    healthBarText.setPosition(1600.f,20.f);
}

void GameUI::drawSanityBar() {
    sanityBarTop.setSize(sf::Vector2f(300.f,40.f));
    sanityBarTop.setPosition(sf::Vector2f(50.f,60.f));
    sanityBarTop.setFillColor(sf::Color::Cyan);
    // sanityBarTop.setOutlineColor(sf::Color::Black);
    // sanityBarTop.setOutlineThickness(5.f);

    sanityBarBottom.setSize(sf::Vector2f(300.f,40.f));
    sanityBarBottom.setPosition(sf::Vector2f(50.f,60.f));
    sanityBarBottom.setFillColor(sf::Color::Red);
    sanityBarBottom.setOutlineColor(sf::Color::Black);
    sanityBarBottom.setOutlineThickness(5.f);

    sanityBarText.setString("Sanity");
    sanityBarText.setCharacterSize(40);
    sanityBarText.setPosition(100.f,20.f);
}

void GameUI::drawBreathBar() {
    breathBarTop.setSize(sf::Vector2f(300.f,40.f));
    breathBarTop.setPosition(sf::Vector2f(1550.f,220.f));
    breathBarTop.setFillColor(CustomColors::breathBarColor);

    breathBarBottom.setSize(sf::Vector2f(300.f,40.f));
    breathBarBottom.setPosition(sf::Vector2f(1550.f,220.f));
    breathBarBottom.setFillColor(sf::Color::Red);
    breathBarBottom.setOutlineColor(sf::Color::Black);
    breathBarBottom.setOutlineThickness(5.f);

    breathBarText.setString("Breath");
    breathBarText.setCharacterSize(30);
    breathBarText.setPosition(1600.f,180.f);
}

void GameUI::drawOverHideableText(int hideable) {
    if (hideable == 1) {
        overHideableText.setString("You can hide in this bush.\nPress Q to hide.");
    } else if (hideable == 2) {
        overHideableText.setString("You can hide in this mud.\nPress Q to hide.");
    }

    overHideableText.setCharacterSize(25);
    overHideableText.setPosition(1550,310);
}

void GameUI::drawStatusTexts() {
    statusMeditatingText.setString("Meditating");
    statusMeditatingText.setCharacterSize(40);
    statusMeditatingText.setPosition(100.f,750.f);

    statusHidingText.setString("Hiding");
    statusHidingText.setCharacterSize(40);
    statusHidingText.setPosition(100.f,600.f);

    statusActivityLevelText.setCharacterSize(40);
    statusActivityLevelText.setPosition(100.f, 450.f);
}

void GameUI::drawBatteryText() {
    batteryText.setCharacterSize(50);
    batteryText.setPosition(1525.f,1020.f);
}

//TODO: Change to general bar x and y
sf::Vector2f GameUI::getBarCurrent(std::string bar) {
    float current;
    float max;
    if (bar == "sanity") {
        current = sanityBarTop.getSize().x;
        max = sanityBarBottom.getSize().x;
    } else if (bar == "health") {
        current = healthBarTop.getSize().x;
        max = healthBarBottom.getSize().x;
    } else if (bar == "breath") {
        current = breathBarTop.getSize().x;
        max = breathBarBottom.getSize().x;
    }
    return sf::Vector2f(current, max);
}

void GameUI::setSanityBar(int sanityChange) {
    if (!(sanityBarTop.getSize().x + sanityChange < 0) && !(sanityBarTop.getSize().x + sanityChange > sanityBarBottom.getSize().x))
        sanityBarTop.setSize(sf::Vector2f(sanityBarTop.getSize().x + sanityChange, sanityBarTop.getSize().y));
}

void GameUI::setBreathBar(int breathChange) {
    if (!(breathBarTop.getSize().x + breathChange < 0) && !(breathBarTop.getSize().x + breathChange > breathBarBottom.getSize().x))
        breathBarTop.setSize(sf::Vector2f(breathBarTop.getSize().x + breathChange, breathBarTop.getSize().y));
}

void GameUI::setHealthBar(int healthChange) {
    if (!(healthBarTop.getSize().x + healthChange < 0) && !(healthBarTop.getSize().x + healthChange > healthBarBottom.getSize().x))
        healthBarTop.setSize(sf::Vector2f(healthBarTop.getSize().x + healthChange, healthBarTop.getSize().y)); 
}

void GameUI::setOverHideable(bool over) {
    renderHideableText = over;
}

void GameUI::setStatusMeditating(bool meditating) {
    isMeditating = meditating;
}

void GameUI::setStatusHiding(bool hiding) {
    isHiding = hiding;
}

void GameUI::setDisplayBreathBar(bool display) {
    renderBreathBar = display;
}

void GameUI::setStatusActivityLevel(std::string level) {
    statusActivityLevelText.setString(level);
}

void GameUI::setBattery(std::string battery) {
    batteryText.setString("Battery: " + battery + "%");
}

// constructor
GameUI::GameUI() {
    initVars();
    initFont();
    drawHealthBar();
    drawSanityBar();
    drawBreathBar();
    drawStatusTexts();
    drawBatteryText();
}

void GameUI::renderUI(sf::RenderTarget& target) {
    target.draw(healthBarBottom);
    target.draw(healthBarTop);
    target.draw(healthBarText);

    target.draw(sanityBarBottom);
    target.draw(sanityBarTop);
    target.draw(sanityBarText);

    if (isMeditating)
        target.draw(statusMeditatingText);
    if (isHiding)
        target.draw(statusHidingText);
    target.draw(statusActivityLevelText);
    if (renderHideableText)
        target.draw(overHideableText);
    if (renderBreathBar) {
        target.draw(breathBarBottom);
        target.draw(breathBarTop);
        target.draw(breathBarText);
    }
    target.draw(batteryText);
}