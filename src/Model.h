#pragma once

#include "MVC.h"

class Model {
public:
    Model();
    virtual ~Model();
    void loadAndPlayMusic();

	const int Width = 10;
	const int Height = 10;

    sf::Music music;
};
