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
	for(int i = 1; i <= 8; ++i) {
		drawBlock(sf::Color(225, 225, 0), sf::Vector2u(1, i));
		drawBlock(sf::Color(0, 195, 0), sf::Vector2u(2, i));
		drawBlock(sf::Color(255, 0, 0), sf::Vector2u(3, i));
		drawBlock(sf::Color(255, 95, 255), sf::Vector2u(4, i));
		drawBlock(sf::Color(63, 63, 255), sf::Vector2u(5, i));
		drawBlock(sf::Color(255, 63, 0), sf::Vector2u(6, i));
		drawBlock(sf::Color(0, 195, 195), sf::Vector2u(7, i));
	}
    window.display();
}

void GameView::initBlock() {
	block = sf::VertexArray(sf::Quads, 4);
	block[0].position = sf::Vector2f(-1, -1);
	block[1].position = sf::Vector2f(1, -1);
	block[2].position = sf::Vector2f(1, 1);
	block[3].position = sf::Vector2f(-1, 1);
	blockSize.x /= std::max(model.Width, model.Height);
	blockSize.y /= std::max(model.Width, model.Height);
	blockShader.loadFromFile(ResourcesPath + "block.vert", ResourcesPath + "block.frag");
	blockShader.setUniform("_blockSize", sf::Glsl::Vec2(blockSize));
}

void GameView::drawBlock(sf::Color color, sf::Vector2u position) {
	blockShader.setUniform("_color", sf::Glsl::Vec4(color));
	blockShader.setUniform("_blockPos", sf::Glsl::Vec2(-1 + (2 * position.x + 1) * blockSize.x, -1 + (2 * position.y + 1) * blockSize.y));
	window.draw(block, &blockShader);
}
