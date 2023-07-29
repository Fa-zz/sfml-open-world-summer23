#include "Engine.hpp"

// PRIVATE FUNCTIONS, INIT FUNCTIONS
void Engine::initWindow() {
    window = new sf::RenderWindow(sf::VideoMode(DataSettings::videoModeWidth,DataSettings::videoModeHeight), "Forest of Shapes", sf::Style::Default | sf::Style::Close);
    window->setVerticalSyncEnabled(false);
    window->setFramerateLimit(DataSettings::frameRateLimit);
}

// Todo: Split into other funcs.
void Engine::initVars() {
    gameAreaSize = sf::Vector2f(DataSettings::gameWorldSizeX, DataSettings::gameWorldSizeY);
    gameAreaBoundsPtr = new sf::FloatRect(sf::Vector2f(0.f,0.f), gameAreaSize);
    meditateActivated = 0;
    hidingActivated = false;
    leftHiding = false;
    flashlightOn = false;
    clickedFlashlight = flashlightOn;
    breathTimer = 0;
    overItem = false;
    useItem = false;
    highlightedIter = -1;
    itemType = "";
    logTimer = 0;
    totalTime = 0;
    notesFound = 0;
    nextAppearanceTimer = appearanceHideTimer = 0;
    inAppearance = false;
    appearanceHappensAt = 0;
    appearanceLogMessage = false;
    playAppearanceMusic = playGhostlyWhispers = false;
    inFound = checkedInFound = false;
    viewOffset = sf::Vector2f(0.f,0.f);
}

void Engine::initLight() {
    // create a light source
    lightPtr = new candle::RadialLight();
    currentLightRange = DataSettings::lightRangeFull;
    lightPtr->setRange(currentLightRange);
    lightPtr->setFade(false);
    lightPtr->setIntensity(0.5);


    float fogRenderOffset = gameAreaSize.x / 10;
    fogPtr1 = new candle::LightingArea(candle::LightingArea::FOG, sf::Vector2f(-fogRenderOffset,-fogRenderOffset), sf::Vector2f(gameAreaSize.x+(fogRenderOffset*2), gameAreaSize.y+(fogRenderOffset*2)));    
    // fogPtr2 = new candle::LightingArea(candle::LightingArea::FOG, sf::Vector2f(gameAreaSize.x/2 -1000,-1000), sf::Vector2f(gameAreaSize.x/2+2000, gameAreaSize.y + 2000));
    fogPtr1->setAreaColor(sf::Color::Black);
    // fogPtr2->setAreaColor(sf::Color::Black);

    flashlightBattery = 100;
    flashlightBatteryTimer = 0;
}

void Engine::initPlayer() {
    playerPtr = new Player(gameWorldPtr, gameAreaBoundsPtr);
}

