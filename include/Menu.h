#pragma once

#include "Model.h"

class Menu : public View {
public:
    Menu(Model &model, Controller *controller, sf::RenderWindow &window);
    virtual ~Menu();
    void newFrame();

private:
    void initCircle();
    void loadFont();
    void loadBackground();
    void animate();
    void drawGUI();
    void setStyle();
    void drawMenu();
    void drawOptions();
    void nextItem();

    const Model &model;
    Controller &controller;
    sf::RenderWindow &window;
    sf::Texture bgTexture, fontTexture;
    sf::Sprite bg;
    sf::CircleShape circle;
    sf::Clock deltaClock, iterationClock;
    int iteration = 0, menu = 0, x, y, delta;
    ImVec4 colorActive = ImVec4(.6, 0, 0, .9);
    ImVec4 colorHovered = ImVec4(.4, 0, 0, .7);
    ImVec4 color = ImVec4(.125, .1, .1, .7);
    ImVec4 textColor = ImVec4(1, 1, 1, .7);
    ImGuiIO &io = ImGui::GetIO();
};
