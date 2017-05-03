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
        view->newFrame();
    }
    delete menu;
    delete gameView;
    ImGui::SFML::Shutdown();
}

void Game::processEvent(const sf::Event &event) {
    ImGui::SFML::ProcessEvent(event);
    if(event.type == sf::Event::Closed)
        window.close();
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        if(view == gameView)
            view = menu;
}

void Game::processEvent(const std::string &event) {
    if(event == "Quit")
        window.close();
    else if(event == "Play")
        view = gameView;
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

