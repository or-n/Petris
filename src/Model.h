#pragma once

#include "MVC.h"
#include "Block.h"

class Model {
public:
    Model();
    virtual ~Model();
	void iterate();
    void loadAndPlayMusic();
	sf::Color getColor(int x, int y) const;
	void moveLeft();
	void moveRight();
	void rotateLeft();
	void rotateRight();
	void clearMap();

	static const int Width = 10;
	static const int Height = 22;

    sf::Music music;

private:
	void spawnBlock();
	void push();
	void pop();
	bool isCollision();

	sf::Color map[Width][Height];
	sf::Color clearColor = sf::Color::Transparent;
	Block blocks[7];
	int actualBlock;
	char tetrominos[7] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	int width, height;
};
