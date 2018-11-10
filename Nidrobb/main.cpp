//#include "gui/display.hpp"
#include "GameEnv/Game.hpp"

int main(int argc, char *argv[])
{
	Game& game = Game::Instance();

	while(!game.quit())
	{
		if(game.quit()) //Indicateur des bugs qui BRISENT LES COUILLES
			cout<<"WTF"<<endl;
		
		game.run();

		SDL_Delay(1); //Semble calmer les bug wtf
	}
}