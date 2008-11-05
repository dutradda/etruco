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

void play_card( Rule& rule, Truco truco, vector< void * > params ) //Considerando params[0] como o jogador e params[1] como carta do jogador
{	
	map <string, void*> state = rule.get_state();
	int manilha = rule.get_dependencies()["pick_vira"]->get_state( "manilhas" );
	int* value = new int( params[1]->get_value() );
	bool flag = false;
	
	if( state["last_played_card"]->value == 0 )
		flag = true;
	else if( state["last_played_card"]->value != manilha and params[1]->get_value() == manilha )
		flag = true;
	else if( (state["last_played_card"]->value == manilha and params[1]->get_value() == manilha) and
										 	state["last_played_card"]->suit < params[1]->get_suit() )
		flag = true;
	else if( state["last_played_card"]->value != manilha and
											state["last_played_card"]->value < params[1]->get_value() )
		flag = true;
	
	// faz o jogador jogar a carta
	params[0]->plays_card(*params[1]);
	
	if( flag )
	{
		rule.set_state( "last_played_card", value );
		rule.set_state( "last_player", params[0] );
	}
}

void round_winner( Rule& rule, Truco truco, vector< void * > params )
{
	rule.set_state( "winner", rule.get_dependencies()["play_card"]->get_state("last_player") );
}

void mao_winner( Rule& rule, Truco truco, vector< void * > params )
{
	rule.set_state( "winner", )
}




