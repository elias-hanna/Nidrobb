#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../Animation/AnimationFrame.hpp"
//#include "../Drawable.hpp" //Inclus dans AnimationFrame
//#include "../Collidable.hpp" //Inclus dans AnimationFrame

using namespace std;

//Repéresente une animation
class Animation : public Drawable, public Collidable
{
protected:
	string _name; //Nome de l'animation
	vector<AnimationFrame*> _frames; //Frames de l'animation
	unsigned int _duration, _progress; //Durée/Progrès de l'animation (en Frame)
public:
	//Animation():_name("Null"), _duration(0), _progress(0){};
	Animation(const string& name, const vector<AnimationFrame*> frames);
	Animation(const Animation& a){ *this = a;}
	~Animation();

	bool inProgress() const; //Indique si l'animation est en cours
	const pair<int,int>& nextFrame(); //Défile l'animation et retourne la position de la frame active
	bool collideA(const SDL_Rect* box) const; //Vérifie si une hitbox rentre en collision active avec la frame active
	bool collideP(const SDL_Rect* box) const; //Vérifie si une hitbox rentre en collision passive avec la frame active
	void holdPos(const pair<int,int>& pos); //Bloque toute les frames à une position donnée (repère SDL)

	//Accesseurs
	const string& name() const{ return _name;}
	AnimationFrame* getFrame() const{ return _frames[_progress];}
	AnimationFrame* getFrame(unsigned int i) const{ if(i<_duration) return _frames[i]; else return nullptr;}
	Sprite& sprite() { return _frames[_progress]->sprite();};
	const Sprite& sprite() const{ return _frames[_progress]->sprite();}
	unsigned int duration() const{ return _duration;}
	unsigned int progress() const{ return _progress+1;} //Numéro de la frame (indice+1)
	/*
	SDL_Texture *getTexture() const {return _frames[_progress]->getTexture();}//On recupere la texture de l'objet dessinable
	SDL_Rect *getRect() const { return _frames[_progress]->getRect();}//On recupere la zone ou dessiner l'objet dessinable
	*/

	Animation& operator=(const Animation& a);
};

#endif