#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void play_card::execute( vector<void*>& v )
{
	map <string, void*> state = rule.get_state();

	//int manilha = rule.get_dependencies()["pick_vira"]->get_state( "manilhas" );
	//int* value = new int( params[1]->get_value() );	//params[0] = jogador e params[1] = carta do jogador
	bool flag = false;
	bool draw = false;

	//rule.set_state( "draw", 0 );
	
	//verifica se houve vitória ou empate
	/*
	if( state["last_played_card"]->value == 0 )
		flag = true;
	else if( state["last_played_card"]->value != manilha and params[1]->get_value() == manilha )
		flag = true;
	else if( (state["last_played_card"]->value == manilha and params[1]->get_value() == manilha) and
								 state["last_played_card"]->suit < params[1]->get_suit() )
		flag = true;
	else if( state["last_played_card"]->value != manilha and state["last_played_card"]->value < params[1]->get_value() )
		flag = true;
	
	if( state["last_played_card"]->value != manilha and params[1]->get_value() != manilha and 
								state["last_played_card"]->value == params[1]->get_value())
		draw = true;
	
	params[0]->plays_card(*params[1]); //faz o jogador jogar a carta
	*/
	
	//caso haja vitória, passa-se quem ganhou e com que carta, caso contrário informa o empate
	if( flag )
	{
		//rule.set_state( "last_played_card", value );
		//rule.set_state( "last_player", params[0] );
	}
	if( draw )
		//rule.set_state( "draw", 1 );
}

int play_card::send_my_message( vector<void*>& v )
{
	/*
	int* a = (int*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at(v.size()-2);
	dealer->send(*who, 1, a, sizeof(int));
	*/
}
