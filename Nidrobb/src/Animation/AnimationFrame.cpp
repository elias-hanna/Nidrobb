#include "AnimationFrame.hpp"

AnimationFrame::AnimationFrame(const Sprite& s, const vector<SDL_Rect*>& pHitBox, const vector<SDL_Rect*>& aHitBox, const pair<int,int>& center)
{
	_sprite=s; //Attention opérateur par copie !
	_center = center;

	//Copie des hitbox
	SDL_Rect* nr = nullptr;
	for(SDL_Rect* r : pHitBox)
	{
		nr = createRect(r->x, r->y, r->w, r->h);
		_passiveHitbox.push_back(nr);
	}
	for(SDL_Rect* r : aHitBox)
	{
		nr = createRect(r->x, r->y, r->w, r->h);
		_activeHitbox.push_back(nr);
	}
}

AnimationFrame::~AnimationFrame()
{
	
	//cout<<"Delete AnimF"<<endl;

	for(SDL_Rect* p : _passiveHitbox)
		delete p;
	for(SDL_Rect* a : _activeHitbox)
		delete a;

	// _passiveHitbox.clear();
	// _activeHitbox.clear();

}

///Vérifie si une hitbox rentre en collision active
bool AnimationFrame::collideA(const SDL_Rect* box) const
{
	for(SDL_Rect* b : _activeHitbox)
	{
		if(SDL_HasIntersection(box,b) == SDL_TRUE) //Collision avec une hitbox
		{
			//cout<<"Collision !"<<endl;
			return true;
		}
	}
	return false;
}

//Vérifie si une hitbox rentre en collision passive
bool AnimationFrame::collideP(const SDL_Rect* box) const
{
	//cout<<"AnimationFrame : Collision test"<<endl;
	for(SDL_Rect* b : _passiveHitbox)
	{
		// if(SDL_IntersectRect(box,b,nullptr) == SDL_TRUE) //Collision avec une hitbox
		// {
		// 	cout<<"Collision !"<<endl;
		// 	return true;
		// }
		if(SDL_HasIntersection(box,b) == SDL_TRUE) //Collision avec une hitbox
		{
			//cout<<"Collision !"<<endl;
			return true;
		}
		// if(checkCollision(box,b))
		// {
		// 	// cout<<"Collision !"<<endl;
		// 	// cout<<"B1 : "<<box->x<<"/"<<box->y<<" - "<<box->w<<"/"<<box->h<<endl;
		// 	// cout<<"B2 : "<<b->x<<"/"<<b->y<<" - "<<b->w<<"/"<<b->h<<endl; 
		// 	return true;
		// }
	}
	return false;
}

//Deplace la frame à un centre donner (repère SDL)
void AnimationFrame::translate(const pair<int,int>& pos)
{
	//Caclul du vecteur de translation
	pair<int,int> transform;
	transform.first = pos.first - _center.first;
	transform.second = pos.second - _center.second;

	//Application de la translation
	_center = pos;

	for(SDL_Rect* r : _passiveHitbox)
	{
		r->x+=transform.first;
		r->y+=transform.second;
	}
	for(SDL_Rect* r : _activeHitbox)
	{
		r->x+=transform.first;
		r->y+=transform.second;
	}
}

AnimationFrame& AnimationFrame::operator=(const AnimationFrame& a)
{
	_sprite = a.sprite(); //Attention opérateur =
	_center = a.center();

	//Copie des hitbox (ATTENTION delete)
	SDL_Rect* nr = nullptr;
	vector<SDL_Rect*> v = a.pHitBox();
	for(SDL_Rect* r : v)
	{
		nr = createRect(r->x, r->y, r->w, r->h);
		_passiveHitbox.push_back(nr);
	}
	v=a.aHitBox();
	for(SDL_Rect* r : v)
	{
		nr = createRect(r->x, r->y, r->w, r->h);
		_activeHitbox.push_back(nr);
	}

	return *this;
}

bool AnimationFrame::operator==(const AnimationFrame& a) const
{
	bool res = true;
	if(_center==a.center() && _sprite==a.sprite() && _passiveHitbox.size()==a.pHitBox().size() && _activeHitbox.size()==a.aHitBox().size())
	{
		for(unsigned int i=0;i<_passiveHitbox.size();i++)
		{
			if(SDL_RectEquals(_passiveHitbox[i],a.pHitBox()[i])==SDL_FALSE)
			{
				res = false;
				break;
			}
		}
		if(res) //Si c'est toujours bon
		{
			for(unsigned int i=0;i<_passiveHitbox.size();i++)
			{
				if(SDL_RectEquals(_activeHitbox[i],a.aHitBox()[i]) == SDL_FALSE)
				{
					res = false;
					break;
				}
			}
		}
	}
	return res;
}