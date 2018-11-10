#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AnimationTest
#include <boost/test/unit_test.hpp>
#include "../Animation/Animation.hpp"

//Fixture
struct F
{
	F()
	{
		BOOST_TEST_MESSAGE( "setup fixture" );
		window = SDL_CreateWindow("Test",SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 10, 10, SDL_WINDOW_SHOWN);
		BOOST_CHECK(window != nullptr);
		renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
		BOOST_CHECK(renderer != nullptr);
		//Chargement d'une texture par defaut (objet noir)
		tmpSurface = IMG_Load("images/black.png");
		//Verification de la non presence d'erreur lors du chargement
		BOOST_CHECK(tmpSurface != nullptr);
		//Creation de la texture du sprite a partir de la surface chargee
		texture = SDL_CreateTextureFromSurface(renderer, tmpSurface);
		//Liberation de la memoire allouee pour la surface
		SDL_FreeSurface(tmpSurface);

		x = 10; y=20; w = 30; h=40;

		
	}
	~F()
	{
		// for(AnimationFrame* a : vframe)
		// 	delete a;

		BOOST_TEST_MESSAGE( "teardown fixture" );
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer( renderer );
		SDL_DestroyWindow( window );
	}

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface *tmpSurface = nullptr;
	SDL_Texture* texture = nullptr;

	int x, y, w , h;
};

BOOST_AUTO_TEST_SUITE (Constructeurs)
BOOST_FIXTURE_TEST_CASE (Constructeur_Full, F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);
	Sprite s2(createRect(x+10,y+10,w,h), texture);
	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y)));
	vframe.push_back(new AnimationFrame(s2, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x+10,y+10)));

	Animation anim(name, vframe);

	BOOST_REQUIRE(anim.name()==name);
	BOOST_REQUIRE(anim.progress()==1);
	BOOST_REQUIRE(anim.duration()==vframe.size());
	for(unsigned int i=0; i<vframe.size(); i++)
	{
		//std::cout<<"Frame : "<<i<<"/"<<vframe.size()<<std::endl;
		BOOST_REQUIRE(anim.getFrame(i)==vframe[i]);
	}
}

BOOST_FIXTURE_TEST_CASE (Constructeur_Copie, F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);
	Sprite s2(createRect(x+10,y+10,w,h), texture);
	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y)));
	vframe.push_back(new AnimationFrame(s2, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x+10,y+10)));

	Animation anim(name, vframe);
	Animation copy(anim);

	BOOST_REQUIRE(copy.name()==anim.name());
	BOOST_REQUIRE(copy.progress()==anim.progress());
	BOOST_REQUIRE(copy.duration()==anim.duration());

	for(unsigned int i=0; i<anim.duration(); i++)
	{
		BOOST_REQUIRE(*copy.getFrame(i)==*anim.getFrame(i));
	}
}
BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE (Frame_Access)

BOOST_FIXTURE_TEST_CASE (InProgress,F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);
	Sprite s2(createRect(x+10,y+10,w,h), texture);
	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y)));
	vframe.push_back(new AnimationFrame(s2, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x+10,y+10)));
	vframe.push_back(new AnimationFrame(s2, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x+10,y+10)));

	Animation anim(name, vframe);

	BOOST_REQUIRE(anim.inProgress()==true);

	anim.nextFrame();
	BOOST_REQUIRE(anim.inProgress()==true);

	anim.nextFrame();
	BOOST_REQUIRE(anim.inProgress()==false); //On a atteint la dernière frame

	anim.nextFrame();
	BOOST_REQUIRE(anim.inProgress()==false);
}

BOOST_FIXTURE_TEST_CASE (NextFrame,F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);
	Sprite s2(createRect(x+10,y+10,w,h), texture);
	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y)));
	vframe.push_back(new AnimationFrame(s2, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x+10,y+10)));

	Animation anim(name, vframe);

	BOOST_CHECK(anim.progress()==1);
	pair<int,int> pos = anim.nextFrame();
	BOOST_REQUIRE(anim.progress()==2);
	BOOST_REQUIRE(pos == make_pair(x,y));

	//Empeche dépassement
	pos = anim.nextFrame();
	BOOST_REQUIRE(pos == make_pair(x+10,y+10));
	BOOST_REQUIRE(anim.progress()==2);
}
BOOST_FIXTURE_TEST_CASE (HoldPos,F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);
	Sprite s2(createRect(x+10,y+10,w,h), texture);
	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y)));
	vframe.push_back(new AnimationFrame(s2, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x+10,y+10)));

	Animation anim(name, vframe);

	pair<int,int> hold = make_pair(100, 200);

	anim.holdPos(hold);

	BOOST_CHECK(anim.progress()==1); //On verfie qu'on est tjrs au début de l'animation
	pair<int,int> pos = anim.nextFrame(); //On récupère la position ( & passe à la prochaine frame)
	BOOST_REQUIRE(pos == hold); 

	BOOST_CHECK(anim.progress()==2);
	pos = anim.nextFrame(); //On récupère la position ( & passe à la prochaine frame)
	BOOST_REQUIRE(pos == hold);
}
BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE (Collisions)
BOOST_FIXTURE_TEST_CASE (CollideA,F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);

	vector<SDL_Rect*> hitboxs;
	hitboxs.push_back(createRect(x,y,w,h));

	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, vector<SDL_Rect*>(), hitboxs, make_pair(x,y)));

	Animation anim(name, vframe);

	int xt=x,yt=y,wt=w-10,ht=h-10;
	int xt2=x+w,yt2=y,wt2=w,ht2=h;

	SDL_Rect* test = createRect(xt,yt,wt,ht); //Box incluse
	SDL_Rect* test2 = createRect(xt2,yt2,wt2,ht2); //Box externe

	BOOST_REQUIRE(anim.collideA(test)==true);
	BOOST_REQUIRE(anim.collideA(test2)==false); 
}
BOOST_FIXTURE_TEST_CASE (CollideP,F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);

	vector<SDL_Rect*> hitboxs;
	hitboxs.push_back(createRect(x,y,w,h));

	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, hitboxs, vector<SDL_Rect*>(), make_pair(x,y)));

	Animation anim(name, vframe);

	int xt=x,yt=y,wt=w-10,ht=h-10;
	int xt2=x+w,yt2=y,wt2=w,ht2=h;

	SDL_Rect* test = createRect(xt,yt,wt,ht); //Box incluse
	SDL_Rect* test2 = createRect(xt2,yt2,wt2,ht2); //Box externe


	BOOST_REQUIRE(anim.collideP(test)==true);
	BOOST_REQUIRE(anim.collideP(test2)==false);
}

BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE (Operateurs)
BOOST_FIXTURE_TEST_CASE(assign,F)
{
	string name = "test";
	Sprite s1(createRect(x,y,w,h), texture);
	Sprite s2(createRect(x+10,y+10,w,h), texture);
	vector<AnimationFrame*> vframe;
	vframe.push_back(new AnimationFrame(s1, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y)));
	vframe.push_back(new AnimationFrame(s2, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x+10,y+10)));

	Animation anim(name, vframe);
	Animation copy = anim;

	BOOST_REQUIRE(copy.name()==anim.name());
	BOOST_REQUIRE(copy.progress()==anim.progress());
	BOOST_REQUIRE(copy.duration()==anim.duration());

	for(unsigned int i=0; i<anim.duration(); i++)
	{
		BOOST_REQUIRE(*copy.getFrame(i)==*anim.getFrame(i));
	}
}

BOOST_AUTO_TEST_SUITE_END( )