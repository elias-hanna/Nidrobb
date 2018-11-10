#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE InputMapTest
#include <boost/test/unit_test.hpp>
#include "../Command/InputMap.hpp"

BOOST_AUTO_TEST_SUITE (Constructeurs)
//A voir quel commande sont ajouté au final au constructeur
BOOST_AUTO_TEST_CASE (Default)
{
	InputMap map;

	BOOST_CHECK(map.GMap().size()>0);
	BOOST_CHECK(map.P1Map().size()>0);
	BOOST_CHECK(map.P2Map().size()>0);
}
BOOST_AUTO_TEST_SUITE_END( )

BOOST_AUTO_TEST_SUITE(Operators)
BOOST_AUTO_TEST_CASE(access)
{
	InputMap map;

	Command* test = map(SDLK_ESCAPE);

	BOOST_CHECK(test->target()==0);
	BOOST_CHECK(test->name()=="ExitCommand");

	test = map(SDLK_q);
	BOOST_CHECK(test->target()==1);
	BOOST_CHECK(test->name()=="LeftCommand");

	test = map(SDLK_KP_0);
	BOOST_CHECK(test->target()==2);
	BOOST_CHECK(test->name()=="AttackCommand");
}
BOOST_AUTO_TEST_CASE(print)
{
	InputMap map;

	BOOST_CHECK(map.GMap().size()>0);
	BOOST_CHECK(map.P1Map().size()>0);
	BOOST_CHECK(map.P2Map().size()>0);

	std::cout<<"InputMap : "<<std::endl<<map<<std::endl;
}
BOOST_AUTO_TEST_SUITE_END()