void Engine::initMonster() {

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
    delete fogPtr1;
    delete playerPtr;
    // delete fogPtr2;
    // delete fogPtr3;
    // delete fogPtr4;
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

void Engine::updateViewOffset() {
    if (inFound && !(inAppearance)) {
        float randomXOffset = gameWorldPtr->randomFloat(-10.f,10.f);
        float randomYOffset = gameWorldPtr->randomFloat(-10.f,10.f);
        std::cout << "xOffset: " << randomXOffset << " yOffset: " << randomYOffset << std::endl;
        viewOffset = sf::Vector2f(randomXOffset, randomYOffset);
    }
}

void Engine::updateItem() {
    overItem = false;
    for (auto iter = 0; iter < gameWorldPtr->itemsVector.size(); ++iter) {
        if (player.getGlobalBounds().intersects(gameWorldPtr->itemsVector[iter].getGlobalBounds())) {
            gameWorldPtr->itemsVector[iter].setOutlineColor(sf::Color::Yellow);
            gameWorldPtr->itemsVector[iter].setOutlineThickness(5.f);
            highlightedIter = iter;
            overItem = true;
            break;
        } 
    }

    if (highlightedIter != -1) {
        if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == sf::Color::Black)
            itemType = "battery";
        if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == CustomColors::holySymbolColor)
            itemType = "holy symbol";
        if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == CustomColors::mushroomColor)
            itemType = "mushroom";
        if (gameWorldPtr->itemsVector[highlightedIter].getFillColor() == CustomColors::noteColor)
            itemType = "note";
    }

    if (overItem && (!useItem)) {
        UIPtr->setOverItem(true);
        UIPtr->drawOverItemText(itemType);
    } else if (overItem && useItem) {
        if (itemType == "battery") {
            if ((flashlightBattery + 10) > 100 ) {
                flashlightBattery = 100;
            } else {
                flashlightBattery += 10;
            }
            currentLightRange += 40;
            flashlightBatteryTimer = 0.f;

            logMessages.push_back(DataSettings::useBatteryString);
            // gameWorldPtr->itemsVector.erase(gameWorldPtr->itemsVector.begin() + highlightedIter);
            // useItem = false;

        } else if (itemType == "holy symbol") {
            UIPtr->setSanityBar(100.f);
            int randChanceToHeal = gameWorldPtr->randomInt(1, 10);
            if (randChanceToHeal > 3) {
                UIPtr->setHealthBar(60.f);
                logMessages.push_back(DataSettings::useHolySymbolString2);
            } else {
                logMessages.push_back(DataSettings::useHolySymbolString1);
            }

        } else if (itemType == "note") {
            // Check if this was the first note found
            notesFound += 1;
            if (notesFound == 1)
                firstNoteFound = true;
        }

        gameWorldPtr->itemsVector.erase(gameWorldPtr->itemsVector.begin() + highlightedIter);
        useItem = false;

    }

    if (!(overItem)) {
        UIPtr->setOverItem(false);
        if (highlightedIter != -1) {
            gameWorldPtr->itemsVector[highlightedIter].setOutlineThickness(0.f);
            highlightedIter = -1;
        }
    }

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

}

