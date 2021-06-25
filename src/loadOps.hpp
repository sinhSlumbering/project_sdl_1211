#ifndef LOADOPS_H
#define LOADOPS_H

#include "preprocessor.hpp"
#include "textureMusic.hpp"

//loads texuture
SDL_Texture *loadTex(std::string path);

//loads texure and sound
bool loadMedia();

//destroys texture and files from memory, closes all systems and shuts down
void close();

#endif