#include "Block.h"

Block::Block() {
}

Block::~Block() {
}

void Block::loadFromFile(const std::string &filename) {
	points.clear();
	FILE *file = fopen(filename.c_str(), "r");
	int pointsAmount, r, g, b;
	fscanf(file, "%d", &pointsAmount);
	while(pointsAmount--)
		fscanf(file, "%d%d", &origin.x, &origin.y),
		points.push_back(origin);
	fscanf(file, "%d%d%d", &r, &g, &b);
	color = sf::Color(r, g, b);
	fscanf(file, "%d%d", &origin.x, &origin.y);
	fclose(file);
}

void Block::clearRotation() {
	rightRotationsCounter %= 4;
	while(rightRotationsCounter != 0)
		rotateRight(),
		rightRotationsCounter %= 4;
}

void Block::rotateLeft() {
	rotateRight();
	rotateRight();
	rotateRight();
}

void Block::rotateRight() {
	++rightRotationsCounter;
	sf::Vector2i newPoint;
	for(sf::Vector2i &point : points)
		point = sf::Vector2i(-point.y + origin.y + origin.x, point.x - origin.x + origin.y);
}

int Block::getPointsAmount() const {
	return points.size();
}

sf::Vector2i Block::getPoint(unsigned index) const {
	assert(index < points.size());
	return points[index];
}

sf::Color Block::getColor() const {
	return color;
}
