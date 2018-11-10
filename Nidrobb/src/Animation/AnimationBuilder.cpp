#include "AnimationBuilder.hpp"

//Chargement de toute les textures joueurs.
//Amélioration : ne charger les texture que une à une quand elles sont demandés
AnimationBuilder::AnimationBuilder(SDL_Renderer *renderer):_renderer(renderer)
{
	//ATTENTION BUILDER CREER UNE FOIS PAR JOUEUR (soit singleton soit texture persos)
	//addTexture("red_square","images/red_square.png");
	// addTexture("stand","images/stickman_stand.png");
	// addTexture("right_move","images/stickman_right.png");
	// addTexture("jump","images/jump.jpg");
	// addTexture("crouch1","images/crouch1.jpg");
	// addTexture("crouch2","images/crouch2.jpg");
	// addTexture("punch","images/stickman_punch.png");

	addTexture("stand","images/Robot/robot_stand.png");
	addTexture("right_move","images/Robot/robot_right.png");
	addTexture("right_move2","images/Robot/robot_right2.png");
	addTexture("left_move","images/Robot/robot_left.png");
	addTexture("left_move2","images/Robot/robot_left2.png");
	addTexture("jump","images/Robot/robot_jump.png");
	addTexture("jump_right","images/Robot/robot_jump_right.png");
	addTexture("jump_right2","images/Robot/robot_jump_right2.png");
	addTexture("jump_left","images/Robot/robot_jump_left.png");
	addTexture("jump_left2","images/Robot/robot_jump_left2.png");
	addTexture("crouch","images/Robot/robot_crouch.png");
	addTexture("attack_left","images/Robot/robot_attack_left.png");
	addTexture("attack_left2","images/Robot/robot_attack_left2.png");
	addTexture("attack_right","images/Robot/robot_attack_right.png");
	addTexture("attack_right2","images/Robot/robot_attack_right2.png");
}

AnimationBuilder::~AnimationBuilder()
{
	for(auto & i : _texture) // map<>::iterator
	{
		SDL_DestroyTexture(i.second); //Destruction des textures
	}
}

//Ajout d'une texture au dictionnaire
void AnimationBuilder::addTexture(const string name, const string imgPath)
{
	//Chargement d'une texture par defaut (objet noir)
	SDL_Surface *tmpSurface = IMG_Load(imgPath.c_str());
	//Verification de la non presence d'erreur lors du chargement
	if(!tmpSurface)
		std::cout << "AnimationBuilder : Surface "<< name <<" non chargee. Erreur :" << SDL_GetError() << std::endl;
	//Creation/Ajout de la texture a partir de la surface chargee
	_texture [name]= SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	//Liberation de la memoire allouee pour la surface
	SDL_FreeSurface(tmpSurface);
}

//Construit une frame de joueur. Par défaut, sans active hitbox et avec le rectangle de texture en passive hitbox.
AnimationFrame* AnimationBuilder::PlayerFrame(SDL_Texture * texture, const pair<int,int>& Pos, SDL_Rect* SpriteRect, const vector<SDL_Rect*> ahitbox, const vector<SDL_Rect*>& phitbox) const
{
	AnimationFrame* res;
	if(SpriteRect == nullptr)
	{
		SpriteRect = createRect(Pos.first,Pos.second,PLAYER_WIDTH,PLAYER_HEIGHT);
	}

	Sprite s(SpriteRect,texture);

	if(phitbox.size()==0)//Passive hitbox par défault (Rectangle du sprite)
	{
		//cout<<"default"<<endl;
		vector<SDL_Rect*> defPhitbox;
		defPhitbox.push_back(SpriteRect);
		res = new AnimationFrame(s,defPhitbox,ahitbox, Pos);
	}
	else
		res = new AnimationFrame(s,phitbox,ahitbox, Pos);
	
	return res;
}

//ON prefere des constructeur avec pos initial ou intial/final ?

