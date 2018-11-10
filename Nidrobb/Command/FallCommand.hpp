#ifndef FALLCOMMAND_HPP
#define FALLCOMMAND_HPP

#include "Command.hpp"

class FallCommand : public Command
{
public:
	FallCommand(int tgt){this->_name ="FallCommand"; this->_target=tgt;};
	virtual void execute(Player& p) const {p.fall();} //Execute l'action sur un joueur
};

#endif