#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

//#include "../gui/sprite.hpp" //Dans drawable
#include "../Drawable.hpp"
#include "../Collidable.hpp"
#include <iostream>

//std::ostream& operator<<(std::ostream& os, const SDL_Rect& r); //Forward declaration

//Obstacle passif
class Obstacle : public Drawable, public Collidable
{
protected:
SDL_Rect* _collisionBox;
Sprite _sprite;
public:
	Obstacle(Sprite& s, SDL_Rect* collisionBox);
	Obstacle(const Obstacle& o){ *this = o;}
	~Obstacle();

	bool collideA(const SDL_Rect* box) const { return false;} //Obstacles passifs
	bool collideP(const SDL_Rect* box) const; //Verifie s'il y a collision avec une hitbox

	//Accesseurs
	std::pair<int,int> center() { return std::make_pair(_collisionBox->x+_collisionBox->w/2,_collisionBox->y+_collisionBox->h/2);}
	Sprite& sprite() { return _sprite;}
	const Sprite& sprite() const { return _sprite;}
	const SDL_Rect* box() const{ return _collisionBox;}

	Obstacle& operator=(const Obstacle& o);
	bool operator==(const Obstacle& o) const;
};

#endif