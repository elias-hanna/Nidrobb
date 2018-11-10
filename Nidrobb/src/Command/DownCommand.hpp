#ifndef DOWNCOMMAND_HPP
#define DOWNCOMMAND_HPP

#include "Command.hpp"

class DownCommand : public Command
{
public:
	DownCommand(int tgt){this->_name ="DownCommand"; this->_target=tgt;}
	virtual void execute(Player& p) const {p.crouch();} //Execute l'action sur un joueur
	//virtual void execute(Game& g){ Game.quit()= true;};
};

#endif