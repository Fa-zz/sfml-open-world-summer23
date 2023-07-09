#include "Engine.hpp"

// PRIVATE FUNCTIONS, INIT FUNCTIONS
void Engine::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(DataSettings::videoModeWidth,DataSettings::videoModeHeight), "Forest of Shapes", sf::Style::Default | sf::Style::Close);
    window->setFramerateLimit(DataSettings::frameRateLimit);
    window->setVerticalSyncEnabled(false);
    window->setFramerateLimit(100);
}

void Engine::initVars() {
    gameAreaSize = sf::Vector2f(DataSettings::gameWorldSizeX, DataSettings::gameWorldSizeY);
    gameAreaBoundsPtr = new sf::FloatRect(sf::Vector2f(0.f,0.f), gameAreaSize);
    playerMoveSpeed = DataSettings::playerMoveSpeedWalk;
    playerSkinTone = CustomColors::skinTone;
    playerNewPosition = sf::Vector2f(0,0);
    meditateActivated = 0;
    hidingActivated = false;
    leftHiding = false;
    flashlightOn = false;
    clickedFlashlight = flashlightOn;
    overHideable = false;
    statusStill = false; 
    statusWalking = false;
    statusRunning = false;
    breathTimer = 0;
    overRock = false;
    overItem = false;
    useItem = false;
    highlightedIter = -1;
    itemType = "";
    logTimer = 0;
    totalTime = 0;
}

void Engine::initLight() {
    // create a light source
    lightPtr = new candle::RadialLight();
    currentLightRange = DataSettings::lightRangeFull;
    lightPtr->setRange(currentLightRange);
    lightPtr->setFade(false);
    lightPtr->setIntensity(0.5);


    float fogRenderOffset = gameAreaSize.x / 10;
    fogPtr = new candle::LightingArea(candle::LightingArea::FOG, sf::Vector2f(-fogRenderOffset,-fogRenderOffset), sf::Vector2f(gameAreaSize.x+(fogRenderOffset*2), gameAreaSize.y+(fogRenderOffset*2)));
    std::cout << "Fog ptr global bounds: " << fogPtr->getGlobalBounds().height << " " << fogPtr->getGlobalBounds().width << std::endl;
    fogPtr->setAreaColor(sf::Color::Black);

    flashlightBattery = 100;
    flashlightBatteryTimer = 0;
}

void Engine::generatePlayerPosition() {
    float x = gameWorldPtr->randomFloat(0.f, gameAreaSize.x);
    float y = gameWorldPtr->randomFloat(0.f, gameAreaSize.y);
    sf::Vector2f playerCoords = sf::Vector2f(x, y);
    player.setPosition(playerCoords);
    std::cout << "PLAYER COORDS SET AND GENERATED: " << playerCoords.x << " " << playerCoords.y << std::endl;
}

void Engine::initPlayer() {
    player.setRadius(DataSettings::playerRadiusDefault);
    player.setFillColor(playerSkinTone);

    generatePlayerPosition();
    while (playerObjectCollision(player)) {
        generatePlayerPosition();
    }
}

void Engine::initObjects() {
    gameWorldPtr = new World();

    initPlayer();
}

void Engine::initUI() {
    UIPtr = new GameUI();
}

void Engine::initView() {
    mainView.setSize(1920,1080);
}

void Engine::initAudio() {
    audioPtr = new GameAudio();
    audioPtr->playLoopingAmbience();
}

// CONSTRUCTOR, DESTRUCTOR
Engine::Engine() {
    initWindow();
    initVars();
    initLight();
    initObjects();
    initUI();
    initView();
    initAudio();
}

Engine::~Engine() {
    delete window;
    delete lightPtr;
    delete fogPtr;
    delete gameAreaBoundsPtr;
    delete gameWorldPtr;
    delete UIPtr;
    delete audioPtr;
}

// RUN, UPDATE, POLL EVENTS FUNCTIONS
void Engine::run() {

    while (window->isOpen()) {
        update();
        render();
    }
}

