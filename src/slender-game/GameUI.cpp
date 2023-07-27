#include "GameUI.hpp"

void GameUI::initVars() {
    barSizeDefaultX = 300.f;
    barSizeDefaultY = 40.f;
    bool isMeditating = false;
    bool isHiding = false;
    bool overHideable = false;
    bool renderHideableText = false;
    bool renderBreathBar = false;
    bool displayToLog = false;
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
        overItemText.setFont(font);
        logText.setFont(font);
        notesFoundText.setFont(font);
    }
}

void GameUI::drawHealthBar() {
    healthBarTop.setSize(sf::Vector2f(barSizeDefaultX,barSizeDefaultY));
    healthBarTop.setPosition(sf::Vector2f(1550.f,60.f));
    healthBarTop.setFillColor(sf::Color::Green);

    healthBarBottom.setSize(sf::Vector2f(barSizeDefaultX,barSizeDefaultY));
    healthBarBottom.setPosition(sf::Vector2f(1550.f,60.f));
    healthBarBottom.setFillColor(sf::Color::Red);
    healthBarBottom.setOutlineColor(sf::Color::Black);
    healthBarBottom.setOutlineThickness(5.f);

    healthBarText.setString("Health");
    healthBarText.setCharacterSize(40);
    healthBarText.setPosition(1600.f,20.f);
}

void GameUI::drawSanityBar() {
    sanityBarTop.setSize(sf::Vector2f(barSizeDefaultX,barSizeDefaultY));
    sanityBarTop.setPosition(sf::Vector2f(1550.f,220.f));
    sanityBarTop.setFillColor(sf::Color::Cyan);

    sanityBarBottom.setSize(sf::Vector2f(barSizeDefaultX,barSizeDefaultY));
    sanityBarBottom.setPosition(sf::Vector2f(1550.f,220.f));  // 50.f,60.f
    sanityBarBottom.setFillColor(sf::Color::Red);
    sanityBarBottom.setOutlineColor(sf::Color::Black);
    sanityBarBottom.setOutlineThickness(5.f);

    sanityBarText.setString("Sanity");
    sanityBarText.setCharacterSize(40);
    sanityBarText.setPosition(1600.f,180.f); // 100.f,20.f
}

void GameUI::drawBreathBar() {
    breathBarTop.setSize(sf::Vector2f(barSizeDefaultX,barSizeDefaultY));
    breathBarTop.setPosition(sf::Vector2f(50.f,150.f));  // 1550.f,220.f
    breathBarTop.setFillColor(CustomColors::breathBarColor);

    breathBarBottom.setSize(sf::Vector2f(barSizeDefaultX,barSizeDefaultY));
    breathBarBottom.setPosition(sf::Vector2f(50.f,150.f));
    breathBarBottom.setFillColor(sf::Color::Red);
    breathBarBottom.setOutlineColor(sf::Color::Black);
    breathBarBottom.setOutlineThickness(5.f);

    breathBarText.setString("Breath");
    breathBarText.setCharacterSize(30);
    breathBarText.setPosition(100.f,110.f);  // 1600.f,180.f
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

void GameUI::drawOverItemText(std::string itemType) {
    overItemText.setString("There is a " + itemType + " here.\n Press E to use.");

    overItemText.setCharacterSize(25);
    overItemText.setPosition(1500,400);
}

void GameUI::drawStatusTexts() {
    statusMeditatingText.setString("Meditating");
    statusMeditatingText.setCharacterSize(40);
    statusMeditatingText.setPosition(100.f,350.f);

    statusHidingText.setString("Hiding");
    statusHidingText.setCharacterSize(40);
    statusHidingText.setPosition(100.f,450.f);

    statusActivityLevelText.setCharacterSize(40);
    statusActivityLevelText.setPosition(100.f, 550.f);
}

// 120, 140 to draw tools

void GameUI::drawBatteryText() {
    batteryText.setCharacterSize(50);
    batteryText.setPosition(1525.f,1020.f);
}

void GameUI::drawLogText() {
    logText.setCharacterSize(30);
    logText.setPosition(0.f,30.f);
}

void GameUI::drawNotesFoundText() {
    notesFoundText.setCharacterSize(50);
    notesFoundText.setPosition(0.f,1020.f);
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

    if (sanityBarTop.getSize().x + sanityChange > sanityBarBottom.getSize().x)
        sanityBarTop.setSize(sf::Vector2f(barSizeDefaultX, barSizeDefaultY));
    if (sanityBarTop.getSize().x + sanityChange < 0)
        sanityBarTop.setSize(sf::Vector2f(0, barSizeDefaultY));
}

void GameUI::setBreathBar(int breathChange) {
    if (!(breathBarTop.getSize().x + breathChange < 0) && !(breathBarTop.getSize().x + breathChange > breathBarBottom.getSize().x))
        breathBarTop.setSize(sf::Vector2f(breathBarTop.getSize().x + breathChange, breathBarTop.getSize().y));
    
    if (breathBarTop.getSize().x + breathChange > breathBarBottom.getSize().x)
        breathBarTop.setSize(sf::Vector2f(barSizeDefaultX, barSizeDefaultY));
    if (breathBarTop.getSize().x + breathChange < 0)
        breathBarTop.setSize(sf::Vector2f(0, barSizeDefaultY));
}

void GameUI::setHealthBar(int healthChange) {
    if (!(healthBarTop.getSize().x + healthChange < 0) && !(healthBarTop.getSize().x + healthChange > healthBarBottom.getSize().x))
        healthBarTop.setSize(sf::Vector2f(healthBarTop.getSize().x + healthChange, healthBarTop.getSize().y)); 

    if (healthBarTop.getSize().x + healthChange > healthBarBottom.getSize().x)
        healthBarTop.setSize(sf::Vector2f(barSizeDefaultX, barSizeDefaultY));
    if (healthBarTop.getSize().x + healthChange < 0)
        healthBarTop.setSize(sf::Vector2f(0, barSizeDefaultY));

}

void GameUI::setOverHideable(bool over) {
    renderHideableText = over;
}

void GameUI::setOverItem(bool over) {
    overItem = over;
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

void GameUI::setBattery(std::string battery, sf::Color color) {
    batteryText.setString("Battery: " + battery + "%");
    batteryText.setColor(color);
}

void GameUI::setLogMessage(bool display, std::string message, sf::Color color){
    displayToLog = display;
    logText.setString(message);
    logText.setColor(color);
}

void GameUI::setNotesFound(int numNotesFound) {
    notesFoundText.setString("Notes found: " +  std::to_string(numNotesFound) + "/5");
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
    drawLogText();
    drawNotesFoundText();
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
    if (overItem)
        target.draw(overItemText);
    if (renderBreathBar) {
        target.draw(breathBarBottom);
        target.draw(breathBarTop);
        target.draw(breathBarText);
    }
    target.draw(batteryText);
    if (displayToLog)
        target.draw(logText);
    target.draw(notesFoundText);
}