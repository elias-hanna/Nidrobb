#include "Game.hpp"

//Single Instance
Game Game::_instance=Game();

//Constructeur singleton
Game::Game() : _builder(_disp.getRenderer())
{
	//Environement
	_world = _builder.sky();
	//_world = _builder.collisionTest();

	//Joueur
	pair<int,int> start_pos_P1 = make_pair (P1_START_POSX,P1_START_POSY);
	Player* p1 = new Player(start_pos_P1,_disp.getRenderer());
	_playerList.push_back(p1);

	pair<int,int> start_pos_P2 = make_pair (P2_START_POSX,P2_START_POSY);
	Player* p2 = new Player(start_pos_P2,_disp.getRenderer()); //Joueurs
	//Player* p2 = new ComputerPlayer(start_pos_P2,_disp.getRenderer()); //IA
	_playerList.push_back(p2);

	//Print infos
	cout << "World : "<<_world->name()<<endl;
	for(Player* p : _playerList)
	{
		cout<<"Player "<<p->id()<<" ready !"<<endl;
	}
}

//Destructeur singleton
Game::~Game()
{
	for(Player* p : _playerList)
		delete p;

	delete _world;
}

//Effectue un tour de jeu
void Game::run()
{
	//_quit = true;
	//cout<<"-------------------"<<endl;
	_loopTime = SDL_GetTicks() + MIN_LOOP_TIME; //Temps fin de boucle prévu

	//Handle events on queue
	while( SDL_PollEvent( &_event ) != 0 )
	{
		switch( _event.type )
		{
			case SDL_QUIT: //User requests quit
				_quit = true;
				break;

			case SDL_KEYDOWN:
				//cout<<"Key down : "<< _event.key.keysym.sym<<endl;
				_currInputs.insert(_event.key.keysym.sym);
				break;

			case SDL_KEYUP:
				//cout<<"Key up : "<< _event.key.keysym.sym<<endl;
				_currInputs.erase(_event.key.keysym.sym);
				break;

			default :
				break;
		}
	}
	if(_menu)
	{

	}
	else //Next Game turn
	{

		//cout<<"Execute input"<<endl;
		//Execute action
		executeInput(_currInputs);
		//executeInput(100); //P1 Droite 
		//executeInput(27); //Echap

		for(Player* p : _playerList)
		{
			p->nextAnim(); //ATTENTION : on saute la pemière frame de chaque animation !
			checkCollisions(p); //On s'assure que les actions des joueurs sont valide
			checkHits(p); //Handle hits
		}
	
	}
	//cout<<"Render"<<endl;
	//Clear screen
	SDL_RenderClear( _disp.getRenderer() );
	//cout<<"draw"<<endl;
	//Render texture to screen
	draw();

	_currTime = SDL_GetTicks(); //Temps fin de boucle
	//cout<<"Time : "<<_currTime<<endl;
	//cout<<"loopTime : "<< _loopTime<<endl;
	if(_loopTime > _currTime)
	{
		//cout<<"wait : "<< _loopTime-_currTime<<endl;
		SDL_Delay(_loopTime - _currTime);
	}
}

//Affiche le jeu 
void Game::draw()
{
	//cout<<"draw W"<<endl;
	_disp.draw(_world);

	//cout<<"draw O"<<endl;
	for(Obstacle* o : _world->obstacles())
	{
		_disp.draw(o);
	}
	//cout<<"draw P"<<endl;
	for(Player* p : _playerList)
	{
		_disp.draw(p);
	}
	//cout<<"draw F"<<endl;

	//cout<<"Valgrind err"<<endl;
	//Update screen
	SDL_RenderPresent( _disp.getRenderer() ); //Source d'erreur valgrind (?)
	//cout<<"Valgrind no err"<<endl;
}

//Execute l'action correspondant à l'argument (si contenu dans l'inputMap)
void Game::executeInput(SDL_Keycode input)
{
	Command* cmd = _inputMap(input);
	if(cmd !=nullptr) //Commande valide
	{
		if(cmd->target()==0) //Commande système
		{
			//cout<<"Commande système : "<<cmd->name()<<endl;
			if(cmd->name()=="ExitCommand")
				_quit = true;
		}
		if(cmd->target()>0 && !_menu) //Commande joueur (Hors menu)
		{
			//cout<<"Commande joueur "<<cmd->target()<<" : "<<cmd->name()<<endl;
			for(Player* p : _playerList)
			{
				if(cmd->target()==p->id())
					cmd->execute(*p);
			}
		}
	}
	else
	{
		cout<<"Game Warning : Invalid Input"<<endl;
	}
}

