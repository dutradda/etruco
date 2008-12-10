#include <string.h>
#include <vector>
#include "truco_paulista_rules.h"

/*
 * Pela Player é enviada uma mensagem de jogada, composta por carta e jogador. Ao receber estes parâmetros, nesta classe é criado 
 * um registro contendo cada jogada realizada e ao mesmo tempo envia mensagens para todos os jogadores o conteúdo dessa jogada (Id_Message: 12).
 * Ao fim de 4 jogadas a round_winner será executada.
 */

void Play_Card::execute( vector<void*>& _data )
{
	strcpy( turn_params, _data.at(0) );
	short int i = move_params[0];
	registred_plays[i].player_id = turn_params[0];
	registred_plays[i].card_value = turn_params[1];
	registred_plays[i].card_suit = turn_params[2];
}

int Play_Card::send_my_message( vector<void*>& _data )
{
	Dealer* dealer = (Dealer*) _data.back();

	for ( int i = 0; i < 4; i++ )
		dealer->send( i, 12, turn_params, sizeof(char)*3 );

	return 1;
}
