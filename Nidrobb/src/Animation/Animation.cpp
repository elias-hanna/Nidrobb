#include "Animation.hpp"

Animation::Animation(const string& name, const vector<AnimationFrame*> frames):_name(name)//, _frames(frames)
{
	//VERIFIER BONNE TRANSMISSION DES FRAMES
	for(AnimationFrame* frame : frames)
	{
		//cout<<"	anim: "<<frame->center().first<<"/"<<frame->center().second<<endl;
		_frames.push_back(frame);
	}
	_duration = _frames.size(); //-1 ?
	_progress = 0;
}

Animation::~Animation()
{
	for(AnimationFrame* a : _frames)
		delete a;
}

//Indique si l'animation est en cours
bool Animation::inProgress() const
{
	if (_progress<_duration-1) //Animation en cours
		return true;
	else //Animation terminée
		return false;
}

//Défile l'animation et retourne la position de la frame active
const pair<int,int>& Animation::nextFrame()
{
	unsigned int res;
	//cout<<"Progress : "<< _progress << "/"<<_duration <<endl;
	res=_progress; //indice de la frame renvoyée

	if(_progress<_duration-1)
	{
		_progress++; //Prochain indice
	}
	else 
	{
		//cout<<"Warning : using finished animation (using Frame "<< res+1 <<" / "<<_frames.size()<<")"<<endl;
	}
	//cout<<"Frame Pos : "<<_frames[res]->center().first<<"/"<<_frames[res]->center().second<<endl;
	return _frames[res]->center();
}

//Vérifie si une hitbox rentre en collision active avec la frame active
bool Animation::collideA(const SDL_Rect* box) const
{
	if(_frames[_progress]->collideA(box))
		return true;
	else
		return false;
}

//Vérifie si une hitbox rentre en collision passive avec la frame active
bool Animation::collideP(const SDL_Rect* box) const
{
	if(_frames[_progress]->collideP(box))
		return true;
	else
		return false;
}

//Bloque toute les frames à une position donnée (repère SDL)
void Animation::holdPos(const pair<int,int>& pos)
{
	for(AnimationFrame* a : _frames)
	{
		a->translate(pos);
	}
}

Animation& Animation::operator=(const Animation& a)
{
	_name = a.name();
	_duration=a.duration();
	_progress=a.progress()-1; //On recupère l'indice 
	
	_frames.clear(); //Si pas supprimé, garde le précédent vecteur et rajoute a la fin ...
	AnimationFrame* animFrame;


	for(unsigned int i=0; i<_duration; i++)
	{
		//std::cout<<"Framecopy "<<i<<"/"<<a.duration()<<std::endl;

		//cout<<"operator = : "<<i<<" - "<<a.getFrame(i)->center().first<<"/"<<a.getFrame(i)->center().second<<endl;
		animFrame = new AnimationFrame(*a.getFrame(i));
		_frames.push_back(animFrame);
	}

	// for(AnimationFrame* f : _frames)
	// 	cout<<"operator = fin : "<<" - "<<f->center().first<<"/"<<f->center().second<<endl;
		//std::cout<<"Framecopyf"<<std::endl;

	return *this;
}