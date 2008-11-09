#include <vector>
#include <string>
#include <Deck.h>

using namespace std;

map <string, int> a;
a["lala"] = 10;

void give_cards( Rule& rule, Truco truco, vector< void * > params )
{
	truco.get_deck()->shuffle();
	for(int i = 0; i < truco.get_players().size(); i++ )
		truco.get_players()[i].receive_cards( truco.get_deck()->get3cards() );
}

void pick_vira( Rule& rule, Truco truco, vector< void * > params )
{
	Card* vira = truco.get_deck()->get_card();
	int* value = new int;
	if( vira.get_value() != 10)
		*value = vira.get_value() + 1;
	else
		*value = 1;
	rule.set_state( "manilhas", value );
}

//Já define no estado quem ganhou.
void play_card( Rule& rule, Truco truco, vector< void * > params ) 	//params[0] = jogador e params[1] = carta do jogador
{									//states: last_played_card,last_player,draw
	map <string, void*> state = rule.get_state();
	int manilha = rule.get_dependencies()["pick_vira"]->get_state( "manilhas" );
	int* value = new int( params[1]->get_value() );
	bool flag = false;
	bool draw = false;
	rule.set_state( "draw", 0 );
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
	// faz o jogador jogar a carta
	params[0]->plays_card(*params[1]);
	
	if( flag )
	{
		rule.set_state( "last_played_card", value );
		rule.set_state( "last_player", params[0] );
	}
	if( draw )
		rule.set_state( "draw", 1 );
}

void round_winner( Rule& rule, Truco truco, vector< void * > params )//states: round, player1, player2, winner, who_is_player1, other_player
{	
	map <string, void*> state = rule.get_state();

//pode ser feita em mao_winner sem o if?
/*
	if( state["round"]->value == 0 or state["winner"]->value != 0 )
	{	
		state["round"]->value = 5; 	//state["player1"] state["player2"] state["winner"]
		state["winner"]->value = 0;
		state["player1"]->value = 0;
		state["player2"]->value = 0;
		state["who_is_player"]->value = 0;
		state["other_player"]->value = 0;
	}
*/

	state["round"]->value--;
	if( state["who_is_player1"]->value == 0 )
		state["who_is_player1"]->value = rule.get_dependencies()["play_card"]->get_state("last_player");
	else if( state["who_is_player1"]->value != rule.get_dependencies()["play_card"]->get_state("last_player") )
		state["other_player"]->value = rule.get_dependencies()["play_card"]->get_state("last_player");
	if( rule.get_dependencies()["play_card"]->get_state("draw") != 0 )
	{
		if( state["who_is_player1"]->value == rule.get_dependencies()["play_card"]->get_state("last_player") )
			state["player1"]->value=state["player1"]->value+state["round"]->value
		else
			state["player2"]->value=state["player2"]->value+state["round"]->value
	}

//isso é do mao_winner
/*
	if( state["round"]->value == 3 )
	{
		if( state["player1"]->value == 7 )
			state["winner"]->value = state["who_is_player"]->value;
		if( state["player2"]->value == 7 )
			state["winner"]->value = state["other_is_player"]->value;
		bool draw = false;
		if(( state["player1"]->value == 0 or state["player2"]->value == 0 ) and
							 (state["player1"]->value != 7 or state["player2"]->value == 7 ))
			draw = true;
*/

//tentativa anterior
/*
	if( state["winner1"]->value == 0 )
		rule.set_state( "winner1", rule.get_dependencies()["play_card"]->get_state("last_player") );
	else if( state["winner2"]->value == 0 )
		rule.set_state( "winner2", rule.get_dependencies()["play_card"]->get_state("last_player") );
	else if( state["winner"]->value == 0 )
		rule.set_state( "winner", rule.get_dependencies()["play_card"]->get_state("last_player") );
	
	if ( rule.get_dependencies()["play_card"]->get_state("draw") != 1 )
		if( state["winner1"]->value ==0  )
			rule.set_state( "winner1", rule.get_dependencies()["play_card"]->get_state("last_player") );
*/

}

void mao_winner( Rule& rule, Truco truco, vector< void * > params )
{
	rule.set_state( "winner", rule.get_dependencies()["round_winner"]->get_state("winner"));

}

void game_winner( Rule& rule, Truco truco, vector< void * > params )
{
	rule.set_state( "winner", rule.get_dependencies()["mao_winner"]->get_state("winner") );
}

