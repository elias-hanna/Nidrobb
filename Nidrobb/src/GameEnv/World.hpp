#ifndef WORLD_HPP
#define WORLD_HPP

//#include <iostream>
#include <vector>
#include "../GameEnv/Obstacle.hpp"
//#include "../gui/Sprite.hpp"
#include "../GameParam.hpp"

//std::ostream& operator<<(std::ostream& os, const SDL_Rect& r); //Forward (Game)

//Représente un monde de jeu
class World : public Drawable
{
protected:
	std::string _worldName; //Nom du monde
	std::vector<Obstacle*> _obsList; //Liste des objets solides
	Sprite _background; //Fond

public:
	//World(){}
	World(const std::string& name, const Sprite& background, const std::vector<Obstacle*>& obsList);
	World(const World& w){ *this = w;}
	~World();

	//BOF BOF
	//void addObs(const Obstacle& newObstacle) { return _obsList.push_back(new Obstacle(newObstacle));}
	//void setSprite(SDL_Renderer *renderer,std::string imgPath); //Fuites memoires

	//Accesseurs
	const std::string& name() const { return _worldName;}
	const std::vector<Obstacle*>& obstacles() const { return _obsList;}
	Sprite& sprite(){ return _background;}
	const Sprite& sprite() const{ return _background;}

	World& operator=(const World& w);
};

#endif