//Execute un ensemble d'action
void Game::executeInput(const set<int>& inputs)
{
	// if(inputs.empty())//Aucune touche appuyée
	// {

	// }
	//Gestion commande joueurs
	for(int i : inputs)
	{
		//cout<<"Execute : "<<i<<endl;
		executeInput(i);
	}
	
	//Gestion commande ordinateur
	for(Player* p : _playerList)
	{
		if(p->isComputer())
		{
			p->nextAction(this);
		}
	}
}

//Verifie la validité de l'action d'un joueur (Hitbox Passive vs Passive & Active vs Active)
void Game::checkCollisions(Player * p)
{

	bool falling = isFallingV2(p, _world->obstacles()); //On demande s'il y a chute
	
	//Handle Active Collision
	for(Player* op : _playerList)
	{
		if(p->id()!=op->id() && p->collideA(op)) //Pas de collision avec soit même
		{
			cout<<"Active collision !"<<endl;
			resolveCollision(p,op); //Handle collision
		}
	}

	//Handle Passive Collision
	for(Obstacle* o : _world->obstacles())
	{
		//cout<<"B :"<<*o->box()<<endl;
		if(p->collideP(o->box()))
		{
			//collided = true;

			// cout<<"Player "<<p->id()<<" : Obstacle Collision"<<endl;
			//Handle Collision
			resolveCollision(p,o);
		}
		// cout << falling << " | " << collided << endl;
		// cout << endl;
	}
	//cout << endl;
	
	//Handle fall
	if(falling)
	{
		//cout << "je tombe" <<  endl;
		if(p->id() == 1)
		{
			// _currInputs.erase(SDLK_q);
			// _currInputs.erase(SDLK_d);
			// _currInputs.erase(SDLK_SPACE);
			_currInputs.insert(SDLK_F1);
		}
		if(p->id() == 2)
		{
			// _currInputs.erase(SDLK_LEFT);
			// _currInputs.erase(SDLK_RIGHT);
			// _currInputs.erase(SDLK_KP_ENTER);
			_currInputs.insert(SDLK_F2);
		}
	}
	else
	{
		//cout << "je tombe pas" <<  endl;
		if(p->id() == 1)
			_currInputs.erase(SDLK_F1);
		if(p->id() == 2)
			_currInputs.erase(SDLK_F2);
	}
}

//Verifie si un attaquant touche un autre joueur (Hitbox Active vs Passive)
void Game::checkHits(Player * attacker)
{
	for(Player* receiver : _playerList)
	{
		if(attacker->id()!=receiver->id() && attacker->hit(receiver)) //On s'assure que le joueur ne tente pas de s'attaquer lui meme
		{
			cout<<"Player "<<attacker->id()<<" hit Player "<<receiver->id()<<" !"<<endl;
			//reset(); //On recommance un round
			reset(receiver->id());
		}
	}
}

//Résoud un cas de collision joueur/obstacle (grossièrement)
//Un peu bugger mais vivable (+ Ne devrait pas permettre d'avoir des animations dans les obstacles)
void Game::resolveCollision(Player * p, Obstacle* o)
{
	//Handle Collision
	int x_transform = 0, y_transform = 0;

		//Provisoire !
	pair<int,int> pcenter = make_pair(p->pos().first+PLAYER_WIDTH/2, p->pos().second+PLAYER_HEIGHT/2); //Center géométrique de player
	// cout<<"Player pos : "<<pcenter.first<<" / "<<pcenter.second<<endl;
	// cout<<"Obstacle pos : "<<o->center().first<<" / "<<o->center().second<<endl;

	if(pcenter.first < o->center().first) //Joueur à gauche de l'obstacle
	{
		x_transform = (o->center().first - pcenter.first) - (PLAYER_WIDTH/2+o->box()->w/2);
	}
	else if(pcenter.first > o->center().first)
	{
		x_transform = (pcenter.first - o->center().first) - (PLAYER_WIDTH/2+o->box()->w/2);
	}
	if(pcenter.second < o->center().second) //Joueur au dessus de l'obstacle
	{
		y_transform = (o->center().second - pcenter.second) - (PLAYER_HEIGHT/2+o->box()->h/2);
	}
	else if(pcenter.second > o->center().second) //Joueur au dessous de l'obstacle
	{
		//y_transform = (pcenter.second - o->center().second) - (PLAYER_HEIGHT/2+o->box()->h/2);
		y_transform = (PLAYER_HEIGHT/2+o->box()->h/2) - (pcenter.second - o->center().second); 
	}
	// cout<<"Transform : "<<x_transform<<" / "<<y_transform<<endl;

	//Resolution de la collision (application du plus faible changement)
	if(x_transform !=0 && abs(x_transform) < abs(y_transform))
	{
		p->holdPos(make_pair(p->pos().first+x_transform, p->pos().second)); //Translation en x
	}
	else //if(abs(y_transform)< PLAYER_HEIGHT) 
	{
		p->holdPos(make_pair(p->pos().first, p->pos().second+y_transform)); //Translation en y
	}
}

