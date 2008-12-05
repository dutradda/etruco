#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void game_winner::execute( vector<void*>& v )
{

	if ( teams_points_state["team1_points"] >= 12  )
		rule.set_state( "winner", mao_winner_state["team1"] );
	else
		rule.set_state( "winner", mao_winner_state["team2"] );
}

int game_winner::send_my_message( vector<void*>& v)
{
	int* a = (int*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at(v.size()-2);
	dealer->send(*who, 1, a, sizeof(int));
}