//Construit l'animation statique
Animation* AnimationBuilder::stand(const pair<int,int>& StartPos)
{
	//cout<<"AnimationBuilder : Stand"<<endl;

	vector<AnimationFrame*> anim;
	anim.push_back(PlayerFrame(_texture["stand"], StartPos));

	/*
	//Creation d'une hitbox
	SDL_Rect *h = createRect(StartPos.first,StartPos.second,PLAYER_WIDTH,PLAYER_HEIGHT);
	//ATTENTION A LA POSITION ? POSITION DU CDG OU DES PIEDS ?

	//Declaration du vecteur des hitboxes d'un personnage
	vector<SDL_Rect*> phitbox;
	//Ajout d'une hitbox au vecteur
	phitbox.push_back(h);

	vector<SDL_Rect*> ahitbox; //Vide
	//Ajout d'une hitbox au vecteur
	//ahitbox.push_back(h2);

	//Sprite s(_renderer, h, "images/stickman_stand.png");
	Sprite s(h,_texture["stand"]);

	//Creation d'une frame d'une animation composee de cette hitbox
	AnimationFrame* animF = new AnimationFrame(s,phitbox,ahitbox, StartPos);

	//Creation de l'animation en ajoutant la frame
	vector<AnimationFrame*> anim;
	anim.push_back(animF);
	*/
	//Animation res(anim);
	return new Animation("Stand",anim);//Attention on souhaite plus tard creer des ensemble de frame
}

//Construit un déplacement vers la droite
//Vitesse en fonction des positions/nombre de frames ...
Animation* AnimationBuilder::moveRight(const pair<int,int>& StartPos)
{
	//cout<<"AnimationBuilder : moveRight"<<endl;

	pair<int,int> FinalPos = make_pair(StartPos.first+PLAYER_MOVE_DISTANCE, StartPos.second); //Position finale
	pair<int,int> MidPos = make_pair((StartPos.first + FinalPos.first)/2, (StartPos.second + FinalPos.second)/2); //Position Intermédiaire
	//cout<<"   "<<StartPos.first<<"/"<<StartPos.second<<"-"<<FinalPos.first<<"/"<<FinalPos.second<<endl;
	vector<AnimationFrame*> anim;

	vector<SDL_Rect*> aHitbox; aHitbox.push_back(createRect(StartPos.first, StartPos.second,PLAYER_WIDTH,PLAYER_HEIGHT));

	//1ere frame
	//anim.push_back(PlayerFrame(_texture["right_move"], StartPos, nullptr, aHitbox));
	anim.push_back(PlayerFrame(_texture["right_move"], StartPos));
	anim.push_back(PlayerFrame(_texture["right_move"], StartPos));	
	/*
	SDL_Rect *h = createRect(StartPos.first,StartPos.second,PLAYER_WIDTH,PLAYER_HEIGHT);
	
	vector<SDL_Rect*> phitbox;
	phitbox.push_back(h);

	vector<SDL_Rect*> ahitbox; //Vide

	Sprite s1(h,_texture["stand"]);

	//AnimationFrame animF1(phitbox,ahitbox, StartPos);
	AnimationFrame* animF1 = new AnimationFrame(s1,phitbox,ahitbox, StartPos);
	*/

	//2e Frame
	anim.push_back(PlayerFrame(_texture["right_move"], MidPos));
	anim.push_back(PlayerFrame(_texture["right_move2"], MidPos));
	/*
	h = createRect(MidPos.first,MidPos.second,PLAYER_WIDTH,PLAYER_HEIGHT);

	phitbox.clear();
	phitbox.push_back(h);

	ahitbox.clear(); //Vide
	//ahitbox.push_back(h2);

	Sprite s2(h,_texture["right_move"]);

	//AnimationFrame animF2(phitbox,ahitbox, MidPos);
	AnimationFrame* animF2 = new AnimationFrame(s2,phitbox,ahitbox, MidPos);
	*/

	//3e Frame
	anim.push_back(PlayerFrame(_texture["right_move2"], FinalPos));
	anim.push_back(PlayerFrame(_texture["stand"], FinalPos));
	/*
	h = createRect(FinalPos.first,FinalPos.second,PLAYER_WIDTH,PLAYER_HEIGHT);
	
	phitbox.clear();
	phitbox.push_back(h);

	ahitbox.clear(); //Vide

	Sprite s3(h,_texture["stand"]);

	//AnimationFrame animF3(phitbox,ahitbox, FinalPos);
	AnimationFrame* animF3 = new AnimationFrame(s3,phitbox,ahitbox, FinalPos);	
	*/

	//Creation de l'animation en ajoutant les frame
	/*
	vector<AnimationFrame*> anim;
	anim.push_back(animF1);
	anim.push_back(animF2);
	anim.push_back(animF3);
	*/
	//cout<<"Builder Right size: "<< anim.size() <<endl;
	//Animation res(anim);
	return new Animation("Right Move",anim);//Attention on souhaite plus tard creer des ensemble de frame
}

