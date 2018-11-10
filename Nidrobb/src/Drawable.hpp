#ifndef DRAWABLE_HPP
#define DRAWABLE_HPP 

#include "SDL2/SDL.h"
#include "./gui/sprite.hpp"

class Drawable
{
public:
	//Drawable(){};
	virtual ~Drawable(){};
	//virtual SDL_Texture *getTexture() const = 0;//On recupere la texture de l'objet dessinable
	//virtual SDL_Rect *getRect() const = 0;//On recupere la zone ou dessiner l'objet dessinable
	virtual Sprite& sprite() = 0; //On recupère l'objet dessinable (peut pas etre const à cause de texture ?)
	virtual const Sprite& sprite() const = 0;
};

#endif