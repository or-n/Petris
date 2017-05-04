#pragma once

#include "Globals.h"

class Model;

class View {
public:
    virtual void newFrame();
};

class Controller {
public:
    virtual void run();
    virtual void processEvent(const sf::Event&);
    virtual void processEvent(const std::string&);
};
