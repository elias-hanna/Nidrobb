#include "../GameEnv/World.hpp"

World::World(const std::string& name, const Sprite& background, const std::vector<Obstacle*>& obsList) : _worldName(name)
{
	_background = background;
	for(Obstacle* o : obsList)
	{
		Obstacle* newObs = new Obstacle(*o);
		_obsList.push_back(newObs);
	}
	// for(Obstacle* o : _obsList)
	// {
	// 	std::cout<<"World :"<<*o->box()<<std::endl;
	// }
}

World::~World()
{
	for(Obstacle* o : _obsList)
	{
		delete o;
	}
}

// void World::setSprite(SDL_Renderer *renderer,std::string imgPath)
// {
// 	SDL_Rect* BackBox = createRect(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
// 	_background = Sprite(renderer,BackBox,imgPath);
// }

World& World::operator=(const World& w)
{
	_worldName = w.name();
	_background = w.sprite();
	std::vector<Obstacle*> obsList = w.obstacles();
	for(Obstacle* o : obsList)
	{
		Obstacle* newObs = new Obstacle(*o);
		_obsList.push_back(newObs);
	}
	return *this;
}