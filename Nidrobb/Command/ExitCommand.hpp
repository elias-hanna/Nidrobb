#ifndef EXITCOMMAND_HPP
#define EXITCOMMAND_HPP

#include "Command.hpp"

class ExitCommand : public Command
{
public:
	ExitCommand(){this->_name ="ExitCommand"; this->_target=0;}
	virtual void execute(Player& p) const {} //Execute l'action sur un joueur
	//virtual void execute(Game& g){ Game.quit()= true;};
};

#endif