#ifndef PLAYER_HPP
#define PLAYER_HPP

//#include "../Drawable.hpp" //Inclus dans Animation
//#include "../Collidable.hpp" //Inclus dans Animation
//#include "../Animation/Animation.hpp" //Inclus dans animationbuilder
#include "../Animation/AnimationBuilder.hpp"

//Forward declaration IA
class Game; 

//Repéresente un joueur
class Player: public Drawable, public Collidable
{
protected:
	unsigned int _playerID; //Identifiant du joueur
	static unsigned int nextPlayerID;
	pair<int,int> _pos; //Position du personnage
	Animation* _currAnim;//Animation courante
	AnimationBuilder _builder;//Builder pour les animations
	bool _prevDirection = true; //Indique la dernière direction prise (true = droite, false = gauche) (Peut manquer d'info, à améliorer au besoin)
	bool _ia = false; //Indique si le joueur est controlée par l'ordinateur

public:
	Player(const pair<int,int>& StartPos, SDL_Renderer *renderer);
	virtual ~Player();

	void stand(); //Reste en place
	void stand(const pair<int,int>& pos); //Reste en place à une position donnée
	void moveRight(); //Déplacement vers la droite (si possible)
	void moveLeft(); //Déplacement vers la gauche (si possible)
	void jump(); //Saut (si possible)
	void crouch(); //Accroupis (si possible)
	void fall(); //Chute
	void attack(); //Attaque (si possible)

	void nextAnim() { _pos=_currAnim->nextFrame();} //Defile la frame & récupère la position
	bool collideA(const Player* p) const; //Vérifie si un joueur entre en collision (Hitbox Active vs Active)
	bool collideA(const SDL_Rect* box) const; //Vérifie si une hitbox rentre en collision active
	bool collideP(const SDL_Rect* box) const; //Vérifie si une hitbox rentre en collision passive
	bool hit(const Player* receiver) const; //Verifie si le joueur touche un autre joueur (Hitbox Active vs Passive)
	void holdPos(const pair<int,int>& pos); //Fini une animation à un point donnée (Ref SDL)

	virtual void nextAction(const Game* g){} //IA : Demande au joueur d'effectuer une action

	//Accesseurs
	int id() const { return _playerID;}
	const AnimationFrame* currFrame() const{ return _currAnim->getFrame();}
	Sprite& sprite() { return _currAnim->sprite();}
	const Sprite& sprite() const{ return _currAnim->sprite();}
	const pair<int,int>& pos() const { return _pos;}
	const vector<SDL_Rect*>& aHitBox() const { return _currAnim->getFrame()->aHitBox();}
	const vector<SDL_Rect*>& pHitBox() const { return _currAnim->getFrame()->pHitBox();}
	const bool isComputer() const { return _ia;}
	
	/*
	SDL_Texture *getTexture() const { return _currAnim.getTexture();}//On recupere la texture de l'objet dessinable
	SDL_Rect *getRect() const { return _currAnim.getTexture();}//On recupere la zone ou dessiner l'objet dessinable
	*/

	//void checkAnim(const vector<SDL_Rect*> obstacles); //On verifie/modifie l'animation pour gerer les collisions
};

#endif