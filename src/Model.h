#pragma once

#include "MVC.h"
#include "Block.h"

class Model {
public:
    Model();
    virtual ~Model();
	void iterate();
    void loadAndPlayMusic();
	sf::Color getColor(unsigned x, unsigned y) const;
	void moveLeft();
	void moveRight();
	void rotateLeft();
	void rotateRight();
	void clearMap();

	static const int Width = 10;
	static const int Height = 22;
	static const int TetrominoesAmount = 7;

    sf::Music music;

private:
	void spawnBlock();
	void push();
	void pop();
	bool isCollision();

	sf::Color map[Width][Height];
	sf::Color clearColor = sf::Color::Transparent;
	Block blocks[TetrominoesAmount];
	int actualBlock;
	char tetrominos[TetrominoesAmount] = {'I', 'O', 'T', 'S', 'Z', 'J', 'L'};
	int x, y;
};
