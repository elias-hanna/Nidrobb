#include "Player.hpp"

unsigned int Player::nextPlayerID = 1;

Player::Player(const pair<int,int>& StartPos, SDL_Renderer *renderer): _builder(renderer)
{
	_playerID = nextPlayerID++;
	_pos = StartPos;
	_currAnim = _builder.stand(_pos);
}

Player::~Player()
{
	delete _currAnim;
}

//Reste en place
void Player::stand()
{
	delete _currAnim;
	_currAnim = _builder.stand(_pos);
}

//Reste en place à une position donnée
void Player::stand(const pair<int,int>& pos)
{
	delete _currAnim;
	_currAnim = _builder.stand(pos);
	_pos = pos;
}

//Déplacement vers la droite (si possible)
void Player::moveRight()
{
	if(!_currAnim->inProgress()) //Animation précédente terminée
	{
		delete _currAnim;
		_currAnim = _builder.moveRight(_pos);
		_prevDirection = true; //mvt droite
	}
	else if(_currAnim->name()=="Jump"&&_currAnim->progress()==0)
	{
		delete _currAnim;
		_currAnim = _builder.rightJump(_pos);
		_prevDirection = true; //mvt droite
	}
}

//Déplacement vers la gauche (si possible)
void Player::moveLeft()
{
	if(!_currAnim->inProgress()) //Animation précédente terminée
	{
		delete _currAnim;
		_currAnim = _builder.moveLeft(_pos);
		_prevDirection = false; //mvt gauche
	}
	else if(_currAnim->name()=="Jump"&&_currAnim->progress()==0)
	{
		delete _currAnim;
		_currAnim = _builder.leftJump(_pos);
		_prevDirection = false; //mvt gauche
	}
}

//Saut (si possible)
void Player::jump()
{
	if(!_currAnim->inProgress()) //Animation précédente terminée
	{
		delete _currAnim;
		_currAnim = _builder.jump(_pos);
	}
	else if(_currAnim->name()=="Right Move")
	{
		delete _currAnim;
		_currAnim = _builder.rightJump(_pos);
	}
	else if(_currAnim->name()=="Left Move")
	{
		delete _currAnim;
		_currAnim = _builder.leftJump(_pos);
	}
}

//Accroupis (si possible)
void Player::crouch()
{
	if(!_currAnim->inProgress()) //Animation précédente terminée
	{
		delete _currAnim;
		_currAnim = _builder.crouch(_pos);
	}
}

//Chute
//Ne devrait pas pouvoir etre évité : Gestion de la chute à affiner
void Player::fall()
{
	//N'agit pas si une animation de saut est en cours (Amelioration: ajouter attribut interompable dans animation)
	//if( !(_currAnim->inProgress() && ( _currAnim->name()=="Jump" || _currAnim->name()=="Right Jump" || _currAnim->name()=="Left Jump")))
	if(!_currAnim->inProgress()) //Animation précédente terminée
	{
		delete _currAnim;
		_currAnim = _builder.fall(_pos);//, EndPos);
	}
}

//Attaque (si possible)
void Player::attack()
{
	if(!_currAnim->inProgress())
	{
		delete _currAnim;
		if(_prevDirection)//Précédente action vers la droite
		{
			_currAnim = _builder.attackRight(_pos);
		}
		else//Précédente action vers la gauche
		{
			_currAnim = _builder.attackLeft(_pos);
		}
	}
}

//Vérifie si un joueur entre en collision (Hitbox Active vs Active)
bool Player::collideA(const Player* p) const
{
	for(SDL_Rect* box : p->aHitBox())
	{
		if(collideA(box)) //Les deux joueurs entre en collisions (active)
			return true;
	}
	return false;
}

//Vérifie si une hitbox rentre en collision active
bool Player::collideA(const SDL_Rect* box) const
{
	if(_currAnim->collideA(box))
		return true;
	else
		return false;
}

//Vérifie si une hitbox rentre en collision passive
bool Player::collideP(const SDL_Rect* box) const
{
	if(_currAnim->collideP(box))
		return true;
	else
		return false;
}

//Verifie si le joueur touche un autre joueur (Hitbox Active vs Passive)
bool Player::hit(const Player* receiver) const
{
	for(SDL_Rect* attack : aHitBox()) //On parcours toute les hitbox actives de l'attaquant
	{
		if(receiver->collideP(attack)) //Si l'attaquant est touché (ie Attaquant touche les hitbox passive du receveur)
		{
			return true;
		}
	}
	return false;
}

//Fini une animation à un point donnée (Ref SDL)
void Player::holdPos(const pair<int,int>& pos)
{
	_currAnim->holdPos(pos);
}

/*
void Player::checkAnim(const vector<SDL_Rect*> obstacles)
{
	bool validAnim = true;
	vector<SDL_Rect*> collisions;

	for (int i = 0; i < 100; i++) //Limite à 100 essais
	{
		//Recherche de tout les obstacles en collision (si aucune collision, on sort)
		for(SDL_Rect* o : obstacles)
		{
			if(_currAnim)
		}

		if(validAnim)
			break;
		//Création d'une animation valide (à priori)
	}

	if(!validAnim)//Aucune solution trouvée
	{
		cout<<"CheckAnim : Pas de solution trouvée"<<endl;
	}
}
*/