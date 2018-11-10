#include "InputMap.hpp"


InputMap::InputMap()
{
	//Default General map
	_GeneralMap[SDLK_ESCAPE]= new ExitCommand();

	//Default Player 1 map
	_P1Map[SDLK_q]= new LeftCommand(1); //Q
	_P1Map[SDLK_d]= new RightCommand(1); //D
	_P1Map[SDLK_s]= new DownCommand(1); //S
	_P1Map[SDLK_SPACE]= new JumpCommand(1); //SpaceBar
	_P1Map[SDLK_g]= new AttackCommand(1); //G

	_P1Map[SDLK_F1] = new FallCommand(1);

	//Default Player 2 map
	_P2Map[SDLK_LEFT]=new LeftCommand(2); //Fleche gauche
	_P2Map[SDLK_RIGHT]= new RightCommand(2); //Fleche droite
	_P2Map[SDLK_DOWN]= new DownCommand(2); //Fleche bas
	_P2Map[SDLK_KP_ENTER] = new JumpCommand(2); //Enter Pav Num
	_P2Map[SDLK_KP_0]= new AttackCommand(2); //0 Pav Num

	_P2Map[SDLK_F2] = new FallCommand(2);
}

InputMap::~InputMap()
{
	for(auto & i : _GeneralMap) //auto = map<>::iterator
	{
		delete i.second;
	}

	for(auto & i : _P1Map) //auto = map<>::iterator
	{
		delete i.second;
	}

	for(auto & i : _P2Map) //auto = map<>::iterator
	{
		delete i.second;
	}
}

//Renvoie la commande associé à l'argument (nullptr si la commande n'existe pas)
Command* InputMap::operator()(int input)
{
	//Recherche GeneralMap
	map<int,Command*>::iterator it = _GeneralMap.find(input);
	if(it != _GeneralMap.end()) //element trouvé
		return _GeneralMap[input];

	//Recherche Player 1 map
	it = _P1Map.find(input);
	if(it != _P1Map.end()) //element trouvé
		return _P1Map[input];

	//Recherche Player 2 map
	it = _P2Map.find(input);
	if(it != _P2Map.end()) //element trouvé
		return _P2Map[input];
	else //Aucune valeur trouvé
		return nullptr;
}

//Relie une commande à une entrée et indique si un ancien mapping a été écrasée
bool InputMap::remap(Command* cmd, int new_input)
{
	bool res = false; //Indique si une ancienne commande a ete ecrasée
	//Suppresion de l'ancien mapping
	int oldKey=0;
	for(auto & i : _GeneralMap) //auto = map<>::iterator
	{
		if(i.second == cmd) //Action déja mappé dans General Map
		{
			//_GeneralMap.erase((map<int,string>::iterator)i);
			oldKey = i.first; //On recupère la clé correspondante
			res = true;
			break;
		}
	}
	_GeneralMap.erase(oldKey); //Suppresion de la clé associé à l'action
	_GeneralMap.erase(new_input); //Suppresion de l'action lié à la nouvelle clé

	for(auto & i : _P1Map) //auto = map<>::iterator
	{
		if(i.second == cmd) //Action déja mappé dans General Map
		{
			//_GeneralMap.erase((map<int,string>::iterator)i);
			oldKey = i.first; //On recupère la clé correspondante
			res = true;
			break;
		}
	}
	_P1Map.erase(oldKey); //Suppresion de la clé associé à l'action
	_P1Map.erase(new_input); //Suppresion de l'action lié à la nouvelle clé

	for(auto & i : _P2Map) //auto = map<>::iterator
	{
		if(i.second == cmd) //Action déja mappé dans General Map
		{
			//_GeneralMap.erase((map<int,string>::iterator)i);
			oldKey = i.first; //On recupère la clé correspondante
			res = true;
			break;
		}
	}
	_P2Map.erase(oldKey); //Suppresion de la clé associé à l'action
	_P2Map.erase(new_input); //Suppresion de l'action lié à la nouvelle clé
	
	//Ajout de la nouvelle entrée
	switch(cmd->target())
	{
		case(0): //Action système
			_GeneralMap[new_input]=cmd;
			break;
		case(1): //Action Joueur 1
			_P1Map[new_input]=cmd;
			break;
		case(2): //Action Joueur 2
			_P2Map[new_input]=cmd;
			break;
	}

	return res;
}

ostream& operator<<(ostream& os,const InputMap& im)
{
	//Verification

	//Operation
	map<int,Command*> map = im.GMap();
	os<< "General" << endl;
	for(auto & i : map) //auto = map<>::iterator
	{
		os<< " " << i.first << " : " << i.second->name() << " " << i.second->target() <<endl;
	}

	map = im.P1Map();
	os<< endl << " P1 Map" << endl;
	for(auto & i : map) //auto = map<>::iterator
	{
		os<< " " << i.first << " : " << i.second->name() << " " << i.second->target() <<endl;
	}

	map = im.P2Map();
	os<< endl << " P2 Map" << endl;
	for(auto & i : map) //auto = map<>::iterator
	{
		os<< " " << i.first << " : " << i.second->name() << " " << i.second->target() <<endl;
	}

	return os;
}
/*
ostream& operator<<(ostream& os,const InputMap& im)
{
	//Verification

	//Operation
	map<int,string> map = im.GMap();
	os<< "General" << endl;
	for(auto & i : map) //auto = map<>::iterator
	{
		os<< " " << i.first << " : " << i.second <<endl;
	}

	map = im.P1Map();
	os<< endl << " P1 Map" << endl;
	for(auto & i : map) //auto = map<>::iterator
	{
		os<< " " << i.first << " : " << i.second <<endl;
	}

	map = im.P2Map();
	os<< endl << " P2 Map" << endl;
	for(auto & i : map) //auto = map<>::iterator
	{
		os<< " " << i.first << " : " << i.second <<endl;
	}

	return os;
}
*/