void Engine::pollEvents() {
    window->setKeyRepeatEnabled(false);
    sf::Event e;
    while(window->pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            std::cout << "WINDOW CLOSED" << std::endl;
            window->close();
        }
        if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) {
            std::cout << "WINDOW CLOSED, ESCAPE" << std::endl;
            window->close();
        }
        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Num1) {
            flashlightOn = (!flashlightOn);
        }
        if (e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::M) {
            meditateActivated = (!meditateActivated);
        }
        if ((overHideable) && e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::Q) {
            hidingActivated = (!hidingActivated);
        }
        if ((overItem) && e.type == sf::Event::KeyReleased && e.key.code == sf::Keyboard::E) {
            useItem = (!useItem);
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
    sf::FloatRect playerBounds = playerArg.getGlobalBounds();

    float GAP_THRESHOLD = 10.f;
    for (auto iter = 0; iter < gameWorldPtr->fallenTreesVector.size(); ++iter) {
        if (playerBounds.intersects(gameWorldPtr->fallenTreesVector[iter].getGlobalBounds()))
            return true;
    }
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

void Engine::updatePlayerMovement(float modifier) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        playerMovement.y -= playerMoveSpeed*modifier;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        playerMovement.y += playerMoveSpeed*modifier;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        playerMovement.x -= playerMoveSpeed*modifier;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        playerMovement.x += playerMoveSpeed*modifier;
}

void Engine::updateItem() {
    overItem = false;
    for (auto iter = 0; iter < gameWorldPtr->batteriesVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(gameWorldPtr->batteriesVector[iter].getGlobalBounds())) {
            gameWorldPtr->batteriesVector[iter].setOutlineColor(sf::Color::Yellow);
            gameWorldPtr->batteriesVector[iter].setOutlineThickness(5.f);
            highlightedIter = iter;
            overItem = true;
            itemType = "battery";
            break;
        } 
    }
    for (auto iter = 0; iter < gameWorldPtr->holySymbolsVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(gameWorldPtr->holySymbolsVector[iter].getGlobalBounds())) {
            gameWorldPtr->holySymbolsVector[iter].setOutlineColor(sf::Color::Yellow);
            gameWorldPtr->holySymbolsVector[iter].setOutlineThickness(5.f);
            highlightedIter = iter;
            overItem = true;
            itemType = "holy symbol";
            break;
        } 
    }
    for (auto iter = 0; iter < gameWorldPtr->mushroomsVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(gameWorldPtr->mushroomsVector[iter].getGlobalBounds())) {
            gameWorldPtr->mushroomsVector[iter].setOutlineColor(sf::Color::Yellow);
            gameWorldPtr->mushroomsVector[iter].setOutlineThickness(5.f);
            highlightedIter = iter;
            overItem = true;
            itemType = "mushroom";
            break;
        } 
    }

    if (overItem && (!useItem)) {
        UIPtr->setOverItem(true);
        UIPtr->drawOverItemText(itemType);
    } else if (overItem && useItem)
        if (itemType == "battery") {
            if ((flashlightBattery + 10) > 100 ) {
                flashlightBattery = 100;
            } else {
                flashlightBattery += 10;
            }
            flashlightBatteryTimer = 0.f;

            logMessages.push_back(DataSettings::useBatteryString);
            gameWorldPtr->batteriesVector.erase(gameWorldPtr->batteriesVector.begin() + highlightedIter);
            useItem = false;
            
        } else if (itemType == "holy symbol") {
            UIPtr->setSanityBar(100.f);
            int randChanceToHeal = gameWorldPtr->randomInt(1, 10);
            if (randChanceToHeal > 3) {
                UIPtr->setHealthBar(60.f);
                logMessages.push_back(DataSettings::useHolySymbolString2);
            } else {
                logMessages.push_back(DataSettings::useHolySymbolString1);
            }

            gameWorldPtr->holySymbolsVector.erase(gameWorldPtr->holySymbolsVector.begin() + highlightedIter);
            useItem = false;
        } 

    if (!(overItem)) {
        UIPtr->setOverItem(false);
        if (highlightedIter != -1) {
            if (itemType == "battery")
                gameWorldPtr->batteriesVector[highlightedIter].setOutlineThickness(0.f);
            if (itemType == "holy symbol")
                gameWorldPtr->holySymbolsVector[highlightedIter].setOutlineThickness(0.f);
            if (itemType == "mushroom")
                gameWorldPtr->mushroomsVector[highlightedIter].setOutlineThickness(0.f);
            highlightedIter = -1;
        }
    } 
}

