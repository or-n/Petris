#pragma once

#include "Globals.h"

class Application {
public:
    Application() {}
    virtual ~Application() {}

    void run();

private:

    sf::ContextSettings getDefaultContextSettings() const;
    void processEvents();
    void iterate();
    void setStyle();
    void loadAndPlayMusic();

    ImVec4 colorActive = ImVec4(.5, 0, 0, .9);
    ImVec4 colorHovered = ImVec4(.4, 0, 0, .7);
    ImVec4 color = ImVec4(.125, .1, .1, .7);
    ImVec4 textColor = ImVec4(1, 1, 1, .7);

    int iteration = 0;
    sf::RenderWindow *window = nullptr;
    sf::Clock iterationClock, deltaClock;
    sf::CircleShape circle;
    sf::Music music;
};
