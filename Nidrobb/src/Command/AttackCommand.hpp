#ifndef ATTACKCOMMAND_HPP
#define ATTACKCOMMAND_HPP

#include "Command.hpp"

class AttackCommand : public Command
{
public:
	AttackCommand(int tgt){this->_name ="AttackCommand"; this->_target=tgt;}
	virtual void execute(Player& p) const {p.attack();} //Execute l'action sur un joueur
	//virtual void execute(Game& g){ Game.quit()= true;};
};

#endif