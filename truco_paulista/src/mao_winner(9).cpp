#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void mao_winner::execute( Rule& rule, Truco truco, vector< void * > params )
{
	/*
	rule.set_state( "num_mao" , 0 );
	
	if( state["num_mao"] == 0 )
	{
		rule.get_dependencies()["teams_points"]->set_state( "team1_points", 0 );
		rule.get_dependencies()["teams_points"]->set_state( "team2_points", 0 );
		rule.get_dependencies()["teams_points"]->set_state( "cont_draw", 0 );
	}
	
	//define se há vencedor e quem é
	if( give_cards_state["round"] == 3 ) //para 2 rodadas
	{
		if( round_winner_state["team1_points"] == 7 )
			rule.set_state( "winner", round_winner_state["team1"] );
		if( round_winner_state["team2_points"] == 7 )
			rule.set_state( "winner", round_winner_state["team2"] );
		rule.set_state( "draw", 0 );
	}
	else //para 3 rodadas
	{ 
		if( round_winner_state["team1_points"] == 0 and round_winner_state["team2_points"] == 0 )
		{
			rule.set_state( "draw", 1 );
			rule.get_dependencies()["teams_points"]->set_state( "cont_draw", state["cont_draw"] + 1 );
		}
		else 
		{
			if( round_winner_state["team1_points"] > round_winner_state["team2_points"] )
				rule.set_state( "winner", round_winner_state["team1"] );
			else
				rule.set_state( "winner", round_winner_state["team2"] );
			rule.set_state( "draw", 0 );
		}
	}
	
	//atribuição de pontuação da mão
	if ( !state["draw"] )
	{
		if( state["winner"] == round_winner_state["team1"] )
			rule.get_dependencies()["teams_points"]->set_state("team1_points", teams_points_state["team1_points"] + give_cards_state["valor_mao"] + state["cont_draw"] );
		else
			rule.get_dependencies()["teams_points"]->set_state("team2_points", teams_points_state["team2_points"] + give_cards_state["valor_mao"] + state["cont_draw"] );
		rule.get_dependencies()["teams_points"]->set_state( "cont_draw", 0 );
	}
	
	rule.set_state( "num_mao" , state["num_mao"] + 1 );
	*/
}

int game_winner::send_my_message( vector<void*>& v )
{
	/*
	int* a = (int*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at(v.size()-2);
	dealer->send(*who, 1, a, sizeof(int));
	*/
}
