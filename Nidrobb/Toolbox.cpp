#include "Toolbox.hpp"

//Retourne le centre géométrique d'un objet à partir 
//Pair<int,int> centerSDLtoObject()

SDL_Rect *createRect(int x, int y, int w, int h)
{
	//Attention il faut desallouer le SDL_Rect en dehors de la fonction
	SDL_Rect *r = new SDL_Rect;
	r->x = x;
	r->y = y;
	r->w = w;
	r->h = h;
	return r;
}

std::ostream& operator<<(std::ostream& os, const SDL_Rect& r)
{
	os<<r.x<<"/"<<r.y<<" - "<<r.w<<"/"<<r.h;
	return os;
}

// bool checkCollision(const SDL_Rect* a, const SDL_Rect* b )
// {
// 	  //The sides of the rectangles
//     int leftA, leftB;
//     int rightA, rightB;
//     int topA, topB;
//     int bottomA, bottomB;

//     //Calculate the sides of rect A
//     leftA = a->x;
//     rightA = a->x + a->w;
//     topA = a->y;
//     bottomA = a->y + a->h;

//     //Calculate the sides of rect B
//     leftB = b->x;
//     rightB = b->x + b->w;
//     topB = b->y;
//     bottomB = b->y + b->h;

//     //If any of the sides from A are outside of B
//     if( bottomA <= topB )
//     {
//         return false;
//     }

//     if( topA >= bottomB )
//     {
//         return false;
//     }

//     if( rightA <= leftB )
//     {
//         return false;
//     }

//     if( leftA >= rightB )
//     {
//         return false;
//     }

//     //If none of the sides from A are outside B
//     return true;
// }