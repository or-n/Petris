#include "GameView.h"

GameView::GameView(Model &model, Controller *controller, sf::RenderWindow &window)
    : model(model)
    , controller(*controller)
    , window(window) {
}

GameView::~GameView() {
}

void GameView::newFrame() {
    window.clear();
    window.display();
}