//Construit un déplacement vers la gauche
//Vitesse en fonction des positions/nombre de frames ...
//Besoin de sprite approprié
Animation* AnimationBuilder::moveLeft(const pair<int,int>& StartPos)
{
	//cout<<"AnimationBuilder : moveLeft"<<endl;

	pair<int,int> FinalPos = make_pair(StartPos.first-PLAYER_MOVE_DISTANCE, StartPos.second); //Position finale
	pair<int,int> MidPos = make_pair((StartPos.first + FinalPos.first)/2, (StartPos.second + FinalPos.second)/2); //Position Intermédiaire

	//cout<<"   "<<StartPos.first<<"/"<<StartPos.second<<"-"<<FinalPos.first<<"/"<<FinalPos.second<<endl;
	
	vector<AnimationFrame*> anim;

	//1ere frame
	anim.push_back(PlayerFrame(_texture["left_move"], StartPos));	
	anim.push_back(PlayerFrame(_texture["left_move"], StartPos));	

	//2e Frame
	anim.push_back(PlayerFrame(_texture["left_move"], MidPos));
	anim.push_back(PlayerFrame(_texture["left_move2"], MidPos));

	//3e Frame
	anim.push_back(PlayerFrame(_texture["left_move2"], FinalPos));
	anim.push_back(PlayerFrame(_texture["stand"], FinalPos));

	//Animation res(anim);
	return new Animation("Left Move",anim);
}

//Construit un saut
//PB DERNIERE FRAME PAS JOUER -> CHECK player in progress
Animation* AnimationBuilder::jump(const pair<int,int>& StartPos)
{
	//cout<<"AnimationBuilder : Jump"<<endl;

	vector<AnimationFrame*> anim;

	pair<int,int> MidPos = make_pair(StartPos.first, StartPos.second - PLAYER_JUMP_HEIGHT/2); //Position Intermédiaire
	pair<int,int> TopPos = make_pair(StartPos.first, (StartPos.second - PLAYER_JUMP_HEIGHT)); //Position zenith
	//1ere frame
	anim.push_back(PlayerFrame(_texture["jump"], StartPos));
	anim.push_back(PlayerFrame(_texture["jump"], StartPos));
	anim.push_back(PlayerFrame(_texture["jump"], StartPos));

	//2e frame
	anim.push_back(PlayerFrame(_texture["jump"], MidPos));
	anim.push_back(PlayerFrame(_texture["jump"], MidPos));
	anim.push_back(PlayerFrame(_texture["jump"], MidPos));

	//3e frame
	anim.push_back(PlayerFrame(_texture["jump"], TopPos));
	anim.push_back(PlayerFrame(_texture["jump"], TopPos));
	anim.push_back(PlayerFrame(_texture["jump"], TopPos));

	//4e frame
	anim.push_back(PlayerFrame(_texture["stand"], MidPos));
	anim.push_back(PlayerFrame(_texture["stand"], MidPos));
	anim.push_back(PlayerFrame(_texture["stand"], MidPos));

	//5e frame
	anim.push_back(PlayerFrame(_texture["stand"], StartPos));
	anim.push_back(PlayerFrame(_texture["stand"], StartPos));

	//Frame de debbug : PB de dernière frame pas tjrs jouer
	//anim.push_back(PlayerFrame(_texture["stand"], StartPos));

	//Animation res(anim);
	return new Animation("Jump",anim);//Attention on souhaite plus tard creer des ensemble de frame
}

//Construit un saut vers la droite
//Besoin de sprite approprié
Animation* AnimationBuilder::rightJump(const pair<int,int>& StartPos)
{
	//cout<<"AnimationBuilder : Right Jump"<<endl;

	vector<AnimationFrame*> anim;

	pair<int,int> MidPos1 = make_pair(StartPos.first+PLAYER_MOVE_DISTANCE, StartPos.second - PLAYER_JUMP_HEIGHT/4); //Position Intermédiaire
	pair<int,int> MidPos2 = make_pair(StartPos.first+PLAYER_MOVE_DISTANCE*2, StartPos.second - PLAYER_JUMP_HEIGHT/2); //Position Intermédiaire
	pair<int,int> TopPos = make_pair(StartPos.first+PLAYER_MOVE_DISTANCE*3, (StartPos.second - PLAYER_JUMP_HEIGHT)); //Position zenith
	pair<int,int> MidPos3 = make_pair(StartPos.first+PLAYER_MOVE_DISTANCE*4, StartPos.second - PLAYER_JUMP_HEIGHT/2); //Position Intermédiaire
	pair<int,int> MidPos4 = make_pair(StartPos.first+PLAYER_MOVE_DISTANCE*5, StartPos.second - PLAYER_JUMP_HEIGHT/4); //Position Intermédiaire
	pair<int,int> EndPos = make_pair(StartPos.first+PLAYER_MOVE_DISTANCE*6, StartPos.second); //Position Intermédiaire

	anim.push_back(PlayerFrame(_texture["jump_right"], StartPos));
	anim.push_back(PlayerFrame(_texture["jump_right"], MidPos1));
	anim.push_back(PlayerFrame(_texture["jump_right"], MidPos1));
	anim.push_back(PlayerFrame(_texture["jump_right"], MidPos2));
	anim.push_back(PlayerFrame(_texture["jump_right"], MidPos2));
	anim.push_back(PlayerFrame(_texture["jump"], TopPos));
	anim.push_back(PlayerFrame(_texture["jump"], TopPos));
	anim.push_back(PlayerFrame(_texture["jump_right2"], MidPos3));
	anim.push_back(PlayerFrame(_texture["jump_right2"], MidPos3));
	anim.push_back(PlayerFrame(_texture["jump_right2"], MidPos4));
	anim.push_back(PlayerFrame(_texture["jump_right2"], MidPos4));
	anim.push_back(PlayerFrame(_texture["jump_right2"], EndPos));
	anim.push_back(PlayerFrame(_texture["stand"], EndPos));

	return new Animation("Right Jump",anim);
}

