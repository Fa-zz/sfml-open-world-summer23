#include "Engine.hpp"

// PRIVATE FUNCTIONS, INIT FUNCTIONS
void Engine::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(Data::videoModeWidth,Data::videoModeHeight), "Forest of Clues", sf::Style::Default | sf::Style::Close);
    window->setFramerateLimit(Data::frameRateLimit);
    window->setVerticalSyncEnabled(false);
}

void Engine::initVars() {
    gameAreaSize = sf::Vector2f(Data::gameWorldSizeX, Data::gameWorldSizeY);
    gameAreaBoundsPtr = new sf::FloatRect(sf::Vector2f(0.f,0.f), gameAreaSize);
    playerMoveSpeed = Data::playerMoveSpeedWalk;
    playerNewPosition = sf::Vector2f(0,0);
}

void Engine::initLight() {
    // create a light source
    lightPtr = new candle::RadialLight();
    lightPtr->setRange(Data::lightRange1);
    lightPtr->setFade(false);

    float fogRenderOffset = gameAreaSize.x / 10;
    fogPtr = new candle::LightingArea(candle::LightingArea::FOG, sf::Vector2f(-fogRenderOffset,-fogRenderOffset), sf::Vector2f(gameAreaSize.x+(fogRenderOffset*2), gameAreaSize.y+(fogRenderOffset*2)));
    std::cout << "Fog ptr global bounds: " << fogPtr->getGlobalBounds().height << " " << fogPtr->getGlobalBounds().width << std::endl;
    fogPtr->setAreaColor(sf::Color::Black);
}

void Engine::generatePlayerPosition() {
    float x = gameWorldPtr->randomFloat(0.f, gameAreaSize.x);
    float y = gameWorldPtr->randomFloat(0.f, gameAreaSize.y);
    sf::Vector2f playerCoords = sf::Vector2f(x, y);
    player.setPosition(playerCoords);
    std::cout << "PLAYER COORDS SET AND GENERATED: " << playerCoords.x << " " << playerCoords.y << std::endl;
}

void Engine::initPlayer() {
    player.setRadius(Data::playerRadiusDefault);
    player.setFillColor(CustomColors::skinTone);

    generatePlayerPosition();
    while (playerObjectCollision(player)) {
        generatePlayerPosition();
    }
}

void Engine::initObjects() {
    gameWorldPtr = new World(gameAreaSize, Data::numTrees, Data::numRocks);

    initPlayer();

    UIElem.setSize(sf::Vector2f(300.f,50.f));
}

void Engine::initView() {
    mainView.setSize(1920,1080);
}

// CONSTRUCTOR, DESTRUCTOR
Engine::Engine() {
    initWindow();
    initVars();
    initLight();
    initObjects();
    initView();
}

Engine::~Engine() {
    delete window;
    delete lightPtr;
    delete fogPtr;
    delete gameAreaBoundsPtr;
    delete gameWorldPtr;
}

// RUN, UPDATE, POLL EVENTS FUNCTIONS
void Engine::run() {

    while (window->isOpen()) {
        update();
        render();
    }
}

void Engine::pollEvents() {
    sf::Event e;
    while(window->pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed) {
            std::cout << "WINDOW CLOSED" << std::endl;
            window->close();
        }
        if (e.Event::KeyPressed && e.Event::key.code == sf::Keyboard::Escape) {
            std::cout << "WINDOW CLOSED, ESCAPE" << std::endl;
            window->close();
        }
    }
}

void Engine::playerOutOfBoundsAdjust() {
    std::cout << "ADJUSTING PLAYER POS, EXCEEDING BOUNDS" << std::endl;
    // Adjust player position if it exceeds the game area bounds
    if (playerNewPosition.x < gameAreaBoundsPtr->left)
        playerNewPosition.x = gameAreaBoundsPtr->left;
    else if (playerNewPosition.x > gameAreaBoundsPtr->left + gameAreaBoundsPtr->width)
        playerNewPosition.x = gameAreaBoundsPtr->left + gameAreaBoundsPtr->width;

    if (playerNewPosition.y < gameAreaBoundsPtr->top)
        playerNewPosition.y = gameAreaBoundsPtr->top;
    else if (playerNewPosition.y > gameAreaBoundsPtr->top + gameAreaBoundsPtr->height)
        playerNewPosition.y = gameAreaBoundsPtr->top + gameAreaBoundsPtr->height;
}

