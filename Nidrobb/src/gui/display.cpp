#include "display.hpp"

//Single Instance
Display Display::_instance=Display();

//Constructeur qui initialise SDL, le renderer, SDL_image et la fenetre
Display::Display()
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		std::cout << "SDL n'a pas pu etre initialise. Erreur SDL : " << SDL_GetError() << std::endl;
		return;
	}
	else
	{
		//On set le mode de filtrage des texture en lineaire
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
			std::cout << "Attention : le filtrage des textures n'est pas lineaire" << std::endl;

		//Cree une fenetre
		_window = SDL_CreateWindow( "Nidrobb", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( _window == NULL )
		{
			std::cout << "La fenetre n'a pas pu etre cree. Erreur SDL : " << SDL_GetError() << std::endl;
			return;
		}
		else
		{
			//Cree un renderer pour la fenetre
			_renderer = SDL_CreateRenderer( _window, -1, SDL_RENDERER_ACCELERATED );
			if( _renderer == NULL )
			{
				std::cout << "Le renderer n'a pas pu etre cree. Erreur SDL : " << SDL_GetError() << std::endl;
				return;
			}
			else
			{
				//Initialise la couleur du renderer en blanc
				SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialise le chargement d'image png
				int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					std::cout << "SDL_image n'a pas pu etre initialiser. Erreur SDL_image :  " << IMG_GetError() << std::endl;
					return;
				}
			}
		}
	}
}


Display& Display::operator=(const Display& d)
{
	_window = d.getWindow();
	_renderer = d.getRenderer();
	//_playerList = d.getPList();

	return *this;
}

Display::~Display()
{
	//Destroy window	
	SDL_DestroyRenderer( _renderer );
	SDL_DestroyWindow( _window );
	_window = NULL;
	_renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

//Dessine un objet
void Display::draw(Drawable* d) const
{
	SDL_RenderCopy( _renderer, d->sprite().getTexture(), NULL,d->sprite().getRect() );
}