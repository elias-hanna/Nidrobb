#ifndef INPUTMAP_HPP
#define INPUTMAP_HPP

#include <map>
#include <iostream>
#include "Command.hpp"
#include "NullCommand.hpp"
#include "ExitCommand.hpp"
#include "RightCommand.hpp"
#include "LeftCommand.hpp"
#include "JumpCommand.hpp"
#include "DownCommand.hpp"
#include "FallCommand.hpp"
#include "AttackCommand.hpp"

using namespace std;

//Représente une map des entrée utilisateurs
class InputMap
{
protected:
	//https://wiki.libsdl.org/SDL_Keycode
	map<int,Command*> _GeneralMap; //Map des commandes système
	map<int,Command*> _P1Map; //Map des commandes joueur 1
	map<int,Command*> _P2Map; //Map des commandes joueur 2

public:
	InputMap();
	~InputMap();
	Command* operator()(int input); //Renvoie la commande associé à l'argument
	//Command* operator()(SDL_Keycode input);
	bool remap(Command* action, int new_input); //Relie une commande à une entrée et indique si un ancien mapping a été écrasée

	//Accesseurs
	const map<int,Command*>& GMap() const { return _GeneralMap;};
	const map<int,Command*>& P1Map() const { return _P1Map;};
	const map<int,Command*>& P2Map() const { return _P2Map;};
};


//Operateur << std
ostream& operator<<(ostream& os,const InputMap& im);

#endif