void Engine::modifySpeedIfObstacles() {
    overHideable = false;
    overRock = false;
    hideable = 0;
    for (auto iter = 0; iter < gameWorldPtr->shrubsVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(gameWorldPtr->shrubsVector[iter].getGlobalBounds())) {
            playerSpeedModifier -= 0.5;
            return;
        }
    }
    for (auto iter = 0; iter < gameWorldPtr->bushesVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(gameWorldPtr->bushesVector[iter].getGlobalBounds())) {
            playerSpeedModifier -= 0.5;
            overHideable = true;
            hideable = 1;
            return;
        }
    }
    for (auto iter = 0; iter < gameWorldPtr->mudPatchesVector.size(); ++iter) {
        if (gameWorldPtr->mudPatchesVector[iter].getGlobalBounds().contains(player.getPosition())) {                
            playerSpeedModifier -= 0.5;
            overHideable = true;
            hideable = 2;
            return;
        }        
    }
    for (auto iter = 0; iter < gameWorldPtr->rocksVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(gameWorldPtr->rocksVector[iter].getGlobalBounds())) {
            overRock = true;
        }
    }
    return;

}

void Engine::updateSanity(bool isMeditating) {
    std::cout << "Curr sanity: " << UIPtr->getBarCurrent("sanity").x << std::endl;
    if (!isMeditating) {
        UIPtr->setStatusMeditating(false);
        if (sanityTimer > 3) {
            UIPtr->setSanityBar(-6);
            sanityTimer = 0;
        }
    } else {
        UIPtr->setStatusMeditating(true);
        if (sanityTimer > 4) {
            UIPtr->setSanityBar(30);
            sanityTimer = 0;
        }
    }        
}

void Engine::handleBreath() {
    float breathCurrent = UIPtr->getBarCurrent("breath").x;
    float breathMax = UIPtr->getBarCurrent("breath").y;
    // std::cout << "breath current: " << breathCurrent << " breath max: " << breathMax << std::endl;

    if (statusRunning || (hidingActivated && hideable == 2) || breathCurrent < breathMax) {
        UIPtr->setDisplayBreathBar(true);
        isBreathing = true;
        if (((hidingActivated && hideable == 2) || statusRunning) && breathCurrent) {
            if (breathTimer > 1) {
                UIPtr->setBreathBar(-30);
                breathTimer = 0;
            }
        } else if (((hidingActivated && hideable == 2) || statusRunning) && (!breathCurrent)) {
            if (breathTimer > 3) {
                UIPtr->setHealthBar(-12);
                breathTimer = 0;
            }
        } else if ( (!hidingActivated || (hidingActivated && hideable == 1) ) && statusWalking && breathCurrent < breathMax) {
            if (breathTimer > 4) {
                UIPtr->setBreathBar(12);
                breathTimer = 0;
            }
        } else if ( (!hidingActivated || (hidingActivated && hideable == 1) ) && statusStill && breathCurrent < breathMax) {
            if (breathTimer > 2) {
                UIPtr->setBreathBar(30);
                breathTimer = 0;
            }
        }
    } else if (breathCurrent == breathMax) {
        isBreathing = false;
        UIPtr->setDisplayBreathBar(false);
    }
}

void Engine::updateHiding(bool hidingActivated, bool overHideable, int hideable) {
    if (!overHideable)
        UIPtr->setOverHideable(false);

    if (!hidingActivated) {
        UIPtr->setStatusHiding(false);
        player.setFillColor(playerSkinTone);
        if (leftHiding) {
            flashlightOn = true;
            leftHiding = false;
        }
    }

    if (!hidingActivated && overHideable) {
        UIPtr->setOverHideable(true);
        UIPtr->drawOverHideableText(hideable);
    }
    
    if (hidingActivated) {
        UIPtr->setOverHideable(false);
        UIPtr->setStatusHiding(true);
        player.setFillColor(CustomColors::invisible);
        flashlightOn = false;
        leftHiding = true;
    }
}

void Engine::updateUIActivityLevel(bool statusStill, bool statusWalking, bool statusRunning) {
    std::string activity;
    if (statusStill) {
        activity = "Still";
    } else if (statusWalking) {
        activity = "Walking";
    } else if (statusRunning) {
        activity = "Running";
    }
    UIPtr->setStatusActivityLevel(activity);
}

