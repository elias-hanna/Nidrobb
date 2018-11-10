#ifndef DISPLAY_HPP
#define DISPLAY_HPP

#include "../GameParam.hpp"
/*
#include <vector>
#include <iostream>

#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
*/
#include "../GameEnv/Player.hpp"
//#include "sprite.hpp"

//class Player; //Forward Delcaration (Fonctionne pas avec vector, veut type complet)
SDL_Rect *createRect(int x, int y, int w, int h); //Forward Declaration (Game)

//Représente l'écran d'affichage
class Display
{
	private:
		SDL_Window *_window; //Fenètre d'affichage
		SDL_Renderer *_renderer; //Outil de rendu

		//Singleton
		static Display _instance;

		Display();
		~Display();
		Display& operator=(const Display& d);
	public:		
		void draw(Drawable* d) const; //Dessine un objet
		//void renderSprites();

		//Singleton
		static Display& Instance() { return _instance;}

		//Accesseurs
		SDL_Window* getWindow() const { return _window;}
		SDL_Renderer* getRenderer() const { return _renderer;}
};

#endif