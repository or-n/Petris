#include "Model.h"

Model::Model() {
    loadAndPlayMusic();
}

Model::~Model() {
}

void Model::loadAndPlayMusic() {
    if(music.openFromFile(ResourcesPath + "TetrisThemeDubstep.ogg"))
        music.setVolume(50),
        music.setLoop(true),
        music.play();
}


