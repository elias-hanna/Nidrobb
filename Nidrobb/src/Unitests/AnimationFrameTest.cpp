#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AnimationFrameTest
#include <boost/test/unit_test.hpp>
#include "../Animation/AnimationFrame.hpp"

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
	}
	~F()
	{
		BOOST_TEST_MESSAGE( "teardown fixture" );
		SDL_DestroyTexture(texture);
		SDL_DestroyRenderer( renderer );
		SDL_DestroyWindow( window );
	}

	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Surface *tmpSurface = nullptr;
	SDL_Texture* texture = nullptr;
};

BOOST_AUTO_TEST_SUITE (Constructeurs)
BOOST_FIXTURE_TEST_CASE (Constructeur_Full, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	AnimationFrame frame(s, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y));

	BOOST_REQUIRE(frame.sprite()==s);
	BOOST_REQUIRE(frame.pHitBox().size()==0);
	BOOST_REQUIRE(frame.aHitBox().size()==0);
	BOOST_REQUIRE(frame.center().first==10);
	BOOST_REQUIRE(frame.center().second==20);
}

BOOST_FIXTURE_TEST_CASE (Constructeur_Copie, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	AnimationFrame frame(s, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y));

	AnimationFrame copy = frame;

	BOOST_REQUIRE(copy.sprite()==frame.sprite());
	BOOST_REQUIRE(copy.pHitBox().size()==frame.pHitBox().size());
	BOOST_REQUIRE(copy.aHitBox().size()==frame.aHitBox().size());
	BOOST_REQUIRE(copy.center().first==frame.center().first);
	BOOST_REQUIRE(copy.center().second==frame.center().second);
}
BOOST_AUTO_TEST_SUITE_END( )


BOOST_AUTO_TEST_SUITE (Collisions)
BOOST_FIXTURE_TEST_CASE (CollideA,F)
{
	int x = 10, y=20, w = 30, h=40;
	int xt=0,yt=0,wt=2,ht=2;

	SDL_Rect* test1 = createRect(x,y,w,h);
	SDL_Rect* test2 = createRect(xt,yt,wt,ht);

	Sprite s(createRect(x,y,w,h), texture);

	vector<SDL_Rect*> hitboxs;
	hitboxs.push_back(createRect(x,y,w,h));

	AnimationFrame frame(s, vector<SDL_Rect*>(), hitboxs, make_pair(x,y));

	BOOST_REQUIRE(frame.collideA(test1));
	BOOST_REQUIRE(!frame.collideA(test2));

	delete test1;
	delete test2;
}
BOOST_AUTO_TEST_SUITE_END( )

BOOST_FIXTURE_TEST_CASE(Translate,F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	AnimationFrame frame(s, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y));
	frame.addPHitbox(createRect(x,y,w,h));
	frame.addAHitbox(createRect(x,y,w,h));
	frame.translate(make_pair(0,0));

	BOOST_REQUIRE(frame.pHitBox()[0]->x == 0);
	BOOST_REQUIRE(frame.pHitBox()[0]->y == 0);
	BOOST_REQUIRE(frame.aHitBox()[0]->x == 0);
	BOOST_REQUIRE(frame.aHitBox()[0]->y == 0);
}

BOOST_AUTO_TEST_SUITE (Accesseurs)
BOOST_FIXTURE_TEST_CASE(AddPHitbox, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	AnimationFrame frame(s, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y));

	frame.addPHitbox(createRect(x,y,w,h));

	SDL_Rect* test = createRect(x,y,w,h);

	BOOST_CHECK(frame.pHitBox().size()==1);
	BOOST_CHECK(SDL_RectEquals(frame.pHitBox()[0],test)== SDL_TRUE);

	delete test;
}

BOOST_FIXTURE_TEST_CASE(AddAHitbox, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	AnimationFrame frame(s, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y));

	frame.addAHitbox(createRect(x,y,w,h));

	SDL_Rect* test = createRect(x,y,w,h);

	BOOST_CHECK(frame.aHitBox().size()==1);
	BOOST_CHECK(SDL_RectEquals(frame.aHitBox()[0],test)== SDL_TRUE);

	delete test;
}
BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE (Operateurs)
BOOST_FIXTURE_TEST_CASE(assign,F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	AnimationFrame frame(s, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y));

	AnimationFrame copy = frame;

	BOOST_REQUIRE(frame.center()==copy.center());
	BOOST_REQUIRE(frame.sprite()==copy.sprite());
	BOOST_REQUIRE(frame.pHitBox().size()==copy.pHitBox().size());
	BOOST_REQUIRE(frame.aHitBox().size()==copy.aHitBox().size());

	for(unsigned int i=0;i<copy.pHitBox().size();i++)
		BOOST_REQUIRE(SDL_RectEquals(frame.pHitBox()[i],copy.pHitBox()[i])==SDL_FALSE);
	for(unsigned int i=0;i<copy.aHitBox().size();i++)
		BOOST_REQUIRE(SDL_RectEquals(frame.aHitBox()[i],copy.aHitBox()[i]) == SDL_FALSE);
}

BOOST_FIXTURE_TEST_CASE(equal,F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	AnimationFrame frame(s, vector<SDL_Rect*>(), vector<SDL_Rect*>(), make_pair(x,y));

	AnimationFrame copy = frame;

	BOOST_CHECK(copy==frame);
}
BOOST_AUTO_TEST_SUITE_END( )