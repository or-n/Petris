#pragma once

#include "Menu.h"
#include "GameView.h"

class Game : public Controller {
public:
    Game();
    virtual ~Game();
    void run();
    void processEvent(const sf::Event &event);
    void processEvent(const std::string &event);

private:
    void initWindow();

    sf::RenderWindow window;
    Model model;
    View *view, *menu, *gameView;
};
