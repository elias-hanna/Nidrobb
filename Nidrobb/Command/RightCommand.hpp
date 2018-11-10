#ifndef RIGHTCOMMAND_HPP
#define RIGHTCOMMAND_HPP

#include "Command.hpp"

class RightCommand : public Command
{
public:
	RightCommand(int tgt){this->_name ="RightCommand"; this->_target=tgt;}
	virtual void execute(Player& p) const {p.moveRight();} //Execute l'action sur un joueur
};

#endif