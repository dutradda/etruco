#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void round_winner::execute( vector<void*>& v )
{
	/*
	//verifica se houve vitória ou empate	
	if( state["last_played_card"]->value == 0 )
		team = true;
	else if( state["last_played_card"]->value != dependencies["pick_vira"].manilhas and params[1]->get_value() == dependencies["pick_vira"].manilhas )
		flag = true;
	else if( (state["last_played_card"]->value == dependencies["pick_vira"].manilhas and params[1]->get_value() == dependencies["pick_vira"].manilhas ) 									and state["last_played_card"]->suit < params[1]->get_suit() )
		flag = true;
	else if( state["last_played_card"]->value != dependencies["pick_vira"].manilhas and state["last_played_card"]->value < params[1]->get_value() )
		flag = true;
	
	if( state["last_played_card"]->value != dependencies["pick_vira"].manilhas and params[1]->get_value() != dependencies["pick_vira"].manilhas and 
								state["last_played_card"]->value == params[1]->get_value() )
		draw = true;

	//caso haja vitória, passa-se quem ganhou e com que carta, caso contrário informa o empate
	if( flag )
	{
		rule.set_state( "last_played_card", value );
		rule.set_state( "last_player", params[0] );
	}
	if( draw )
		rule.set_state( "draw", 1 );
	*/
	
	//se houve vitória atribui-se pontuação de acordo com rodada
	if( !draw )
	{
		if( team1 == team_winner )
			team1_points = team1_points + dependencies["give_cards"].round;
		else
			team2_points = team1_points + dependencies["give_cards"].round;
	}

	dependencies["give_cards"].round --;
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
