#include "Player.hpp"

// HELPER FUNCS
bool Player::playerObjectCollision(sf::CircleShape playerArg) {
    sf::FloatRect playerBounds = playerArg.getGlobalBounds();

    float GAP_THRESHOLD = 10.f;
    for (auto iter = 0; iter < m_gameWorldPtr->fallenTreesVector.size(); ++iter) {
        if (playerBounds.intersects(m_gameWorldPtr->fallenTreesVector[iter].getGlobalBounds()))
            return true;
    }
    for (auto iter = 0; iter < m_gameWorldPtr->treesVector.size(); ++iter) {
        sf::FloatRect circleBounds = m_gameWorldPtr->treesVector[iter].getGlobalBounds();
        
        // Calculate the distance between the centers of player and circle
        sf::Vector2f playerCenter = playerArg.getPosition() + sf::Vector2f(playerArg.getRadius(), playerArg.getRadius());
        sf::Vector2f circleCenter = m_gameWorldPtr->treesVector[iter].getPosition() + sf::Vector2f(m_gameWorldPtr->treesVector[iter].getRadius(), m_gameWorldPtr->treesVector[iter].getRadius());
        
        float distance = std::sqrt(std::pow(playerCenter.x - circleCenter.x, 2) + std::pow(playerCenter.y - circleCenter.y, 2));

        // Check for collision only if the player is close enough to the circle
        // Adjust the threshold value according to your requirements
        if (distance <= playerArg.getRadius() + m_gameWorldPtr->treesVector[iter].getRadius() + GAP_THRESHOLD) {
            if (playerBounds.intersects(circleBounds)) {
                return true;  // Collision detected
            }
        }
    }    

    return false;
}

void Player::generatePlayerPosition() {
    float x = m_gameWorldPtr->randomFloat(0.f, DataSettings::gameWorldSizeX);
    float y = m_gameWorldPtr->randomFloat(0.f, DataSettings::gameWorldSizeY);
    sf::Vector2f playerCoords = sf::Vector2f(x, y);
    player.setPosition(playerCoords);
    std::cout << "PLAYER COORDS SET AND GENERATED: " << playerCoords.x << " " << playerCoords.y << std::endl;
}

void Player::modifySpeedIfObstacles() {
    overHideable = false;
    hideable = 0;
    for (auto iter = 0; iter < m_gameWorldPtr->shrubsVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(m_gameWorldPtr->shrubsVector[iter].getGlobalBounds())) {
            playerSpeedModifier -= 0.5;
            return;
        }
    }
    for (auto iter = 0; iter < m_gameWorldPtr->bushesVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(m_gameWorldPtr->bushesVector[iter].getGlobalBounds())) {
            playerSpeedModifier -= 0.5;
            overHideable = true;
            hideable = 1;
            return;
        }
    }
    for (auto iter = 0; iter < m_gameWorldPtr->mudPatchesVector.size(); ++iter) {
        if (m_gameWorldPtr->mudPatchesVector[iter].getGlobalBounds().contains(player.getPosition())) {                
            playerSpeedModifier -= 0.5;
            overHideable = true;
            hideable = 2;
            return;
        }        
    }
    return;
}

void Player::updatePlayerMovement(float modifier) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        playerMovement.y -= playerMoveSpeed*modifier;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        playerMovement.y += playerMoveSpeed*modifier;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        playerMovement.x -= playerMoveSpeed*modifier;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        playerMovement.x += playerMoveSpeed*modifier;
}

void Player::playerOutOfBoundsAdjust() {
    outOfBounds = true;
    // Adjust player position if it exceeds the game area bounds
    if (playerNewPosition.x < m_gameAreaBoundsPtr->left)
        playerNewPosition.x = m_gameAreaBoundsPtr->left;
    else if (playerNewPosition.x > m_gameAreaBoundsPtr->left + m_gameAreaBoundsPtr->width)
        playerNewPosition.x = m_gameAreaBoundsPtr->left + m_gameAreaBoundsPtr->width;

    if (playerNewPosition.y < m_gameAreaBoundsPtr->top)
        playerNewPosition.y = m_gameAreaBoundsPtr->top;
    else if (playerNewPosition.y > m_gameAreaBoundsPtr->top + m_gameAreaBoundsPtr->height)
        playerNewPosition.y = m_gameAreaBoundsPtr->top + m_gameAreaBoundsPtr->height;
}

// INIT FUNCS
void Player::initPlayer() {
    playerSkinTone = CustomColors::skinTone;
    player.setRadius(DataSettings::playerRadiusDefault);
    player.setFillColor(playerSkinTone);

    generatePlayerPosition();
    while (playerObjectCollision(player)) {
        generatePlayerPosition();
    }
}

