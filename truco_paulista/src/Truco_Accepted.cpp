#include <string>
#include <vector>
#include "truco_paulista_rule.h"

void truco_accepted::execute( vector<void*>& v )
{
	/*
	rule.get_dependencies()["give_cards"]->set_state( "truco_accepted", true);
	rule.get_dependencies()["give_cards"]->set_state( "asks", give_cards_state["asks"] + 1 );
	rule.get_dependencies()["give_cards"]->set_state( "valor_mao", 3*give_cards_state["asks"] );
	*/
}

int truco_accepted::send_my_message( vector<void*>& v )
{
	/*
	int* a = (int*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at(v.size()-2);
	dealer->send(*who, 1, a, sizeof(int));
	*/
}
