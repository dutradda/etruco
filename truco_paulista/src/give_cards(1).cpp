#include <string>
#include <vector>
#include "truco_paulista_rules.h"

void give_cards::execute( vector<void*>& v )
{
	int round = 5;
	int valor_mao = 1;
	int asks = 0;
	bool truco_accepted = false;
	bool truco_rejected = false;
	
	truco.get_deck()->shuffle();
	
	for(int i = 0; i < truco.get_players().size(); i++ )
		truco.get_players()[i].receive_cards( truco.get_deck()->get3cards() );

	v.insert( v.back(), /*server*/ );
	v.insert( v.size()-2, -1 );
}

int give_cards::send_my_message( vector<void*>& v )
{
	void* msg = (void*) v.at(0);
	Dealer* dealer = (Dealer*) v.back();
	int* who = (int*) v.at( v.size()-2 );
	dealer->send( *who, 1, msg, sizeof(int) ) ;
	return 1;
}