// TODO: move player collision stuff to its own function
void Engine::updatePlayer() {
    // std::cout << "Player speed modifier: " << playerSpeedModifier << " Player move speed: " << playerMoveSpeed << " Player movement x: " << playerMovement.x << " Player movement y: " << playerMovement.y << std::endl;
    statusStill = false;
    statusWalking = false;
    statusRunning = false;
    playerMovement = sf::Vector2f(0,0);

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
    if (gameAreaBoundsPtr->contains(playerNewPosition) && !playerObjectCollision(newPlayer)) {
        player.setPosition(playerNewPosition);  // Update the player's position
    } else {
        if (!(gameAreaBoundsPtr->contains(playerNewPosition))) {
            playerOutOfBoundsAdjust();
        }
    }
    
    // std::cout << "Statusstill: " << statusStill << " Statuswalking: " << statusWalking << " Statusrunning: " << statusRunning << std::endl; 
}

void Engine::updateLog() {
    if (logMessages.size()) {
        UIPtr->setLogMessage(true, logMessages[0]);
        if (logTimer > 5.f) {
            logMessages.erase(logMessages.begin());
            logTimer = 0;
        }
    } else {
        UIPtr->setLogMessage(false, "");
        logTimer = 0;
    }
}

void Engine::updateUI() {
    updateSanity(meditateActivated);
    updateHiding(hidingActivated, overHideable, hideable);
    updateUIActivityLevel(statusStill, statusWalking, statusRunning);
    updateLog();
}

void Engine::updateLight() {
    // Calculate the midpoint of the circle, then set lightPtr equal to
    circlePosition = player.getPosition();
    float circleRadius = player.getRadius();
    playerMidpoint = sf::Vector2f(circlePosition.x + circleRadius, circlePosition.y + circleRadius);
    lightPtr->setPosition(playerMidpoint - sf::Vector2f(3.f,3.f));

    if (!flashlightOn) {
        lightPtr->setFade(true);
        lightPtr->setRange(DataSettings::lightRangeOff);
    } else if (currentLightRange > 200.f) {
        lightPtr->setFade(false);
        lightPtr->setRange(currentLightRange);
        if (flashlightBatteryTimer > 5.f) {
            flashlightBattery -= 1;
            flashlightBatteryTimer = 0;
            currentLightRange-=4.f;
        }
    }

    std::string flashlightBatteryString;
    flashlightBatteryString = std::to_string(flashlightBattery);
    if (flashlightBattery > 75) {
        UIPtr->setBattery(flashlightBatteryString, sf::Color::Green);
    } else if (flashlightBattery >= 50 && flashlightBattery <= 75) {
        UIPtr->setBattery(flashlightBatteryString, sf::Color::Yellow);
    } else if (flashlightBattery > 1 && flashlightBattery <= 50) {
        UIPtr->setBattery(flashlightBatteryString, sf::Color::Red);
    }
}

void Engine::updateAudio() {
    if (clickedFlashlight != flashlightOn) {
        audioPtr->playFlashlightClick();
        clickedFlashlight = flashlightOn;
    }
}

void Engine::update() {
    pollEvents();
    updatePlayer();
    handleBreath();

    fps.update();
    std::ostringstream ss;
    ss << fps.getFPS();
    getElapsed = clock.getElapsedTime();
    totalTime += getElapsed.asSeconds();
    currentTime = clock.restart().asSeconds();
    sanityTimer += currentTime;
    if (flashlightOn)
        flashlightBatteryTimer += currentTime;
    if (isBreathing) {
        breathTimer += currentTime;
    } else {
        breathTimer = 0;
    }
    if (logMessages.size() > 0)
        logTimer += currentTime;

    updateUI();
    updateLight();
    updateItem();
    updateAudio();
    
    window->setTitle("Forest of Shapes || FPS: " + ss.str());
    std::cout << "Total time: " << totalTime << " Current time: " << currentTime << " sanityTimer: " << sanityTimer << " breathTimer: " << breathTimer << " flashlightBatteryTimer: " << flashlightBatteryTimer << " logTimer: " << logTimer << std::endl;
}

// RENDER FUNCTIONS
void Engine::renderUI(sf::RenderTarget& target) {
    UIPtr->renderUI(target);
}

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
    window->draw(visibleToPlayer);
    window->draw(player);

    // for (auto iter = 0; iter < gameWorldPtr->bushesVector.size(); ++iter) {
    //     if (lightPtr->getGlobalBounds().contains(gameWorldPtr->bushesVector[iter].getOrigin()))
    //         window->draw(gameWorldPtr->bushesVector[iter]);
    // }

    // Draw UI
    window->setView(window->getDefaultView());
    renderUI(*this->window);
    // window->draw(UIElem);

    // Finished drawning
    window->display();
}