#pragma once

#include "MVC.h"

class Model {
public:
    Model();
    virtual ~Model();
    void loadAndPlayMusic();

    sf::Music music;
};
