#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE SpriteTest
#include <boost/test/unit_test.hpp>
#include "../gui/sprite.hpp"

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
};

BOOST_AUTO_TEST_SUITE (Constructeurs)

BOOST_AUTO_TEST_CASE (Default)
{
	Sprite s;
	BOOST_CHECK(s.getTexture() == nullptr); // test basique
	BOOST_CHECK(s.getRect() == nullptr);
}

BOOST_FIXTURE_TEST_CASE (Constructeur_rect_texture, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	BOOST_REQUIRE(s.getTexture() != nullptr);

	SDL_Rect* r = s.getRect();
	BOOST_REQUIRE(r != nullptr);
	BOOST_REQUIRE(r->x==x);
	BOOST_REQUIRE(r->y==y);
	BOOST_REQUIRE(r->w==w);
	BOOST_REQUIRE(r->h==h);

}

BOOST_FIXTURE_TEST_CASE (Constructeur_copie, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	Sprite copy(s);

	BOOST_REQUIRE(copy.getTexture() == s.getTexture()); //Pas de création de nouvelles textures

	SDL_Rect* r1 = s.getRect();
	SDL_Rect* r2 = copy.getRect();
	BOOST_REQUIRE(r2 != nullptr);
	BOOST_REQUIRE(r1->x==r2->x);
	BOOST_REQUIRE(r1->y==r2->y);
	BOOST_REQUIRE(r1->w==r2->w);
	BOOST_REQUIRE(r1->h==r2->h);

}

BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE(Operators)

BOOST_FIXTURE_TEST_CASE(assign, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	Sprite copy;

	copy=s;

	BOOST_REQUIRE(copy.getTexture() == s.getTexture()); //Pas de création de nouvelles textures

	SDL_Rect* r1 = s.getRect();
	SDL_Rect* r2 = copy.getRect();
	BOOST_REQUIRE(r2 != nullptr);
	BOOST_REQUIRE(r1->x==r2->x);
	BOOST_REQUIRE(r1->y==r2->y);
	BOOST_REQUIRE(r1->w==r2->w);
	BOOST_REQUIRE(r1->h==r2->h);
}

BOOST_FIXTURE_TEST_CASE(equal, F)
{
	int x = 10, y=20, w = 30, h=40;

	Sprite s(createRect(x,y,w,h), texture);

	Sprite copy = s;

	BOOST_CHECK(s==copy);
}

BOOST_AUTO_TEST_SUITE_END()