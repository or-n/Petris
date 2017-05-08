#include "Model.h"

Model::Model() {
    loadAndPlayMusic();
	for(int i = 0; i < TetrominoesAmount; ++i)
		blocks[i].loadFromFile(ResourcesPath + tetrominos[i]);
	clearMap();
}

Model::~Model() {
}

void Model::iterate() {
	pop();
	--y;
	if(isCollision()) {
		++y;
		push();
		spawnBlock();
	}
	else
		push();
}

void Model::loadAndPlayMusic() {
    if(music.openFromFile(ResourcesPath + "TetrisThemeDubstep.ogg"))
        music.setVolume(50),
        music.setLoop(true),
        music.play();
}

sf::Color Model::getColor(unsigned x, unsigned y) const {
	assert(x < Width);
	assert(y < Height);
	return map[x][y];
}

void Model::clearMap() {
	for(int x = 0; x < Width; ++x)
		for(int y = 0; y < Height; ++y)
			map[x][y] = clearColor;
	spawnBlock();
}

void Model::spawnBlock() {
	actualBlock = rand() % 7;
	blocks[actualBlock].clearRotation();
	x = Width >> 1;
	y = Height - 1;
	if(!isCollision())
		push();
}

bool Model::isCollision() {
	sf::Vector2i position;
	for(int i = 0; i < blocks[actualBlock].getPointsAmount(); ++i) {
		position = blocks[actualBlock].getPoint(i),
		position.x = x + position.x / 2,
		position.y = y - position.y / 2;
		if(position.x < 0 || position.x >= Width
		|| position.y < 0 || position.y >= Height
	    || map[position.x][position.y] != clearColor)
			return true;
	}
	return false;
}

void Model::push() {
	assert(!isCollision());
	sf::Vector2i position;
	for(int i = 0; i < blocks[actualBlock].getPointsAmount(); ++i)
		position = blocks[actualBlock].getPoint(i),
		position.x = x + position.x / 2,
		position.y = y - position.y / 2,
        map[position.x][position.y] = blocks[actualBlock].getColor();
}

void Model::pop() {
	assert(!isCollision());
	sf::Vector2i position;
	for(int i = 0; i < blocks[actualBlock].getPointsAmount(); ++i)
		position = blocks[actualBlock].getPoint(i),
		position.x = x + position.x / 2,
		position.y = y - position.y / 2,
		map[position.x][position.y] = clearColor;
}

void Model::moveLeft() {
	pop();
	--x;
	if(isCollision())
		++x;
	push();
}

void Model::moveRight() {
	pop();
	++x;
	if(isCollision())
		--x;
	push();
}

void Model::rotateLeft() {
	pop();
	blocks[actualBlock].rotateLeft();
	if(isCollision())
		blocks[actualBlock].rotateRight();
	push();
}

void Model::rotateRight() {
	pop();
	blocks[actualBlock].rotateRight();
	if(isCollision())
		blocks[actualBlock].rotateLeft();
	push();
}


