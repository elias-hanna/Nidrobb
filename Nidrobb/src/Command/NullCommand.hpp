#ifndef NULLCOMMAND_HPP
#define NULLCOMMAND_HPP

#include "Command.hpp"

class NullCommand : public Command
{
public:
	NullCommand(){this->_name ="NullCommand"; this->_target=-1;}
	NullCommand(string name){this->_name =name; this->_target=0;} //Commande système en attendant de mieux
	virtual void execute(Player& p) const {} //Execute l'action sur un joueur
	//virtual void execute(Game& g){};
};

#endif