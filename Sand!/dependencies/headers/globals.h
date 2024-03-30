#ifndef GLOBALS_H
#define GLOBALS_H

#include "raylib.h"
#include "gameobjects.h"
#include <list>
#include <vector>


extern std::list<GameObjects*> gameObject;

extern int windowWidth;
extern int windowHeight;

extern float mouseX;
extern float mouseY;

#endif