bool Engine::playerObjectCollision(sf::CircleShape& playerArg) {
    float GAP_THRESHOLD = 10.f;
    sf::FloatRect playerBounds = playerArg.getGlobalBounds();
    
    for (auto iter = 0; iter < gameWorldPtr->treesVector.size(); ++iter) {
        sf::FloatRect circleBounds = gameWorldPtr->treesVector[iter].getGlobalBounds();
        
        // Calculate the distance between the centers of player and circle
        sf::Vector2f playerCenter = playerArg.getPosition() + sf::Vector2f(playerArg.getRadius(), playerArg.getRadius());
        sf::Vector2f circleCenter = gameWorldPtr->treesVector[iter].getPosition() + sf::Vector2f(gameWorldPtr->treesVector[iter].getRadius(), gameWorldPtr->treesVector[iter].getRadius());
        
        float distance = std::sqrt(std::pow(playerCenter.x - circleCenter.x, 2) + std::pow(playerCenter.y - circleCenter.y, 2));

        // Check for collision only if the player is close enough to the circle
        // Adjust the threshold value according to your requirements
        if (distance <= playerArg.getRadius() + gameWorldPtr->treesVector[iter].getRadius() + GAP_THRESHOLD) {
            if (playerBounds.intersects(circleBounds)) {
                return true;  // Collision detected
            }
        }
    }    

    return false;
}

void Engine::updatePlayer() {
    sf::Vector2f playerBeforePos = player.getPosition();
    // std::cout << "PLAYER POS: " << player.getPosition().x << " " << player.getPosition().y << std::endl;
    playerMovement = sf::Vector2f(0,0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        playerMovement.y -= playerMoveSpeed;
    } 
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        playerMovement.y += playerMoveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        playerMovement.x -= playerMoveSpeed;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        playerMovement.x += playerMoveSpeed;
    }

    std::cout << "PLAYER MOVEMENT: " << playerMovement.x << " " << playerMovement.y << std::endl;

    // Checking if player collides with gameArea or other objects
    playerNewPosition = player.getPosition() + playerMovement;
    sf::CircleShape newPlayer = player;
    newPlayer.setPosition(playerNewPosition);

    if (gameAreaBoundsPtr->contains(playerNewPosition) && !playerObjectCollision(newPlayer)) {
        player.setPosition(playerNewPosition);  // Update the player's position
    } else {
        if (!(gameAreaBoundsPtr->contains(playerNewPosition))) {
            playerOutOfBoundsAdjust();
        }

    }

    // if (gameAreaBoundsPtr->contains(playerNewPosition) && !(playerObjectCollision()))
    //     player.setPosition(playerNewPosition);
    // else {
    //     if (!(gameAreaBoundsPtr->contains(playerNewPosition))) {
    //         playerOutOfBoundsAdjust();
    //     }
    //     if (playerObjectCollision())
    //         playerObjectCollisionAdjust();
    //}

    // Checking collision between objects and player
    std::cout << "Player object collision func: " << playerObjectCollision(newPlayer) << std::endl;
    // if (!playerObjectCollision()) {
    //     player.setPosition(playerNewPosition);  // Update the player's position
    // }
}

void Engine::update() {
    pollEvents();
    updatePlayer();

    // Calculate the midpoint of the circle, then set lightPtr equal to
    circlePosition = player.getPosition();
    float circleRadius = player.getRadius();
    sf::Vector2f playerMidpoint(circlePosition.x + circleRadius, circlePosition.y + circleRadius);

    lightPtr->setPosition(playerMidpoint - sf::Vector2f(3.f,3.f));
}

// RENDER FUNCTIONS
void Engine::renderObjects(sf::RenderTarget& target) {
    gameWorldPtr->render(target);
}

void Engine::render() {
    mainView.setCenter(player.getPosition());
    // Draw

    // Draw light, fog
    fogPtr->clear();
    fogPtr->draw(*lightPtr);
    fogPtr->display();

    window->clear(CustomColors::groundColor);

    window->setView(mainView);

    // Draw objects
    renderObjects(*this->window);

    window->draw(*fogPtr);
    window->draw(player);

    // Draw UI
    window->setView(window->getDefaultView());
    window->draw(UIElem);

    // Finished drawning
    window->display();
}