//Résoud un cas de collision joueur/joueur (Knockback des deux joueurs)
void Game::resolveCollision(Player * p1, Player* p2)
{
	pair<int,int> pos1 = p1->pos(), pos2 = p2->pos();
	if(pos1.first < pos2.first) //P1 à gauche de P2
	{
		pos1.first -= PLAYER_KNOCKBACK;
		pos2.first += PLAYER_KNOCKBACK;
	}
	else //P2 à gauche de P1
	{
		pos1.first += PLAYER_KNOCKBACK;
		pos2.first -= PLAYER_KNOCKBACK;
	}
	p1->stand(pos1);
	p2->stand(pos2);
}

/*
bool Game::isFalling(Player *p, Obstacle *o)
{
	pair<int,int> pcenter = make_pair(p->pos().first+PLAYER_WIDTH/2, p->pos().second+PLAYER_HEIGHT/2); //Center géométrique de player
	int oh = o->box()->h;
	int ow = o->box()->w;
	cout << oh << " | " << o->center().second << endl;
	cout << "position pied : " << pcenter.second + PLAYER_HEIGHT/2 << " | position du sol de l'obstacle : " << o->center().second - oh/2 -20 << endl;
	if ((pcenter.second + PLAYER_HEIGHT/2 < o->center().second - oh/2 -5) && abs(pcenter.first - o->center().first) < ow/2)
		return true;
	return false;
}
*/

//Vérifie si un joueur chute
bool Game::isFalling(Player *p, std::vector<Obstacle*> obsList)
{
	//Identification des obstacles sous le joueur eligibles
	pair<int,int> pcenter = make_pair(p->pos().first+PLAYER_WIDTH/2, p->pos().second+PLAYER_HEIGHT/2); //Centre géométrique de player
	int oh, ow;
	Obstacle floor(*obsList[0]); //Risqué !
	bool firstOcc = true;
	for(Obstacle* o : obsList)
	{
		ow = o->box()->w;
		oh = o->box()->h;
		if ((abs(pcenter.first - o->center().first) <= ow/2) && (pcenter.second + PLAYER_HEIGHT/2 < o->center().second - oh/2))
		{
			if(firstOcc)
			{
				firstOcc = false;
				floor = *o;
			}
			else if(o->center().second - oh/2 < floor.center().second - floor.box()->h/2) 
				floor = *o;
		}
	}
	return (pcenter.second + PLAYER_HEIGHT/2 < floor.center().second - floor.box()->h/2);
}

//Vérifie si un joueur chute
bool Game::isFallingV2(const Player *p, const vector<Obstacle*> obsList)
{
	bool res = true; //On suppose qu'il y a chute

	//A simplifier en n'utilisant que les hitbox passive
	AnimationFrame testFrame(*p->currFrame()); //Sert à tester si un chute est envisageable
	pair<int,int> testPos = testFrame.center();
	testPos.second += 1; //On test juste en dessous du personnage
	testFrame.translate(testPos);

	for(Obstacle* o : obsList)
	{
		if(testFrame.collideP(o->box())) //Si une frame touche un obstacle
		{
			res = false;
			break;
		}
	}
	return res;
}

//Remet à zéro la partie
//Replace les joueurs aux positions de départ
void Game::reset()
{
	_playerList[0]->stand(make_pair(P1_START_POSX,P1_START_POSY));
	_playerList[1]->stand(make_pair(P2_START_POSX,P2_START_POSY));
}
//Replace un joueur à son spawn
void Game::reset(unsigned int playerID)
{
	if(playerID==1)
		_playerList[0]->stand(make_pair(P1_START_POSX,P1_START_POSY));
	if(playerID==2)
		_playerList[1]->stand(make_pair(P2_START_POSX,P2_START_POSY));
}

Game& Game::operator=(const Game& g)
{
	//_playerList = g.PList();

	return *this;
}