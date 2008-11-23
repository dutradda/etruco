#include <vector>
#include <string>
#include <Deck.h>

using namespace std;

//dá as cartas e define primeiro round
void give_cards( Rule& rule, Truco truco, vector< void * > params )		//state: round, valor_mao, asks, truco_accepted e truco_rejected
{
	truco.get_deck()->shuffle();
	
	for(int i = 0; i < truco.get_players().size(); i++ )
		truco.get_players()[i].receive_cards( truco.get_deck()->get3cards() );
	
	//inicialização de estados que devem ser renovados a cada começo de mão
	rule.set_state( "round", 5 );
	rule.set_state[ "valor_mao", 1 );
	rule.set_state( "asks", 0 );
	rule.set_state( "truco_accepted", false );
	rule.set_state( "truco_rejected" , false );
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
void play_card( Rule& rule, Truco truco, vector< void * > params ) 		//states: last_played_card, last_player e draw
{																		//dependency states: manilhas
	map <string, void*> state = rule.get_state();
	
	int manilha = rule.get_dependencies()["pick_vira"]->get_state( "manilhas" );
	int* value = new int( params[1]->get_value() );	//params[0] = jogador e params[1] = carta do jogador
	bool flag = false;
	bool draw = false;
	
	rule.set_state( "draw", 0 );
	
	//verifica se houve vitória ou empate
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
	
	//caso haja vitória, passa-se quem ganhou e com que carta, caso contrário informa o empate
	if( flag )
	{
		rule.set_state( "last_played_card", value );
		rule.set_state( "last_player", params[0] );
	}
	if( draw )
		rule.set_state( "draw", 1 ); 
}

//define vencedor da rodada atribuindo pontuação (pontos por rodada: 1ª - 4, 2ª - 3, 3ª - 2)
void round_winner( Rule& rule, Truco truco, vector< void * > params )	//states: team1, team2, winner, team1_points, team2_points e draw
{																		//dependency states: last_player e draw
	map <string, void*> state = rule.get_state();
	map <string, void*> play_card_state = rule.get_dependencies["play_card"]->get_state();
	map <string, void*> give_cards_state = rule.get_dependencies["give_cards"]->get_state();

	rule.set_state( "draw", 0 );
	
	//inicializa estados a cada início de mão
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
}

//verifica se é mao de onze
void mao_onze( Rule& rule, Truco truco, vector< void * > params ) 		//states: mao_onze
{																		//dependency states: (team1_points e team2_points <da teams_points>)
	map <string, void*> teams_points_state = rule.get_dependencies["teams_points"]->get_state();
	
	rule.set_state( "mao_onze", false );

	if( teams_points_state["team1_points"] = 11 xor teams_points_state["team2_points"] = 11 )
	{
		rule.set_state( "mao_onze", true );
		rule.get_dependencies()["give_cards"]->set_state( "valor_mao", 3 );
	}
}

//verifica se é mao de ferro
void mao_ferro( Rule& rule, Truco truco, vector< void * > params ) 		//states: mao_ferro
{																		//dependency states: (team1_points e team2_points <da teams_points>)
	map <string, void*> teams_points_state = rule.get_dependencies["teams_points"]->get_state();
	
	rule.set_state( "mao_ferro", false );

	if( teams_points_state["team1_points"] = 11 and teams_points_state["team2_points"] = 11 ) 
		rule.set_state( "mao_ferro", true )
}

//suporte ao caso de aceite de truco e aumento de aposta (define quantos pontos a mao_winner dá)
void truco_accepted( Rule& rule, Truco truco, vector< void * > params )	//dependency states: asks , valor_mao e truco_accepted
{
	map <string, void*> state = rule.get_state();
	map <string, void*> give_cards_state = rule.get_dependencies()["give_cards"]->get_state();
	
	rule.get_dependencies()["give_cards"]->set_state( "truco_accepted", true);
	rule.get_dependencies()["give_cards"]->set_state( "asks", give_cards_state["asks"] + 1 );
	rule.get_dependencies()["give_cards"]->set_state( "valor_mao", 3*give_cards_state["asks"] );
}

//suporte ao caso de rejeite de truco (define quantos pontos a mao_winner dá)
void truco_rejected( Rule& rule, Truco truco, vector< void * > params )	//dependency states: valor_mao, asks e truco_rejected
{																		
	map <string, void*> state = rule.get_state();
	map <string, void*> truco_accepted_state = rule.get_dependencies()["truco_accepted"]->get_state();
	
	rule.get_dependencies()["give_cards"]->set_state( "truco_rejected", true);
	rule.get_dependencies()["give_cards"]->set_state( "asks", give_cards_state["asks"] + 1 );
	
	if ( give_cards_state["asks"] == 1 )
	else
		rule.get_dependencies()["give_cards"]->set_state( "valor_mao", 3*(truco_accepted_state["asks"] - 1) );
}

//define ganhador da mão de acordo com as pontuações por rodada e atribui pontuação por mão aos times.
void mao_winner( Rule& rule, Truco truco, vector< void * > params ) //states: winner, draw e num_mao
{																	//dependency states: valor_mao, round, team1, team2, (team1_points, team2_points <da round_winner>) e (team1_points, team2_points <da team_points>)
	map <string, void*> state = rule.get_state();
	map <string, void*> give_cards_state = rule.get_dependencies()["give_cards"]->get_state();
	map <string, void*> round_winner_state = rule.get_dependencies()["round_winner"]->get_state();
	map <string, void*> truco_accepted_state = rule.get_dependencies()["truco_accepted"]->get_state();
	map <string, void*> teams_points_state = rule.get_dependencies()["teams_points"]->get_state();
	
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
			//teams_points_state["team1_points"] += truco_accepted_state["valor_mao"];
		else
			rule.get_dependencies()["teams_points"]->set_state("team2_points", teams_points_state["team2_points"] + give_cards_state["valor_mao"] + state["cont_draw"] );
			//teams_points_state["team2_points"] += truco_accepted_state["valor_mao"];
		rule.get_dependencies()["teams_points"]->set_state( "cont_draw", 0 );
	}
	
	rule.set_state( "num_mao" , state["num_mao"] + 1 );
}

//define ganhador do jogo
void game_winner( Rule& rule, Truco truco, vector< void * > params )	//states: winner
{																		//dependency states: team1_points <da teams_points>, team1 e team2
	map <string, void*> state = rule.get_state();
	map <string, void*> teams_points_state = rule.get_dependencies()["teams_points"]->get_state();
	map <string, void*> mao_winner_state = rule.get_dependencies()["mao_winner"]->get_state();
	
	if ( teams_points_state["team1_points"] >= 12  )
		rule.set_state( "winner", mao_winner_state["team1"] );
	else
		rule.set_state( "winner", mao_winner_state["team2"] );
}
