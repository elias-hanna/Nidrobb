#ifndef COLLIDABLE_HPP
#define COLLIDABLE_HPP

#include <SDL2/SDL.h>

//http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
//https://loka.developpez.com/tutoriel/sdl/collision/

class Collidable
{
public:
	//Collidable(){}
	virtual ~Collidable(){}

	//Manque des infos de direction de collision (un set de direction ?)
	virtual bool collideA(const SDL_Rect* box) const = 0; //Collisions passive
	virtual bool collideP(const SDL_Rect* box) const = 0; //Collisions active
	//On devrait avoir passiveCollide & *activeCollide* afin de pouvoir "parer"
};

#endif