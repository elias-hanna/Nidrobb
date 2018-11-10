#ifndef ANIMATIONBUILDER_HPP
#define ANIMATIONBUILDER_HPP

#include <map>
#include "../Animation/Animation.hpp"

#include "../GameParam.hpp"

SDL_Rect *createRect(int x, int y, int w, int h); //Forward Declaration (Game.cpp)

//Usine à animation
//Possiblement transformer en singleton
class AnimationBuilder
{
protected:
	SDL_Renderer *_renderer; //Outils de rendu lié à display (Détruit dans display)
	map<string,SDL_Texture *> _texture; //Dictionnaire des textures
public:
	AnimationBuilder(SDL_Renderer *renderer);
	~AnimationBuilder();

	void addTexture(const string name, const string imgPath); //Ajout d'une texture au dictionnaire
	//Construit une frame de joueur. Par défaut, sans active hitbox et avec le rectangle de texture en passive hitbox.
	AnimationFrame* PlayerFrame(SDL_Texture * texture, const pair<int,int>& Pos, SDL_Rect* SpriteRect = nullptr, const vector<SDL_Rect*> ahitbox =vector<SDL_Rect*>(), const vector<SDL_Rect*>& phitbox =vector<SDL_Rect*>()) const;

	//Pas de const à cause de SDL_Texture...
	Animation* stand(const pair<int,int>& StartPos); //Construit l'animation statique
	Animation* moveRight(const pair<int,int>& StartPos); //Construit un déplacement vers la droite
	Animation* moveLeft(const pair<int,int>& StartPos); //Construit un déplacement vers la gauche
	Animation* jump(const pair<int,int>& StartPos); //Construit un saut
	Animation* rightJump(const pair<int,int>& StartPos); //Construit un saut vers la droite
	Animation* leftJump(const pair<int,int>& StartPos); //Construit un saut vers la gauche
	Animation* crouch(const pair<int,int>& StartPos); //Constuit l'animation pour s'accroupir
	Animation* fall(const pair<int, int>& StartPos); //Construit une chute
	Animation* attackRight(const pair<int,int>& StartPos); //Construit une attaque vers la droite
	Animation* attackLeft(const pair<int,int>& StartPos); //Construit une attaque vers la gauche
};

#endif