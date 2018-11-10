#ifndef GAME_HPP
#define GAME_HPP

#include <set>

#include "../gui/display.hpp"
#include "../Command/InputMap.hpp"
//#include "../GameEnv/Obstacle.hpp"
//#include "../GameEnv/World.hpp"
#include "../GameEnv/WorldBuilder.hpp"
#include "../GameEnv/ComputerPlayer.hpp" //Pour l'IA
#include "../Toolbox.hpp"

#include "../GameParam.hpp"

class Game
{
private:
	Display& _disp = Display::Instance(); //Affichage
	//vector<Obstacle*> _obsList;
	World* _world; //Monde
	WorldBuilder _builder; //Usine à monde (on pourrait l'externaliser en singleton)
	vector<Player*> _playerList; //Liste des joueurs
	set<int> _currInputs; //Touche appuyés (SDL_Keycode ! bug ?) (On preferait SDL_Keysym pour avoir les modifiers) (https://wiki.libsdl.org/SDL_Keysym)
	InputMap _inputMap; //Map des entrée utilisateurs
	bool _quit = false, _menu = false;

	unsigned int _currTime,_loopTime; //millisecondes
	//Event handler
	SDL_Event _event;

	//Singleton
	static Game _instance;
    Game();
	~Game();
	Game& operator=(const Game& g);
public:

	void run(); //Effectue un tour de jeu
	void draw(); //Affiche le jeu 
	void executeInput(int input); //Execute l'action correspondant à l'argument (si contenu dans l'inputMap)
	void executeInput(const set<int>& inputs); //Execute un ensemble d'action

	void checkCollisions(Player * p); //Verifie la validité de l'action d'un joueur (Hitbox Passive vs Passive & Active vs Active)
	void checkHits(Player * attacker); //Verifie si un attaquant touche un autre joueur (Hitbox Active vs Passive)
	void resolveCollision(Player * p, Obstacle* o); //Résoud un cas de collision joueur/obstacle (grossièrement)
	void resolveCollision(Player * p1, Player* p2); //Résoud un cas de collision joueur/joueur (Knockback des deux joueurs)
	bool isFalling(Player *p, std::vector<Obstacle*> obsList); //Vérifie si un joueur chute
	bool isFallingV2(const Player *p, const vector<Obstacle*> obsList); //Vérifie si un joueur chute
	void reset(); //Remet à zéro la partie
	void reset(unsigned int playerID); //Replace un joueur à son spawn

	//Singleton
	static Game& Instance(){ return _instance;} //Accès à l'instance du jeu

	//Accesseurs
	std::vector<Player*> PList() const { return _playerList;}
	bool quit() const { return _quit;}
	bool& quit(){ return _quit;}

};

#endif