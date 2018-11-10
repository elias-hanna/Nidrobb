#ifndef TOOLBOX_HPP
#define TOOLBOX_HPP

#include <iostream>
#include <SDL2/SDL.h>

SDL_Rect *createRect(int x, int y, int w, int h);
std::ostream& operator<<(std::ostream& os, const SDL_Rect& r);
//bool checkCollision(const SDL_Rect* a, const SDL_Rect* b );

#endif