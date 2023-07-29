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
    sanity = health = 300;
    sanityTimer = 0;

}

// CONSTRUCTOR
Player::Player(World* gameWorldPtr, sf::FloatRect* gameAreaBoundsPtr):m_gameWorldPtr(gameWorldPtr), m_gameAreaBoundsPtr(gameAreaBoundsPtr) {
    initPlayer();
    initVars();
}

// UPDATE FUNCS
void Player::updateSanityTimer(float currentTime) {
    sanityTimer += currentTime;
}

void Player::updateSanity(bool isMeditating) {
    // std::cout << "Curr sanity: " << UIPtr->getBarCurrent("sanity").x << std::endl;
    if (sanity < 0) {
        sanity = 0;
    } else if (sanity > 300) {
        sanity = 300;
    }

    difference = 0;
    std::cout << "Curr sanity (player): " << sanity << std::endl;
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

void Player::updatePlayer() {
    // std::cout << "Player speed modifier: " << playerSpeedModifier << " Player move speed: " << playerMoveSpeed << " Player movement x: " << playerMovement.x << " Player movement y: " << playerMovement.y << std::endl;
    statusStill = statusWalking = statusRunning = false;
    outOfBounds = false;
    playerMovement = sf::Vector2f(0,0);

    updateSanity(meditateActivated);

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

float Player::getSanityTimer() { return sanityTimer; }

// SETTERS
void Player::setMeditateActivated(bool meditating) {
    meditateActivated = meditating;
}