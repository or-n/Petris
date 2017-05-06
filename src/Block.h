#pragma once

#include "Globals.h"

class Block {
public:
	Block();
	virtual ~Block();
	void loadFromFile(const std::string &filename);
	void clearRotation();
	void rotateLeft();
	void rotateRight();
	int getPointsAmount() const;
	sf::Vector2i getPoint(unsigned index) const;
	sf::Color getColor() const;

private:

	int rightRotationsCounter = 0;
	sf::Color color;
	sf::Vector2i origin;
	std::vector<sf::Vector2i> points;
};