//Construit un saut vers la gauche
//Besoin de sprite approprié
Animation* AnimationBuilder::leftJump(const pair<int,int>& StartPos)
{
	//cout<<"AnimationBuilder : Left Jump"<<endl;

	vector<AnimationFrame*> anim;

	pair<int,int> MidPos1 = make_pair(StartPos.first-PLAYER_MOVE_DISTANCE, StartPos.second - PLAYER_JUMP_HEIGHT/4); //Position Intermédiaire
	pair<int,int> MidPos2 = make_pair(StartPos.first-PLAYER_MOVE_DISTANCE*2, StartPos.second - PLAYER_JUMP_HEIGHT/2); //Position Intermédiaire
	pair<int,int> TopPos = make_pair(StartPos.first-PLAYER_MOVE_DISTANCE*3, (StartPos.second - PLAYER_JUMP_HEIGHT)); //Position zenith
	pair<int,int> MidPos3 = make_pair(StartPos.first-PLAYER_MOVE_DISTANCE*4, StartPos.second - PLAYER_JUMP_HEIGHT/2); //Position Intermédiaire
	pair<int,int> MidPos4 = make_pair(StartPos.first-PLAYER_MOVE_DISTANCE*5, StartPos.second - PLAYER_JUMP_HEIGHT/4); //Position Intermédiaire
	pair<int,int> EndPos = make_pair(StartPos.first-PLAYER_MOVE_DISTANCE*6, StartPos.second); //Position Intermédiaire

	anim.push_back(PlayerFrame(_texture["jump_left"], StartPos));
	anim.push_back(PlayerFrame(_texture["jump_left"], MidPos1));
	anim.push_back(PlayerFrame(_texture["jump_left"], MidPos1));
	anim.push_back(PlayerFrame(_texture["jump_left"], MidPos2));
	anim.push_back(PlayerFrame(_texture["jump_left"], MidPos2));
	anim.push_back(PlayerFrame(_texture["jump"], TopPos));
	anim.push_back(PlayerFrame(_texture["jump"], TopPos));
	anim.push_back(PlayerFrame(_texture["jump_left2"], MidPos3));
	anim.push_back(PlayerFrame(_texture["jump_left2"], MidPos3));
	anim.push_back(PlayerFrame(_texture["jump_left2"], MidPos4));
	anim.push_back(PlayerFrame(_texture["jump_left2"], MidPos4));
	anim.push_back(PlayerFrame(_texture["jump_left2"], EndPos));
	anim.push_back(PlayerFrame(_texture["stand"], EndPos));

	return new Animation("Left Jump",anim);
}

//Constuit l'animation pour s'accroupir
Animation* AnimationBuilder::crouch(const pair<int,int>& StartPos)
{
	//cout << "AnimationBuilder : Crouch" << endl;

	vector<AnimationFrame*> anim;

	SDL_Rect* crouchRect1 = createRect(StartPos.first,StartPos.second+PLAYER_HEIGHT*1/3,PLAYER_WIDTH,PLAYER_HEIGHT*2/3); //Acrroupi = plus petite hitbox/sprite
	SDL_Rect* crouchRect2 = createRect(StartPos.first,StartPos.second+PLAYER_HEIGHT*1/3,PLAYER_WIDTH,PLAYER_HEIGHT*2/3); 

	anim.push_back(PlayerFrame(_texture["crouch"], StartPos, crouchRect1));
	anim.push_back(PlayerFrame(_texture["crouch"], StartPos, crouchRect2));

	return new Animation("Crouch", anim);
}

