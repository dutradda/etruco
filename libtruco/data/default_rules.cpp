#include <vector>
#include <string>
#include <Deck.h>

using namespace std;

//dá as cartas
void give_cards( Rule& rule, Truco truco, vector< void * > params )		
{
	truco.get_deck()->shuffle();
	
	for(int i = 0; i < truco.get_players().size(); i++ )
		truco.get_players()[i].receive_cards( truco.get_deck()->get3cards() );
}

//define manilha
void pick_vira( Rule& rule, Truco truco, vector< void * > params )		//state: manilhas
{
	Card* vira = truco.get_deck()->get_card();
	int* value = new int;

	if( vira.get_value() != 10)
		*value = vira.get_value() + 1;
	else
		*value = 1;

	rule.set_state( "manilhas", value );
}

//jogada de carta, definindo vitória ou empate em relação à jogada anterior
void play_card( Rule& rule, Truco truco, vector< void * > params ) 		//states: last_played_card, last_player, draw
{																		//dependency_states: manilhas
	map <string, void*> state = rule.get_state();
	
	int manilha = rule.get_dependencies()["pick_vira"]->get_state( "manilhas" );
	int* value = new int( params[1]->get_value() );	//params[0] = jogador e params[1] = carta do jogador
	bool flag = false;
	bool draw = false;
	
	rule.set_state( "draw", 0 );
	
	if( state["last_played_card"]->value == 0 ) //verifica se houve vitória ou empate
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
	
	if( flag ) //caso haja vitória, passa quem ganhou e com que carta, caso contrário informa o empate
	{
		rule.set_state( "last_played_card", value );
		rule.set_state( "last_player", params[0] );
	}
	if( draw )
		rule.set_state( "draw", true );
}

//define vencedor da rodada atribuindo pontuação (fictícia) por rodada (pontos: 1ª - 4, 2ª - 3, 3ª - 2)
void round_winner( Rule& rule, Truco truco, vector< void * > params )	//states: round, team1, team2, winner, team1_points, team2_points, draw
{																		//dependency_states: last_player, draw
	map <string, void*> state = rule.get_state();
	void* last_player = rule.get_dependencies()["play_card"]->get_state("last_player");
	int* draw = rule.get_dependencies()["play_card"]->get_state("draw");
	
	if( state["round"] == 0 or state["winner"] != 0 )
	{	
		rule.set_state( "draw", 0);
		rule.set_state( "round", 5 );
		rule.set_state( "winner", 0 ) ;
		rule.set_state( "team1_points", 0 );
		rule.set_state( "team2_points", 0 );
		rule.set_state( "team1", 0 );
		rule.set_state( "team2", 0 );
	}

	rule.set_state( "round", state["round"]-1 );
	
	//last_player é um jogador, não um time!
	if( state["team1"] == 0 )
		rule.set_state( "team1", last_player );
	else if( state["team1"] != last_player )
		rule.set_state( "team2", last_player );
		
	//informa vencedor e pontuação (fictícia) pela rodada
	if( draw )
	{
		rule.set_state( "winner", 0 );
		rule.set_state( "draw", 1 );
	}
	else
	{
		if( state["team1"] == last_player )
			rule.set_state( "team1_points", state["team1_points"] + state["round"] );
		else
			rule.set_state( "team2_points", state["team2_points"] + state["round"] );
			
		rule.set_state( "winner", last_player );
	}
}

//verifica se é mao de onze
void mao_onze( Rule& rule, Truco truco, vector< void * > params ) 		//states: mao_onze
{																		//dependency_states: team1_points, team2_points (da teams_points)
	map <string, void*> teams_points_state = rule.get_dependencies["teams_points"]->get_state();
	
	rule.set_state( "mao_onze", false );

	if( teams_points_state["team1_points"] = 11 xor teams_points_state["team2_points"] = 11 ) 
		rule.set_state( "mao_onze", true );
}

//verifica se é mao de ferro
void mao_ferro( Rule& rule, Truco truco, vector< void * > params ) 		//states: mao_ferro
{																		//dependency_states: team1_points, team2_points (da teams_points)
	map <string, void*> teams_points_state = rule.get_dependencies["teams_points"]->get_state();
	
	rule.set_state( "mao_ferro", false );

	if( teams_points_state["team1_points"] = 11 and teams_points_state["team2_points"] = 11 ) 
		rule.set_state( "mao_ferro", true )
}

//suporte ao caso de aceite de truco e aumento de aposta (define quantos pontos a mao_winner dá)
void truco_accepted( Rule& rule, Truco truco, vector< void * > params ) //states: asks, valor_mao
{																		//dependency_states: mao_onze
	map <string, void*> state = rule.get_state();
	
	rule.set_state( "asks", 0 );
				
	if ( state["mao_onze"] or asks == 1 )
		rule.set_state( "valor_mao", 3 );
	else if (asks > 1)
			rule.set_state( "valor_mao", 3*asks );

	rule.set_state( "valor_mao", 1 );
	rule.set_state( "asks", state["asks"] + 1 );
}

//suporte ao caso de rejeite de truco
void truco_rejected( Rule& rule, Truco truco, vector< void * > params )
{
	map <string, void*> state = rule.get_state();

}

//define ganhador da mão de acordo com as pontuações por rodada (fictícias) e atribui pontuação aos times.
void mao_winner( Rule& rule, Truco truco, vector< void * > params ) //states: winner, team1_points, team2_points, draw
{																	//dependency_states: asks, valor_mao, round, team1, team2, winner (da round_winner), team1_points, team2_points (da teams points)
	map <string, void*> state = rule.get_state();
	map <string, void*> round_winner_state = rule.get_dependencies()["round_winner"]->get_state();
	map <string, void*> truco_accepted_state = rule.get_dependencies()["truco_accepted"]->get_state();
	map <string, void*> teams_points_state = rule.get_dependencies()["teams_points"]->get_state(); //diferente das demais por teams_poinsts não ser função
	
	//define se há vencedor e quem é 
	if( round_winner_state["round"] == 3 ) //para 2 rodadas
	{
		if( round_winner_state["team1_points"] == 7 )
			rule.set_state( "winner", round_winner_state["team1"] );
		if( round_winner_state["team2_points"] == 7 )
			rule.set_state( "winner", round_winner_state["team2"] );
		rule.set_state( "draw", 0 );
	}
	else if( round_winner_state["team1_points"] == 0 and round_winner_state["team2_points"] == 0 ) //para 3 rodadas
			rule.set_state( "draw", 1);
	else if( round_winner_state["team1_points"] > round_winner_state["team2_points"] )
			rule.set_state( "winner", round_winner_state["team1"] );
		 else
		 	rule.set_state( "winner", round_winner_state["team2"] );
	
	if ( state["draw"] ) //atribuição de pontuação
//O QUE FAZER QUANDO A MÃO DÁ EMPATE?!	
	else if( state["winner"] == round_winner_state["team1"] )
			rule.get_dependencies()["teams_points"]->set_state("team1_points", teams_points_state["team1_points"] + truco_accepted_state["valor_mao"] );
			//teams_points_state["team1_points"] += truco_accepted_state["valor_mao"];
		else
			rule.get_dependencies()["teams_points"]->set_state("team2_points", teams_points_state["team2_points"] + truco_accepted_state["valor_mao"] );
			//teams_points_state["team2_points"] += truco_accepted_state["valor_mao"];
}

//define ganhador do jogo
void game_winner( Rule& rule, Truco truco, vector< void * > params )
{
	map <string, void*> state = rule.get_state();
	map <string, void*> mao_winner_state = rule.get_dependencies()["mao_winner"]->get_state();
}

