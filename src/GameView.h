#pragma once

#include "Model.h"

class GameView : public View {
public:
    GameView(Model &model, Controller *controller, sf::RenderWindow &window);
    virtual ~GameView();
    void newFrame();

private:
	void initBlock();
	void drawBlock(sf::Color color, sf::Vector2u position);
	void drawGUI();

    const Model &model;
    Controller &controller;
    sf::RenderWindow &window;
	ImGuiIO &io = ImGui::GetIO();
	sf::VertexArray block;
	sf::Vector2f blockSize = {io.DisplaySize.y / io.DisplaySize.x, 1};
	sf::Shader blockShader;
	sf::Clock deltaClock;
	sf::Color borderColor = sf::Color(63, 63, 63);
};
