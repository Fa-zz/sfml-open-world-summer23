#include "GameUI.hpp"

void GameUI::initVars() {
    bool isMeditating = false;
    bool isHiding = false;
    bool overHideable = false;
    bool renderHideableText = false;
}

void GameUI::initFont() {
    if (!font.loadFromFile("./subway-ticker.regular.ttf")) {
        std::cout << "Did Not Load Font" << std::endl;
    } else {
        healthBarText.setFont(font);
        sanityBarText.setFont(font);
        statusMeditatingText.setFont(font);
        statusHidingText.setFont(font);
        overHideableText.setFont(font);
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

void GameUI::drawOverHideableText(int hideable) {
    if (hideable == 1) {
        overHideableText.setString("You can hide in this bush.\nPress Q to hide.");
    } else if (hideable == 2) {
        overHideableText.setString("You can hide in this mud.\nPress Q to hide.");
    }

    overHideableText.setCharacterSize(25);
    overHideableText.setPosition(1570,310);
}

void GameUI::drawStatusTexts() {
    statusMeditatingText.setString("Meditating");
    statusMeditatingText.setCharacterSize(40);
    statusMeditatingText.setPosition(100.f,650.f);

    statusHidingText.setString("Hiding");
    statusHidingText.setCharacterSize(40);
    statusHidingText.setPosition(100.f,600.f);
}

sf::Vector2f GameUI::getSanityBarCurrent() {
    float maxSanity = sanityBarBottom.getSize().x;
    float currentSanity = sanityBarTop.getSize().x;
    return sf::Vector2f(currentSanity, maxSanity);
}

void GameUI::setSanityBar(int sanityChange) {
    if (!(sanityBarTop.getSize().x + sanityChange < 0) && !(sanityBarTop.getSize().x + sanityChange > sanityBarBottom.getSize().x))
        sanityBarTop.setSize(sf::Vector2f(sanityBarTop.getSize().x + sanityChange, sanityBarTop.getSize().y));
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

// constructor
GameUI::GameUI() {
    initVars();
    initFont();
    drawHealthBar();
    drawSanityBar();
    drawStatusTexts();
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
    if (renderHideableText)
        target.draw(overHideableText);
}