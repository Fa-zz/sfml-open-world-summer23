#include "GameUI.hpp"

void GameUI::initFont() {
    if (!font.loadFromFile("./subway-ticker.regular.ttf")) {
        std::cout << "Did Not Load Font" << std::endl;
    } else {
        healthBarText.setFont(font);
        sanityBarText.setFont(font);
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

void GameUI::setSanityBar(int sanityChange) {
    if (!(sanityBarTop.getSize().x + sanityChange < 0))
        sanityBarTop.setSize(sf::Vector2f(sanityBarTop.getSize().x + sanityChange, sanityBarTop.getSize().y));
}

GameUI::GameUI() {
    initFont();
    drawHealthBar();
    drawSanityBar();
}

void GameUI::renderUI(sf::RenderTarget& target) {
    target.draw(healthBarBottom);
    target.draw(healthBarTop);

    target.draw(sanityBarBottom);
    target.draw(sanityBarTop);

    target.draw(healthBarText);
    target.draw(sanityBarText);
}