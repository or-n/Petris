#include "Model.h"

Model::Model() {
    loadAndPlayMusic();
	for(int i = 0; i < 7; ++i)
		blocks[i].loadFromFile(ResourcesPath + tetrominos[i]);
	clearMap();
}

Model::~Model() {
}

void Model::iterate() {
	pop();
	--height;
	if(isCollision()) {
		++height;
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

sf::Color Model::getColor(int x, int y) const {
	assert(x >= 0 && x < Width);
	assert(y >= 0 && y < Height);
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
	width = Width >> 1;
	height = Height - 1;
	if(!isCollision())
		push();
}

bool Model::isCollision() {
	sf::Vector2i position;
	for(int i = 0; i < blocks[actualBlock].getPointsAmount(); ++i) {
		position = blocks[actualBlock].getPoint(i),
		position.x =  position.x / 2 + width,
		position.y = -position.y / 2 + height;
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
		position.x =  position.x / 2 + width,
		position.y = -position.y / 2 + height,
        map[position.x][position.y] = blocks[actualBlock].getColor();
}

void Model::pop() {
	assert(!isCollision());
	sf::Vector2i position;
	for(int i = 0; i < blocks[actualBlock].getPointsAmount(); ++i)
		position = blocks[actualBlock].getPoint(i),
		position.x =  position.x / 2 + width,
		position.y = -position.y / 2 + height,
		map[position.x][position.y] = clearColor;
}

void Model::moveLeft() {
	pop();
	--width;
	if(isCollision())
		++width;
	push();
}

void Model::moveRight() {
	pop();
	++width;
	if(isCollision())
		--width;
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


