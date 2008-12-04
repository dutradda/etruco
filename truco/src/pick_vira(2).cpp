#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void pick_vira::execute( vector<void*>& v )
{
	Card* vira = truco.get_deck()->get_card();
	int* value = new int;

	if( vira.get_value() != 10)
		*value = vira.get_value() + 1;
	else
		*value = 1;

	//rule.set_state( "manilhas", value );
}

int pick_vira::send_my_message( vector<void*>& v )
{
	/*int* a = (int*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at(v.size()-2);
	dealer->send(*who, 1, a, sizeof(int));*/
}
