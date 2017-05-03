#include "Controller.h"

Game::Game() {
}

Game::~Game() {
    if(view)
        delete view;
}

void Game::run() {
    initWindow();
    ImGui::SFML::Init(window);
    view = new Menu(model, this, window);
    while(window.isOpen() && view) {
        sf::Event event;
        while(window.pollEvent(event))
            processEvent(event);
        view->newFrame();
    }
    ImGui::SFML::Shutdown();
}

void Game::processEvent(const sf::Event &event) {
    ImGui::SFML::ProcessEvent(event);
    if(event.type == sf::Event::Closed)
        window.close();
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
        window.close();
}

void Game::processEvent(const std::string &event) {
    if(event == "Quit")
        window.close();
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