//Construit une chute
Animation* AnimationBuilder::fall(const pair<int, int>& StartPos)//, const pair<int, int>& EndPos)
{
	//cout << "AnimationBuilder : Fall" << endl;

	vector<AnimationFrame*> anim;

	/*
	pair<int, int> pos;

	//Chute a vitesse consdtante... on peut l'ameliorer on verra

	int y = StartPos.second;
	
	while( y < EndPos.second )
	{
		pos = make_pair(StartPos.first, y);
		anim.push_back(PlayerFrame(_texture["stand"], pos));
		y += 1;
	}
	*/

	pair<int, int> newPos(StartPos.first, StartPos.second + PLAYER_FALL_SPEED);

	// anim.push_back(PlayerFrame(_texture["stand"], StartPos));
	anim.push_back(PlayerFrame(_texture["stand"], newPos));

	//COmment faire ? On aimerait detecter le bord le plus pres sur lequel le perso atterit ?
	return new Animation("Fall", anim);
}

//Construit une attaque vers la droite
//Hitbox active à retravailler ! (parade impossible)
Animation* AnimationBuilder::attackRight(const pair<int,int>& StartPos)
{
	vector<AnimationFrame*> anim;

	vector<SDL_Rect*> attackBox1;
	//attackBox.push_back(createRect(StartPos.first,StartPos.second+PLAYER_HEIGHT*1/4,PLAYER_WIDTH,PLAYER_HEIGHT*1/10));
	attackBox1.push_back(createRect(StartPos.first,StartPos.second,PLAYER_WIDTH,PLAYER_HEIGHT*1/3));

	vector<SDL_Rect*> attackBox2;
	//attackBox.push_back(createRect(StartPos.first,StartPos.second+PLAYER_HEIGHT*1/4,PLAYER_WIDTH,PLAYER_HEIGHT*1/10));
	attackBox2.push_back(createRect(StartPos.first,StartPos.second,PLAYER_WIDTH*3/2,PLAYER_HEIGHT*1/3));
	
	anim.push_back(PlayerFrame(_texture["attack_right"], StartPos, nullptr, attackBox1));
	anim.push_back(PlayerFrame(_texture["attack_right"], StartPos, nullptr, attackBox1));
	anim.push_back(PlayerFrame(_texture["attack_right"], StartPos, nullptr, attackBox1));
	anim.push_back(PlayerFrame(_texture["attack_right2"], StartPos, nullptr, attackBox2));
	anim.push_back(PlayerFrame(_texture["attack_right2"], StartPos, nullptr, attackBox2));
	anim.push_back(PlayerFrame(_texture["attack_right2"], StartPos, nullptr, attackBox2));
	anim.push_back(PlayerFrame(_texture["stand"], StartPos));

	return new Animation("Attack Right", anim);
}

//Construit une attaque vers la gauche
//Besoin de sprite approprié
//Hitbox active à retravailler ! (parade impossible)
Animation* AnimationBuilder::attackLeft(const pair<int,int>& StartPos)
{
	vector<AnimationFrame*> anim;

	vector<SDL_Rect*> attackBox1;
	attackBox1.push_back(createRect(StartPos.first-PLAYER_WIDTH,StartPos.second,PLAYER_WIDTH,PLAYER_HEIGHT*1/3));

	vector<SDL_Rect*> attackBox2;
	//attackBox.push_back(createRect(StartPos.first,StartPos.second+PLAYER_HEIGHT*1/4,PLAYER_WIDTH,PLAYER_HEIGHT*1/10));
	attackBox2.push_back(createRect(StartPos.first-PLAYER_WIDTH/2,StartPos.second,PLAYER_WIDTH*3/2,PLAYER_HEIGHT*1/3));
	
	anim.push_back(PlayerFrame(_texture["attack_left"], StartPos, nullptr, attackBox1));
	anim.push_back(PlayerFrame(_texture["attack_left"], StartPos, nullptr, attackBox1));
	anim.push_back(PlayerFrame(_texture["attack_left"], StartPos, nullptr, attackBox1));
	anim.push_back(PlayerFrame(_texture["attack_left2"], StartPos, nullptr, attackBox2));
	anim.push_back(PlayerFrame(_texture["attack_left2"], StartPos, nullptr, attackBox2));
	anim.push_back(PlayerFrame(_texture["attack_left2"], StartPos, nullptr, attackBox2));
	anim.push_back(PlayerFrame(_texture["stand"], StartPos));

	return new Animation("Attack Left", anim);
}