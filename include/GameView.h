#pragma once

#include "Model.h"

class GameView : public View {
public:
    GameView(Model &model, Controller *controller, sf::RenderWindow &window);
    virtual ~GameView();
    void newFrame();

private:

    const Model &model;
    Controller &controller;
    sf::RenderWindow &window;
};