void Player::initVars() {
    statusStill = statusWalking = statusRunning = false;
    overHideable = false;
    playerSpeedModifier = 0; 
    playerMoveSpeed = DataSettings::playerMoveSpeedWalk;
    playerMovement = playerNewPosition = sf::Vector2f(0.f,0.f);
    outOfBounds = false;
    sanity = health = breath = DataSettings::barSizeDefaultX;
    maxBar = DataSettings::barSizeDefaultX;
    sanityTimer = breathTimer = 0;
    flashlightOn = false;
    leftHiding = false;
    displayBreath = false;
}

// CONSTRUCTOR
Player::Player(World* gameWorldPtr, sf::FloatRect* gameAreaBoundsPtr):m_gameWorldPtr(gameWorldPtr), m_gameAreaBoundsPtr(gameAreaBoundsPtr) {
    initPlayer();
    initVars();
}

// UPDATE FUNCS
void Player::updateBreathTimer(float currentTime) {
    breathTimer += currentTime;
}

void Player::updateSanityTimer(float currentTime) {
    sanityTimer += currentTime;
}

void Player::updateBreath() {
    if (breath < 0) {
        breath = 0;
    } else if (breath > 300) {
        breath = 300;
    }

    if (statusRunning || (hidingActivated && hideable == 2) || breath < maxBar) {
        // UIPtr->setDisplayBreathBar(true);
        displayBreath = true;
        isBreathing = true;
        if (((hidingActivated && hideable == 2) || statusRunning) && breath) {
            if (breathTimer > 1) {
                // UIPtr->setBreathBar(-30);
                breath -= 30;
                breathTimer = 0;
            }
        } else if (((hidingActivated && hideable == 2) || statusRunning) && (!breath)) {
            if (breathTimer > 3) {
                // UIPtr->setHealthBar(-12);
                health -= 12;
                breathTimer = 0;
            }
        } else if ( (!hidingActivated || (hidingActivated && hideable == 1) ) && statusWalking && breath < maxBar) {
            if (breathTimer > 4) {
                // UIPtr->setBreathBar(12);
                breath += 12;
                breathTimer = 0;
            }
        } else if ( (!hidingActivated || (hidingActivated && hideable == 1) ) && statusStill && breath < maxBar) {
            if (breathTimer > 2) {
                // UIPtr->setBreathBar(30);
                breath += 30;
                breathTimer = 0;
            }
        }
    } else if (breath == maxBar) {
        // isBreathing = false;
        // UIPtr->setDisplayBreathBar(false);
        displayBreath = false;
    }
}

void Player::updateHiding() {
    if (!hidingActivated) {
        player.setFillColor(playerSkinTone);
        if (leftHiding) {
            flashlightOn = true;
            leftHiding = false;
        }
    }
    
    if (hidingActivated) {
        // UIPtr->setOverHideable(false);
        // UIPtr->setStatusHiding(true);
        player.setFillColor(CustomColors::invisible);
        flashlightOn = false;
        leftHiding = true;
    }

    if (hidingActivated) {
        player.setFillColor(CustomColors::invisible);
        flashlightOn = false;
        leftHiding = true;
    }
}

void Player::updateSanity(bool isMeditating) {
    // std::cout << "Curr sanity: " << UIPtr->getBarCurrent("sanity").x << std::endl;
    if (sanity < 0) {
        sanity = 0;
    } else if (sanity > 300) {
        sanity = 300;
    }

    difference = 0;
    if (!isMeditating) {
        if (sanityTimer > 3) {
            difference = -6;
            sanityTimer = 0;
        }
    } else if (isMeditating) {
        if (sanityTimer > 4) {
            difference = 30;
            sanityTimer = 0;
        }
    }
    sanity += difference;
}

