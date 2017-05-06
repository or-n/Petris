#include "GameView.h"

GameView::GameView(Model &model, Controller *controller, sf::RenderWindow &window)
    : model(model)
    , controller(*controller)
    , window(window) {
	initBlock();
}

GameView::~GameView() {
}

void GameView::newFrame() {
	window.clear();
	for(int x = 1; x <= model.Width; ++x)
		drawBlock(borderColor, sf::Vector2u(x, 0));
	for(int y = 0; y < model.Height; ++y)
		drawBlock(borderColor, sf::Vector2u(0, y)),
		drawBlock(borderColor, sf::Vector2u(model.Width + 1, y));
	for(int x = 0; x < model.Width; ++x)
		for(int y = 0; y < model.Height; ++y)
			drawBlock(model.getColor(x, y), sf::Vector2u(x + 1, y + 1));
	window.pushGLStates();
	drawGUI();
	window.popGLStates();
    window.display();
}

void GameView::initBlock() {
	block = sf::VertexArray(sf::Quads, 4);
	block[0].position = sf::Vector2f(-1, -1);
	block[1].position = sf::Vector2f(1, -1);
	block[2].position = sf::Vector2f(1, 1);
	block[3].position = sf::Vector2f(-1, 1);
	blockSize.x /= model.Height;
	blockSize.y /= model.Height;
	blockShader.loadFromFile(ResourcesPath + "block.vert", ResourcesPath + "block.frag");
	blockShader.setUniform("_blockSize", sf::Glsl::Vec2(blockSize));
}

void GameView::drawBlock(sf::Color color, sf::Vector2u position) {
	blockShader.setUniform("_color", sf::Glsl::Vec4(color));
	blockShader.setUniform("_blockPos", sf::Glsl::Vec2(-1 + (2 * position.x + 1) * blockSize.x, -1 + (2 * position.y + 1) * blockSize.y));
	window.draw(block, &blockShader);
}

void GameView::drawGUI() {
	ImGui::SFML::Update(window, deltaClock.restart());
	ImGui::Begin("", nullptr, ImVec2(1920, 1080), 0,
	             ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings);
	ImGui::SetCursorPosX(io.DisplaySize.x / 2);
	ImGui::SetCursorPosY(io.DisplaySize.y / 2);
	if(ImGui::Button("New Game"))
		controller.processEvent("Clear");
	ImGui::End();
	ImGui::Render();
}