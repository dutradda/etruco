#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void Pick_Vira::execute( vector<void*>& _data )
{
	card = dependencies["give_cards"].deck->get_card();
	manilhas = card->get_value();
}

int Pick_Vira::send_my_message( vector<void*>& _data )
{
	Dealer* dealer = _data.back();
	
	for( int i = 0; i < 4; i++ )
		dealer->send( i, 6, manilhas, sizeof(int) );
	 
	return 1;
}
