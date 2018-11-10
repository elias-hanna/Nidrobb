#ifndef JUMPCOMMAND_HPP
#define JUMPCOMMAND_HPP

#include "Command.hpp"

class JumpCommand : public Command
{
public:
	JumpCommand(int tgt){this->_name ="JumpCommand"; this->_target=tgt;};
	virtual void execute(Player& p) const {p.jump();} //Execute l'action sur un joueur
};

#endif