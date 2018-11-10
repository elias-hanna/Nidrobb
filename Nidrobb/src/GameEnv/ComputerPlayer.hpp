#ifndef COMPUTERPLAYER_HPP
#define COMPUTERPLAYER_HPP

#include "../GameEnv/Player.hpp"

class Game; //Forward trop limité pour le traitement de l'IA

//Classe parente de toute les IA
class ComputerPlayer : public Player
{
public:
	ComputerPlayer(const pair<int,int>& StartPos, SDL_Renderer *renderer): Player(StartPos, renderer){_ia = true;}
	//virtual ~ComputerPlayer(){}
	
	virtual void nextAction(const Game* g){ this->jump();} //A surcharger pour le traitement
};

#endif