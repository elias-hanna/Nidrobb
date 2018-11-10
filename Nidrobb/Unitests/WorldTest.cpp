#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE WorldTest
#include <boost/test/unit_test.hpp>
#include "../GameEnv/World.hpp"

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
	std::string name = "Test";
	Sprite s(createRect(x,y,w,h), texture);
	std::vector<Obstacle*> obsList;
	obsList.push_back(new Obstacle(s,createRect(x,y,w,h)));

	World w(name,s, obsList);

	BOOST_REQUIRE(w.name()==name);
	BOOST_REQUIRE(w.sprite()==s);
	BOOST_REQUIRE(w.obstacles().size()==obsList.size());
	std::vector<Obstacle*> wo = w.obstacles();
	for(unsigned int i =0; i< obsList.size(); i++)
	{
		BOOST_REQUIRE(*obsList[i]==*wo[i]);
	}
}

BOOST_FIXTURE_TEST_CASE (Constructeur_copie, F)
{
	std::string name = "Test";
	Sprite s(createRect(x,y,w,h), texture);
	std::vector<Obstacle*> obsList;
	obsList.push_back(new Obstacle(s,createRect(x,y,w,h)));

	World w(name,s, obsList);
	World copy(w);

	BOOST_REQUIRE(w.name()==copy.name());
	BOOST_REQUIRE(w.sprite()==copy.sprite());
	BOOST_REQUIRE(w.obstacles().size()==copy.obstacles().size());
	std::vector<Obstacle*> wo = w.obstacles();
	std::vector<Obstacle*> wc = copy.obstacles();
	for(unsigned int i =0; i< obsList.size(); i++)
	{
		BOOST_REQUIRE(*wc[i]==*wo[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE(Operators)
BOOST_FIXTURE_TEST_CASE(assign, F)
{
	std::string name = "Test";
	Sprite s(createRect(x,y,w,h), texture);
	std::vector<Obstacle*> obsList;
	obsList.push_back(new Obstacle(s,createRect(x,y,w,h)));

	World w(name,s, obsList);
	World copy = w;

	BOOST_REQUIRE(w.name()==copy.name());
	BOOST_REQUIRE(w.sprite()==copy.sprite());
	BOOST_REQUIRE(w.obstacles().size()==copy.obstacles().size());
	std::vector<Obstacle*> wo = w.obstacles();
	std::vector<Obstacle*> wc = copy.obstacles();
	for(unsigned int i =0; i< obsList.size(); i++)
	{
		BOOST_REQUIRE(*wc[i]==*wo[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END()