#ifndef WORLDBUILDER_HPP
#define WORLDBUILDER_HPP

#include <map>
#include "../GameEnv/World.hpp"

using namespace std;

//Usine à monde
//Possiblement transformer en singleton
class WorldBuilder
{
	protected :
		SDL_Renderer *_renderer; //Outils de rendu lié à display (Détruit dans display)
		map<string,SDL_Texture *> _texture; //Dictionnaire des textures

	public:
		WorldBuilder(SDL_Renderer *renderer);
		~WorldBuilder();
		
		void addTexture(const string name, const string imgPath); //Ajout d'une texture au dictionnaire
		Obstacle* createObstacle(SDL_Texture * texture, const pair<int,int>& Pos, int width, int height) const; //Construit un obstacle

		//Pas de const à cause de SDL_Texture...
		World* sky(); //Construit la map aérienne
		World* collisionTest(); //Construit la map de test de collision
};

#endif	