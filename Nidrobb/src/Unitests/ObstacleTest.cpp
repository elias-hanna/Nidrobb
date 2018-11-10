#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ObstacleTest
#include <boost/test/unit_test.hpp>
#include "../GameEnv/Obstacle.hpp"

//http://www.linuxembedded.fr/2015/02/introduction-a-boost-test-library-unit-test-framework/

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

	int x = 10, y=20, w = 30, h=40;
};

BOOST_AUTO_TEST_SUITE (Constructeurs)

BOOST_FIXTURE_TEST_CASE (Default, F)
{
	Sprite s(createRect(x,y,w,h), texture);

	Obstacle o(s, createRect(x,y,w,h));

	SDL_Rect* test = createRect(x,y,w,h);
	BOOST_REQUIRE(o.center()==std::make_pair(x+w/2,y+h/2));
	BOOST_REQUIRE(o.sprite()==s);
	BOOST_REQUIRE(SDL_RectEquals(o.box(),test)==SDL_TRUE);
}

BOOST_FIXTURE_TEST_CASE (Constructeur_copie, F)
{
	Sprite s(createRect(x,y,w,h), texture);

	Obstacle o(s, createRect(x,y,w,h));
	Obstacle copy(o);

	BOOST_REQUIRE(o.center()==copy.center());
	BOOST_REQUIRE(o.sprite()==copy.sprite());
	BOOST_REQUIRE(SDL_RectEquals(o.box(),copy.box())==SDL_TRUE);
}

BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE(Collisions)
BOOST_FIXTURE_TEST_CASE(CollideA, F)
{
	Sprite s(createRect(x,y,w,h), texture);

	Obstacle o(s, createRect(x,y,w,h));

	SDL_Rect* test = createRect(x,y,w,h);

	BOOST_REQUIRE(o.collideA(test)==false); //Obstacle passif

	delete test;
}
BOOST_FIXTURE_TEST_CASE(CollideP, F)
{
	Sprite s(createRect(x,y,w,h), texture);

	Obstacle o(s, createRect(x,y,w,h));

	SDL_Rect* test = createRect(x,y,w,h);
	SDL_Rect* test2 = createRect(x+w,y,w,h);

	BOOST_REQUIRE(o.collideP(test)==true);
	BOOST_REQUIRE(o.collideP(test2)==false);

	delete test;
	delete test2;
}
BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE(Operators)
BOOST_FIXTURE_TEST_CASE(assign, F)
{
	Sprite s(createRect(x,y,w,h), texture);

	Obstacle o(s, createRect(x,y,w,h));

	Obstacle copy = o;

	BOOST_REQUIRE(o.center()==copy.center());
	BOOST_REQUIRE(o.sprite()==copy.sprite());
	BOOST_REQUIRE(SDL_RectEquals(o.box(),copy.box())==SDL_TRUE);
}
BOOST_FIXTURE_TEST_CASE(equal, F)
{
	Sprite s(createRect(x,y,w,h), texture);

	Obstacle o(s, createRect(x,y,w,h));

	Obstacle copy = o;

	BOOST_REQUIRE(o==copy);
}

BOOST_AUTO_TEST_SUITE_END()