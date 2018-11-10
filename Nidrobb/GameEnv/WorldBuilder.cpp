#include "WorldBuilder.hpp"


//Chargement de toute les textures environement.
//Amélioration : ne charger les texture que une à une quand elles sont demandés
WorldBuilder::WorldBuilder(SDL_Renderer *renderer) : _renderer(renderer)
{
	addTexture("red_square","images/red_square.png");
	addTexture("skyBack","images/skyBackground.jpg");
	addTexture("logo","images/Nidrobb.png");
	addTexture("nuage","images/nuage.png");
}

WorldBuilder::~WorldBuilder()
{
	for(auto & i : _texture) // map<>::iterator
	{
		SDL_DestroyTexture(i.second); //Destruction des textures
	}
}

//Ajout d'une texture au dictionnaire
void WorldBuilder::addTexture(const string name, const string imgPath)
{
	//Chargement d'une texture par defaut (objet noir)
	SDL_Surface *tmpSurface = IMG_Load(imgPath.c_str());
	//Verification de la non presence d'erreur lors du chargement
	if(!tmpSurface)
		std::cout << "WorldBuilder : Surface "<< name <<" non chargee. Erreur :" << SDL_GetError() << std::endl;
	//Creation/Ajout de la texture a partir de la surface chargee
	_texture [name]= SDL_CreateTextureFromSurface(_renderer, tmpSurface);
	//Liberation de la memoire allouee pour la surface
	SDL_FreeSurface(tmpSurface);
}

//Construit un obstacle
Obstacle* WorldBuilder::createObstacle(SDL_Texture * texture, const pair<int,int>& Pos, int width, int height) const
{
	SDL_Rect *h = createRect(Pos.first,Pos.second,width,height); //ATTENTION : sprite supprime les rect
	Sprite s(h,texture);
	SDL_Rect *h2 = createRect(Pos.first,Pos.second,width,height);
	Obstacle* res = new Obstacle(s,h2);
	//cout <<"Create Obs: "<<*res->box()<<endl;
	return res;
}

//Construit la map aérienne
World* WorldBuilder::sky()
{
	//Background
	SDL_Rect* worldArea = createRect(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Sprite worldSprite(worldArea,_texture["skyBack"]);

	//Environement
	vector<Obstacle*> obsList;	
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(-WALL_THICKNESS+10,-10), WALL_THICKNESS,SCREEN_HEIGHT+10)); //Mur gauche
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(SCREEN_WIDTH,-90), WALL_THICKNESS,SCREEN_HEIGHT)); //Mur droit
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(-90,-90),SCREEN_WIDTH, WALL_THICKNESS)); //Plafond
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(-50,SCREEN_HEIGHT-WALL_THICKNESS/2),SCREEN_WIDTH+100, WALL_THICKNESS)); //Sol
	obsList.push_back(createObstacle(_texture["logo"], make_pair(SCREEN_WIDTH/2-200, 0), 400, 100)); //Logo
	//Plateformes
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(200,250),300,60));
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(SCREEN_WIDTH-500,250),300,60));
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(50,SCREEN_HEIGHT-200),200,60));
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(SCREEN_WIDTH-400,SCREEN_HEIGHT-200),200,60));
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(SCREEN_WIDTH/2-200,SCREEN_HEIGHT-300),400,100));
	// for(Obstacle* o : obsList)
	// {
	// 	cout<<"Builder :"<<*o->box()<<endl;
	// }

	World* res = new World("Sky World",worldSprite, obsList);

	// for(Obstacle* o : res->obstacles())
	// {
	// 	cout<<"Builder :"<<*o->box()<<endl;
	// }
	return res;
}

//Construit la map de test de collision
World* WorldBuilder::collisionTest()
{
	//Background
	SDL_Rect* worldArea = createRect(0,0, SCREEN_WIDTH, SCREEN_HEIGHT);
	Sprite worldSprite(worldArea,_texture["skyBack"]);

	//Environement
	vector<Obstacle*> obsList;	
	obsList.push_back(createObstacle(_texture["nuage"], make_pair(0,450),700,40)); //Sol
	obsList.push_back(createObstacle(_texture["logo"], make_pair(SCREEN_WIDTH/2-100, 0), 200, 100)); //Logo
	obsList.push_back(createObstacle(_texture["red_square"], make_pair(300,350),100,101)); //Obstacle 1
	obsList.push_back(createObstacle(_texture["red_square"], make_pair(200,400),100,101)); //Obstacle 2
	obsList.push_back(createObstacle(_texture["red_square"], make_pair(350,250),100,101)); //Obstacle 3

	// for(Obstacle* o : obsList)
	// {
	// 	cout<<"Builder :"<<*o->box()<<endl;
	// }

	World* res = new World("Sky World",worldSprite, obsList);

	// for(Obstacle* o : res->obstacles())
	// {
	// 	cout<<"Builder :"<<*o->box()<<endl;
	// }
	return res;
}