#include <SFML/Graphics.hpp>
#include "iostream"

#include "Game.h"
//#include "Textbox.h"

sf::Vector2i centerWindow((sf::VideoMode::getDesktopMode().width / 4) - 500, (sf::VideoMode::getDesktopMode().height / 4) - 535);
    Game textbox1(30, sf::Color::Red, true);

Game::Game(): 
    window(sf::VideoMode(1000, 1200), "Guess the Baseball Player!"),
    currentState(Gamestate::Initial), tempState(Gamestate::Initial) {
    playerManager.loadPlayers("players.csv");
    window.setPosition(centerWindow);
    window.setKeyRepeatEnabled(true);
     }


void Game::run() {
    while (window.isOpen()) {
        processEvents();
        if (tempState == currentState) {
            rend = 0;
        }
        else {
            rend = 1; 
            tempState = currentState;
        }
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {

            case sf::Event::Closed:
                window.close();
            case sf::Event::TextEntered:
                textbox1.typedOn(event);

        }
        // Handle other events based on current state
    }
}

void Game::update() {
    switch (currentState) {
        case Gamestate::Initial:
            handleInitial();
            break;
        case Gamestate::Selection:
            handleSelection();
            break;
        case Gamestate::Guessing:
            handleGuessing();
            break;
        //case Gamestate::Correct:
            //handleCorrect();
            //break;
        //case Gamestate::Incorrect:
            //handleIncorrect();
            //break;
    }
}

void Game::render() {
    if (rend != 0) {
        window.clear(sf::Color::Black);
    }
    if (currentState == Gamestate::Guessing) {
        //textbox1.drawTo(window);
    }
    // Render elements based on current state
    window.display();
}

void Game::handleInitial() {
    sf::RectangleShape startButton(sf::Vector2f(300, 150));
    startButton.setFillColor(sf::Color::Yellow);
    startButton.setPosition(350, 500);


    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf")) { // Use a font file (e.g. "arial.ttf")
            std::cerr << "Failed to load font." << std::endl;
            // Error handling (e.g. exit the program)
            std::exit(EXIT_FAILURE);
        }

    sf::Text startText("Start", font, 100);
    startText.setFillColor(sf::Color::Black);
    startText.setPosition(370, 500);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (startButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            currentState = Gamestate::Selection;
        }
    }

    window.draw(startButton);
    window.draw(startText);
}

void Game::handleSelection() {
    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf")) { // Use a font file (e.g. "arial.ttf")
            std::cerr << "Failed to load font." << std::endl;
            // Error handling (e.g. exit the program)
            std::exit(EXIT_FAILURE);
        }

    sf::RectangleShape HanshinB(sf::Vector2f(300, 50));
    HanshinB.setFillColor(sf::Color::Yellow);
    HanshinB.setPosition(325, 150);

    sf::Text HanshinT("Hanshin Tigers", font, 25);
    HanshinT.setFillColor(sf::Color::Black);
    HanshinT.setPosition(385, 160);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (HanshinB.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            currentState = Gamestate::Guessing;
            //break;
        }
    }

    window.draw(HanshinB);
    window.draw(HanshinT);
}

void Game::handleGuessing() {
    static const Player* currentPlayer = nullptr;
    if (!currentPlayer) {
        currentPlayer = &playerManager.getRandomPlayer();
        }
    
    sf::Sprite playerSprite(currentPlayer->getTexture());
    playerSprite.setPosition(100, 0);

    sf::RectangleShape inputBox(sf::Vector2f(300, 50));
    inputBox.setFillColor(sf::Color::White);
    inputBox.setOutlineColor(sf::Color::Yellow);
    inputBox.setOutlineThickness(2);
    inputBox.setPosition(250, 400);


    sf::Font font;
    if (!font.loadFromFile("misaki_gothic_2nd.ttf")) { // Use a font file (e.g. "arial.ttf")
            std::cerr << "Failed to load font." << std::endl;
            // Error handling (e.g. exit the program)
            std::exit(EXIT_FAILURE);
        }

    //Textbox textbox1(15, sf::Color::Black, true);
    textbox1.setFont(font);
    textbox1.setPosition({250, 400});

    sf::RectangleShape confirmButton(sf::Vector2f(100, 50));
    confirmButton.setFillColor(sf::Color::White);
    confirmButton.setPosition(350, 470);

    sf::Text dareda("Guess the Player!", font, 50);
    dareda.setFillColor(sf::Color::Yellow);
    dareda.setPosition(100, 0);

    sf::Text confirmText("Confirm", font, 20);
    confirmText.setFillColor(sf::Color::Black);
    confirmText.setPosition(365, 480);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (confirmButton.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            if (textbox1.getText() == currentPlayer->getName()) {
                window.close();
                std::cout << "SEIKAI" << std::endl;
                std::cout << textbox1.getText() << std::endl;
                // Correct guess
                //score++; // Assuming you've added a 'score' member to Game class
                // Move to next player or round
            } else {
                //window.close();
                std::cout << "FUSEIKAI" << std::endl;
                std::cout << "Your input: " + textbox1.getText() << std::endl;
                std::cout << "Correct answer: " + currentPlayer->getName() << std::endl;

                // Incorrect guess
                // Perhaps show correct answer and then move to next player or round
            }
            playerInput.clear();
            currentPlayer = nullptr; // Reset for next round
        }
    }


    window.draw(playerSprite);
    window.draw(dareda);
    window.draw(inputBox);
    window.draw(confirmButton);
    window.draw(confirmText);
    window.draw(inputText);
    textbox1.drawTo(window);
}