#ifndef LEFTCOMMAND_HPP
#define LEFTCOMMAND_HPP

#include "Command.hpp"

class LeftCommand : public Command
{
public:
	LeftCommand(int tgt){this->_name ="LeftCommand"; this->_target=tgt;};
	virtual void execute(Player& p) const {p.moveLeft();} //Execute l'action sur un joueur
};

#endif