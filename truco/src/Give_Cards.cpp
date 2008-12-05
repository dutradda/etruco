#include <string>
#include <vector>
#include "truco_paulista_rules.h"

Give_Cards::Give_Cards( int _deck_size )
{
	deck = new Deck(_deck_size);
}

Give_Cards::~Give_Cards()
{
	delete deck;
}

void Give_Cards::execute( vector<void*>& _data )
{
	deck->shuffle();
	
	for(int i = 0; i < 12; i++ )
		cards.push_back(deck->get_card());
}

int Give_Cards::send_my_message( vector<void*>& _data )
{
	Dealer* dealer = (Dealer*) _data.back();
	char[6] cards_sended;
	
	vector<Card*>::iterator card_iter = cards.begin();
	for( int i = 0; i < 4; i++ )
	{
		for( int j = 0; j < 3; )
		{
			cards_sended[j] = (*card_iter)->get_value();
			cards_sended[++j] = (*card_iter)->get_suit();
			card_iter = cards.erase(card_iter);
		}
		dealer->send(i, 5, cards_sended, sizeof(char)*6);
	}

	return 1;
}
