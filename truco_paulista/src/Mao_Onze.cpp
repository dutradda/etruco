#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void mao_onze::execute( vector<void*>& v )
{
	/*
	rule.set_state( "mao_onze", false );

	if( teams_points_state["team1_points"] = 11 xor teams_points_state["team2_points"] = 11 )
	{
		rule.set_state( "mao_onze", true );
		rule.get_dependencies()["give_cards"]->set_state( "valor_mao", 3 );
	}
	*/
}

int mao_onze::send_my_message( vector<void*>& v )
{
	/*
	int* a = (int*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at(v.size()-2);
	dealer->send(*who, 1, a, sizeof(int));
	*/
}