void Engine::updateLog() {
    if (!(playerPtr->getPlayerOutOfBounds()))
        logMessages.push_back(DataSettings::outOfBoundsString);

    if (logMessages.size()) {
        sf::Color color;
        if (logMessages[0] == DataSettings::appearanceString) {
            color = sf::Color::Yellow;
        } else {
            color = sf::Color::White;
        }
        UIPtr->setLogMessage(true, logMessages[0], color);
        if (logTimer > 5.f) {

            if (logMessages[0] == DataSettings::outOfBoundsString) {
                logMessages.clear();
            } else {
                logMessages.erase(logMessages.begin());
            }
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
    UIPtr->setNotesFound(notesFound);
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
    if (playAppearanceMusic != inAppearance) {
        audioPtr->playAppearanceMusic();
        playAppearanceMusic = inAppearance;
    } else if (playAppearanceMusic == inAppearance && (playGhostlyWhispers != inAppearance)) {
        if (audioPtr->getAppearanceMusicStatus() == sf::Sound::Stopped) {
            audioPtr->playGhostlyWhispers();
            playGhostlyWhispers = inAppearance;
        }
    }
}

void Engine::updateMonster() {
    if (!inAppearance && !inFound)
        UIPtr->setMonsterText(false, false);

    if (!(appearanceHappensAt)) {
        int lowerBound = DataSettings::lowerBound - (10*notesFound);
        int upperBound = DataSettings::upperBound - (10*notesFound);
        appearanceHappensAt = gameWorldPtr->randomInt(lowerBound, upperBound);
    }
    std::cout << "Appearance happens at: " << appearanceHappensAt << std::endl;

    if (nextAppearanceTimer > appearanceHappensAt) {
        int appearanceChance = gameWorldPtr->randomInt(0,100);
        if (UIPtr->getBarCurrent("sanity").x > 300 && UIPtr->getBarCurrent("sanity").x > 210) {
            appearanceChance -= 25;
        } else if (UIPtr->getBarCurrent("sanity").x <= 210 && UIPtr->getBarCurrent("sanity").x >= 150) {
            appearanceChance += 50;
        } else if (UIPtr->getBarCurrent("sanity").x <= 150) {
            appearanceChance += 75;
        }
        for (int i = 0; i < notesFound; i++)
            appearanceChance += 25;

        std::cout << "APPEARANCE CHECK, appearance chance: " << appearanceChance << std::endl;
        if (appearanceChance >= 75) {
            inAppearance = true;
            appearanceLogMessage = true;
        }
        nextAppearanceTimer = 0;
        appearanceHappensAt = 0;
    }

    if (inAppearance) {
        if (appearanceLogMessage) {
            logMessages.push_back(DataSettings::appearanceString);
            appearanceLogMessage = false;
        }
        UIPtr->setMonsterText(true, false);

        if (appearanceHideTimer > 15 && (!checkedInFound)) {
            appearanceHideTimer = 0;
            int foundChance = 0;
            if (hidingActivated && hideable == 2) {
                foundChance = gameWorldPtr->randomInt(1,5);
                if (foundChance == 1)
                    inFound = true;
            } else if (hidingActivated && hideable == 1) {
                foundChance = gameWorldPtr->randomInt(1,3);
                if (foundChance == 1)
                    inFound = true;
            } else if (!hidingActivated) {
                foundChance = gameWorldPtr->randomInt(1, 11);
                if (foundChance > 1)
                    inFound = true;
            }
            checkedInFound = true;
        }
    }

    if ((inAppearance) && (checkedInFound) && !(audioPtr->getGhostlyWhispersStatus() == sf::Music::Playing)) {
        inAppearance = false;
        playAppearanceMusic = false;
        playGhostlyWhispers = false;
        appearanceHideTimer = 0;
        checkedInFound = false;
    }

    if (inFound && (!inAppearance)) {
        UIPtr->setMonsterText(false, true);
    }

}

void Engine::update() {
    pollEvents();
    // updateViewOffset();
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

    if (!(inAppearance) && !(inFound) && !(audioPtr->getGhostlyWhispersStatus() == sf::Music::Playing)) {
        nextAppearanceTimer += currentTime;
    } else if ((inAppearance) && (!inFound)) {
        nextAppearanceTimer = 0;
        appearanceHideTimer += currentTime;
    } else if (inFound) {
        nextAppearanceTimer = 0;
        appearanceHideTimer = 0;
    }

    updateUI();
    updateLight();
    updateItem();
    updateAudio();
    updateMonster();
    
    window->setTitle("Forest of Shapes || FPS: " + ss.str());
    // std::cout << "Total time: " << totalTime << " Current time: " << currentTime << " sanityTimer: " << sanityTimer << " breathTimer: " << breathTimer << " flashlightBatteryTimer: " << flashlightBatteryTimer << " nextAppearanceTimer: " << nextAppearanceTimer << " hideTimer: " << appearanceHideTimer << std::endl;
    std::cout << "Total time: " << totalTime << " Current time: " << currentTime << " nextAppearanceTimer: " << nextAppearanceTimer << " hideTimer: " << appearanceHideTimer << std::endl;
    std::cout << "Player pos x: " << player.getPosition().x << " Player pos y: " << player.getPosition().y << std::endl;
    std::cout << "inAppearance: " << inAppearance << " inFound: " << inFound << std::endl;
}

// RENDER FUNCTIONS
void Engine::renderUI(sf::RenderTarget& target) {
    UIPtr->renderUI(target);
}

void Engine::renderObjects(sf::RenderTarget& target) {
    gameWorldPtr->render(target);
}

void Engine::render() {
    mainView.setCenter(player.getPosition()+viewOffset);
    // Draw

    // Draw light, fog
    fogPtr1->clear();
    fogPtr1->draw(*lightPtr);
    fogPtr1->display();
    // fogPtr2->clear();
    // fogPtr2->draw(*lightPtr);
    // fogPtr2->display();

    window->clear(CustomColors::groundColor);

    window->setView(mainView);

    // Draw objects
    renderObjects(*this->window);

    window->draw(*fogPtr1);
    // window->draw(*fogPtr2);
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