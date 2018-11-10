#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ToolboxTest
#include <boost/test/unit_test.hpp>
#include "../Toolbox.hpp"

BOOST_AUTO_TEST_SUITE (CreateRect)

BOOST_AUTO_TEST_CASE (Positive)
{
	int x = 10, y=20, w = 30, h=40;
	SDL_Rect* r = createRect(x,y,w,h);

	BOOST_REQUIRE(r != nullptr); //Bloquant
	BOOST_REQUIRE(r->x==x);
	BOOST_REQUIRE(r->y==y);
	BOOST_REQUIRE(r->w==w);
	BOOST_REQUIRE(r->h==h);

	delete r;
}

BOOST_AUTO_TEST_CASE (Nul)
{
	int x = 0, y=0, w = 0, h=0;
	SDL_Rect* r = createRect(x,y,w,h);

	BOOST_REQUIRE(r != nullptr);
	BOOST_REQUIRE(r->x==x);
	BOOST_REQUIRE(r->y==y);
	BOOST_REQUIRE(r->w==w);
	BOOST_REQUIRE(r->h==h);

	delete r;
}

BOOST_AUTO_TEST_CASE (Negative)
{
	int x = -10, y=-20, w = -30, h=-40;
	SDL_Rect* r = createRect(x,y,w,h);

	BOOST_REQUIRE(r != nullptr);
	BOOST_REQUIRE(r->x==x);
	BOOST_REQUIRE(r->y==y);
	BOOST_CHECK(r->w>=0); //Devrait pas autoriser w, h <0
	BOOST_CHECK(r->h>=0); //Non bloquant

	delete r;
}

BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE (OperatorPrint)

BOOST_AUTO_TEST_CASE (SDLRect)
{
	int x = 10, y=20, w = 30, h=40;
	SDL_Rect* r = createRect(x,y,w,h);

	BOOST_REQUIRE(r != nullptr); 

	std::cout<<"Rect : "<<x<<"/"<<y<<" - "<<w<<"/"<<h<<" = "<<*r<<std::endl;

	delete r;
}

BOOST_AUTO_TEST_SUITE_END( )