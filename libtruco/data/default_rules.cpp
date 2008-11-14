#include <vector>
#include <string>
#include <Deck.h>

using namespace std;

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

void round_winner( Rule& rule, Truco truco, vector< void * > params )//states: round, team1, team2, winner, team1_points, team2_points
{	
	map <string, void*> state = rule.get_state();

	if( state["round"]->value == 0 or state["winner"]->value != 0 )
	{	
		state["round"]->value = 5; 	//state["player1"] state["player2"] state["winner"]
		state["winner"]->value = 0;
		state["team1_points"]->value = 0;
		state["team2_points"]->value = 0;
		state["team1"]->value = 0;
		state["team2"]->value = 0;
	}

	state["round"]->value--;
	if( state["team1"]->value == 0 )
		state["team1"]->value = rule.get_dependencies()["play_card"]->get_state("last_player");
	else if( state["team1"]->value != rule.get_dependencies()["play_card"]->get_state("last_player") )
		state["team2"]->value = rule.get_dependencies()["play_card"]->get_state("last_player");
		
	if( rule.get_dependencies()["play_card"]->get_state("draw") != 0 )
	{
		if( state["team1"]->value == rule.get_dependencies()["play_card"]->get_state("last_player") )
			state["team1_points"]->value=state["team1"]->value+state["round"]->value;
		else
			state["team2_points"]->value=state["team2"]->value+state["round"]->value;
			
		state["winner"]->value=rule.get_dependencies()["play_card"]->get_state("last_player");
	}
	else
	{
		state["winner"]->value=0;
		state["draw"]->value=true;
	}

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

void mao_winner( Rule& rule, Truco truco, vector< void * > params ) //states: winner, team1_points, team2_points
{
	//falta determinar quantos pontos a mão dá <depende da ask_truco>
	map <string, void*> state = rule.get_state();
	map <string, void*> state_round_winner = rule.get_dependencies()["round_winner"].get_state();
	
	//rule.set_state( "winner", rule.get_dependencies()["round_winner"]->get_state("winner"));

	if( state_round_winner["round"]->value == 3 )
	{
		if( state_round_winner["team1_points"]->value == 7 )
			state["winner"]->value = state_round_winner["team1"]->value;
		if( state_round_winner["team2_points"]->value == 7 )
			state["winner"]->value = state_round_winner["team2"]->value;
		bool draw = false;
	}
	else if( state_round_winner["team1_points"]->value == 0 and state_round_winner["team2_points"]->value == 0 )
			draw = true;
	else if( state_round_winner["team1_points"]->value > state_round_winner["team2_points"]->value )
			state["winner"]->value = state_round_winner["team1"]->value;
		 else
		 	state["winner"]->value = state_round_winner["team2"]->value;
}

void ask_truco( Rule& rule, Truco truco, vector< void * > params )
{


}

void game_winner( Rule& rule, Truco truco, vector< void * > params )
{
	rule.set_state( "winner", rule.get_dependencies()["mao_winner"]->get_state("winner") );
}