void Player::updateItem() {
    // overItem = false;
    // for (auto iter = 0; iter < gameWorldPtr->itemsVector.size(); ++iter) {
    //     if (playerPtr->getPlayerGlobalBounds().intersects(gameWorldPtr->itemsVector[iter].getGlobalBounds())) {
    //         gameWorldPtr->itemsVector[iter].setOutlineColor(sf::Color::Yellow);
    //         gameWorldPtr->itemsVector[iter].setOutlineThickness(5.f);
    //         highlightedIter = iter;
    //         overItem = true;
    //         break;
    //     } 
    // }

    // if (highlightedIter != -1) {
    //     if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == sf::Color::Black)
    //         itemType = "battery";
    //     if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == CustomColors::holySymbolColor)
    //         itemType = "holy symbol";
    //     if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == CustomColors::mushroomColor)
    //         itemType = "mushroom";
    //     if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == CustomColors::noteColor)
    //         itemType = "note";
    // }

    // if (overItem && (!useItem)) {
    //     UIPtr->setOverItem(true);
    //     UIPtr->drawOverItemText(itemType);
    // } else if (overItem && useItem) {
    //     if (itemType == "battery") {
    //         if ((flashlightBattery + 10) > 100 ) {
    //             flashlightBattery = 100;
    //         } else {
    //             flashlightBattery += 10;
    //         }
    //         currentLightRange += 40;
    //         flashlightBatteryTimer = 0.f;

    //         logMessages.push_back(DataSettings::useBatteryString);
    //         // gameWorldPtr->itemsVector.erase(gameWorldPtr->itemsVector.begin() + highlightedIter);
    //         // useItem = false;

    //     } else if (itemType == "holy symbol") {
    //         UIPtr->setSanityBar(100.f);
    //         int randChanceToHeal = gameWorldPtr->randomInt(1, 10);
    //         if (randChanceToHeal > 3) {
    //             UIPtr->setHealthBar(60.f);
    //             logMessages.push_back(DataSettings::useHolySymbolString2);
    //         } else {
    //             logMessages.push_back(DataSettings::useHolySymbolString1);
    //         }

    //     } else if (itemType == "note") {
    //         // Check if this was the first note found
    //         notesFound += 1;
    //         if (notesFound == 1)
    //             firstNoteFound = true;
    //     }

    //     gameWorldPtr->itemsVector.erase(gameWorldPtr->itemsVector.begin() + highlightedIter);
    //     useItem = false;

    // }

    // if (!(overItem)) {
    //     UIPtr->setOverItem(false);
    //     if (highlightedIter != -1) {
    //         gameWorldPtr->itemsVector[highlightedIter].setOutlineThickness(0.f);
    //         highlightedIter = -1;
    //     }
    // }
}

void Player::updatePlayer() {
    std::cout << "Curr sanity (player): " << sanity << std::endl;
    std::cout << "Curr breath (player): " << breath << std::endl;

    // std::cout << "Player speed modifier: " << playerSpeedModifier << " Player move speed: " << playerMoveSpeed << " Player movement x: " << playerMovement.x << " Player movement y: " << playerMovement.y << std::endl;
    statusStill = statusWalking = statusRunning = false;
    outOfBounds = false;
    playerMovement = sf::Vector2f(0,0);

    updateSanity(meditateActivated);
    updateHiding();

    playerSpeedModifier = 1;
    if (meditateActivated || hidingActivated) {
        playerSpeedModifier = 0;
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) {
        playerSpeedModifier = 2;
        statusRunning = true;
    }

    // Adjust speed given obstacles
    if (playerSpeedModifier) {
        modifySpeedIfObstacles();
    }

    updatePlayerMovement(playerSpeedModifier);

    // If player does not move, player is still
    if (playerMovement.x == 0 && playerMovement.y == 0) {
        playerSpeedModifier = 0;
    } else if (playerSpeedModifier >= 0.5 && playerSpeedModifier <= 1) {
        statusStill = false;
        statusWalking = true;
        statusRunning = false;
    } else {
        statusStill = false;
        statusWalking = false;
        statusRunning = true;
    }
    if (playerSpeedModifier == 0) {
        statusStill = true;
        statusWalking = false;
        statusRunning = false;
    }

    updateBreath();

    // Checking if player collides with gameArea or other objects
    playerNewPosition = player.getPosition() + playerMovement;
    sf::CircleShape newPlayer = player;
    newPlayer.setPosition(playerNewPosition);

    // Checking collision between objects and player
    if (m_gameAreaBoundsPtr->contains(playerNewPosition) && !playerObjectCollision(newPlayer)) {
        player.setPosition(playerNewPosition);  // Update the player's position
    } else {
        if (!(m_gameAreaBoundsPtr->contains(playerNewPosition))) {
            playerOutOfBoundsAdjust();
        }
    }
    
    // std::cout << "Statusstill: " << statusStill << " Statuswalking: " << statusWalking << " Statusrunning: " << statusRunning << std::endl; 
}

// GETTERS
sf::FloatRect Player::getPlayerGlobalBounds() { return player.getGlobalBounds(); }
bool Player::getPlayerOutOfBounds() { return outOfBounds; }
bool Player::getMeditateActivated() { return meditateActivated; }
std::array<bool, 2> Player::getHiding() { return {hidingActivated, overHideable}; }
int Player::getHideable() { return hideable; }
std::array<bool, 3> Player::getStatus() { return {statusStill, statusWalking, statusRunning}; }
int Player::getSanity() { return sanity; } 
sf::CircleShape Player::getPlayer() { return player; }
bool Player::getFlashlightOn() { return flashlightOn; }
int Player::getBreath() { return breath; }
bool Player::getDisplayBreath() { return displayBreath; }
int Player::getHealth() { return health; }

float Player::getSanityTimer() { return sanityTimer; }
float Player::getBreathTimer() { return breathTimer; }

// SETTERS
void Player::setMeditateActivated(bool meditating) {
    meditateActivated = meditating;
}
void Player::setHidingActivated(bool hiding) {
    hidingActivated = hiding;
}
void Player::setFlashlightOn(bool newFlashlight) {
    flashlightOn = newFlashlight;
}