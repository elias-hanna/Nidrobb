#include "Obstacle.hpp"

Obstacle::Obstacle(Sprite& s, SDL_Rect* collisionBox)
{
	_sprite = s;
	_collisionBox = collisionBox;
}

Obstacle::~Obstacle()
{
	//std::cout<<"Destructeur Obstacle"<<std::endl;
	delete _collisionBox;
}

//Verifie s'il y a collision avec une hitbox
bool Obstacle::collideP(const SDL_Rect* box) const
{
	//std::cout<<"Obstacle : Collision test"<<std::endl;
	if(SDL_HasIntersection(box,_collisionBox)  == SDL_TRUE) //Collision avec une hitbox
			return true;
	else
		return false;
}

Obstacle& Obstacle::operator=(const Obstacle& o)
{
	_sprite = o.sprite();
	_collisionBox = createRect(o.box()->x, o.box()->y, o.box()->w, o.box()->h);

	//std::cout<<"Obs = : "<<*this->box()<<std::endl;
	return *this;
}

bool Obstacle::operator==(const Obstacle& o) const
{
	if(_sprite==o.sprite() && SDL_RectEquals(_collisionBox, o.box()) == SDL_TRUE)
		return true;
	else
		return false;
}