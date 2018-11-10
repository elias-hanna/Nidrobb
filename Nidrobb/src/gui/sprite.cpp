#include "sprite.hpp"

Sprite::Sprite(){}
//Fuite memoire avec les textures
// Sprite::Sprite(SDL_Renderer *renderer, SDL_Rect *rect)
// {
// 	//association du rectangle passe en arg a la zone ou applique la texture du sprite
// 	_rect = rect;
// 	//Chargement d'une texture par defaut (objet noir)
// 	SDL_Surface *tmpSurface = IMG_Load("images/black.png");
// 	//Verification de la non presence d'erreur lors du chargement
// 	if(!tmpSurface)
// 		std::cout << "Surface non chargee a partir de black.png. Erreur :" << SDL_GetError() << std::endl;
// 	//Creation de la texture du sprite a partir de la surface chargee
// 	_texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
// 	//Liberation de la memoire allouee pour la surface
// 	SDL_FreeSurface(tmpSurface);
// }

//Fuite memoire avec les textures
// Sprite::Sprite(SDL_Renderer *renderer, SDL_Rect *rect, std::string imgPath)
// {
// 	//association du rectangle passe en arg a la zone ou applique la texture du sprite
// 	_rect = rect;
// 	//Chargement d'une texture a partir du chemin d'une image passe en arg
// 	SDL_Surface *tmpSurface = IMG_Load(imgPath.c_str());
// 	//Verification de la non presence d'erreur lors du chargement
// 	if(!tmpSurface)
// 		std::cout << "Surface non chargee a partir de " << imgPath << " Erreur :" << SDL_GetError() << std::endl;
// 	//Creation de la texture du sprite a partir de la surface chargee
// 	_texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
// 	//Liberation de la memoire allouee pour la surface
// 	SDL_FreeSurface(tmpSurface);
// }

Sprite::Sprite(SDL_Rect *rect, SDL_Texture *texture)
{
	//association du rectangle passe en arg a la zone ou applique la texture du sprite
	_rect = rect;
	//association de la texture passee en arg au sprite
	_texture = texture;
}

Sprite::Sprite(Sprite& s)
{
	*this = s;
}

Sprite::~Sprite()
{
	//std::cout<<"Destructeur sprite"<<std::endl;
	//Genere des erreurs de double free(), des problemes d'affichage... je laisse la main a SDL 
	if(_rect !=nullptr)
		delete _rect; //Attention parfois supprimé plusieurs fois
	// SDL_DestroyTexture(_texture); //Stocké/Détruite hors de sprite
}

Sprite& Sprite::operator=(const Sprite& s)
{
	const SDL_Rect* r = s.getRect();
	_rect = createRect(r->x, r->y, r->w, r->h);

	//ATTENTION suppose ques les textures sont supprimés en fin de pogramme seulement
	_texture = s.getTexture();

	return *this;
}

bool Sprite::operator==(const Sprite& s) const
{
	if(this->getTexture()==s.getTexture() && SDL_RectEquals(this->getRect(),s.getRect())==SDL_TRUE)
		return true;
	else
		return false;
}