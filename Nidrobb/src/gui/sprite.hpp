#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
#include <iostream>

SDL_Rect *createRect(int x, int y, int w, int h); //Forward Declaration (Game) 

class Sprite
{
	private:
		SDL_Rect *_rect = nullptr; //Rectangle du sprite
		SDL_Texture *_texture = nullptr; //Texture du sprite (Stocké dans les usines)
	public:
		Sprite();
		//Sprite(SDL_Renderer *renderer, SDL_Rect *rect); //Fuite mémoire avec les textures
		//Sprite(SDL_Renderer *renderer, SDL_Rect *rect, std::string imgPath); //Fuite mémoire avec les textures
		Sprite(SDL_Rect *rect, SDL_Texture *texture);
		Sprite(Sprite& s);
		~Sprite();

		//Accesseurs
		SDL_Texture *getTexture() const { return _texture;} //SDL_Texture ne peut pas etre const
		SDL_Rect *getRect() const { return _rect;}

		Sprite& operator=(const Sprite& s);
		bool operator==(const Sprite& s) const;
};

#endif