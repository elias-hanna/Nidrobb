#ifndef ANIMATIONFRAME_HPP
#define ANIMATIONFRAME_HPP

#include <vector>
//#include "../gui/sprite.hpp"
#include "../Drawable.hpp"//Inclus sprite
#include "../Collidable.hpp"

using namespace std;

//bool checkCollision( const SDL_Rect* a, const SDL_Rect* b ); //Forward declaration (Game)

//Représente une frame d'animation
class AnimationFrame : public Drawable, public Collidable
{
protected:
	Sprite _sprite; //Sprite (pourrait être préférable par pointeur)

	vector<SDL_Rect*> _passiveHitbox; //Liste des hitbox passive (Reception de dommages)
    vector<SDL_Rect*> _activeHitbox; //Liste des hitbox active (Envoie de dommages)

    //Amelioration : rendre relatif au centre les autre attributs
    pair<int,int> _center; //Centre du personnage (repère SDL)

public:
	//AnimationFrame(){};
	AnimationFrame(const Sprite& s, const vector<SDL_Rect*>& pHitBox, const vector<SDL_Rect*>& aHitBox, const pair<int,int>& center);
	AnimationFrame(const AnimationFrame& a){ *this = a;}
	~AnimationFrame();
	bool collideA(const SDL_Rect* box) const; //Vérifie si une hitbox rentre en collision active
	bool collideP(const SDL_Rect* box) const; //Vérifie si une hitbox rentre en collision passive
	void translate(const pair<int,int>& pos); //Deplace la frame à un centre donner (repère SDL)

	//Accesseurs
	void addPHitbox(SDL_Rect* p){_passiveHitbox.push_back(p);}
	void addAHitbox(SDL_Rect* a){_activeHitbox.push_back(a);}
	Sprite& sprite() { return _sprite;}
	const Sprite& sprite() const{ return _sprite;}
	pair<int,int>& center() { return _center;}
	const pair<int,int>& center() const{ return _center;}
	const vector<SDL_Rect*>& pHitBox() const { return _passiveHitbox;}
	const vector<SDL_Rect*>& aHitBox() const {return _activeHitbox;}

	//Opérateurs
	AnimationFrame& operator=(const AnimationFrame& a);
	bool operator==(const AnimationFrame& a) const;
};

#endif