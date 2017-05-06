#include "Controller.h"

Game::Game() {
}

Game::~Game() {
}

void Game::run() {
    initWindow();
    ImGui::SFML::Init(window);
    menu = new Menu(model, this, window);
    gameView = new GameView(model, this, window);
    view = menu;
    while(window.isOpen() && view) {
        sf::Event event;
        while(window.pollEvent(event))
            processEvent(event);
	    if(movementClock.getElapsedTime().asMilliseconds() > 50) {
		    movementClock.restart();
		    viewDelay = 200;
		    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			    model.moveLeft();
		    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			    model.moveRight();
		    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			    viewDelay = 50;
	    }
        view->newFrame();
	    if(view == gameView && viewClock.getElapsedTime().asMilliseconds() > viewDelay)
		    viewClock.restart(),
		    model.iterate();
    }
    delete menu;
    delete gameView;
    ImGui::SFML::Shutdown();
}

void Game::processEvent(const sf::Event &event) {
	ImGui::SFML::ProcessEvent(event);
	if(event.type == sf::Event::Closed)
		window.close();
	else if(event.type == sf::Event::KeyPressed)
		if(view == gameView)
			if(event.key.code == sf::Keyboard::Escape)
				view = menu;
			else if(event.key.code == sf::Keyboard::Up)
				model.rotateRight();
}

void Game::processEvent(const std::string &event) {
    if(event == "Quit")
        window.close();
    else if(event == "Play")
        view = gameView;
    else if(event == "Clear")
	    model.clearMap();
    else if(event.find("Volume") == 0) {
        int volume;
        sscanf(event.c_str(), "Volume %d", &volume);
        model.music.setVolume(volume);
    }
}

void Game::initWindow() {
    window.create(sf::VideoMode::getDesktopMode(), "Petris", sf::Style::Fullscreen);
    window.setFramerateLimit(128);
    window.setVerticalSyncEnabled(true);
}

