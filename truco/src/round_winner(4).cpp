#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void round_winner::execute( vector<void*>& v )
{
	//rule.set_state( "draw", 0 );
	
	//inicializa estados a cada início de mão
	/*
	if( give_cards_state["round"] == 5 )
	{	
		rule.set_state( "team1_points", 0 );
		rule.set_state( "team2_points", 0 );
		rule.set_state( "team1", play_card_state["last_player"] ); //PROBLEMA: chamando o nome do time com nome de jogador
		rule.set_state( "team2", 0 );
	}
	
	//definição dos times
	if ( state["team1"] != play_card_state["last_player"] ) //PROBLEMA: se o team2 nunca ganhar, team2 = 0.
		rule.set_state( "team2", play_card_state["last_player"] );
	
	rule.get_dependencies["give_cards"]->set_state( "round", state["round"] - 1 );
	
	//se houve vitória atribui-se pontuação de acordo com rodada, senão dá empate
	if( play_card_state["draw"] )
		rule.set_state( "draw", 1 );
	else
	{
		if( state["team1"] == play_card_state["last_player"] )
			rule.set_state( "team1_points", state["team1_points"] + give_cards_state["round"] );
		else
			rule.set_state( "team2_points", state["team2_points"] + give_cards_state["round"] );
	}
	*/
}

int round_winner::send_my_message( vector<void*>& v )
{
	/*
	int* a = (int*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at(v.size()-2);
	dealer->send(*who, 1, a, sizeof(int));
	*/
}
