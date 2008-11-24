#include <libtruco/Deck.h>
#include <iostream>
using namespace std;

int main( int argc, char** argv )
{
	int size = atoi(argv[1]);
	int suits = atoi(argv[2]);
	Deck deck = Deck(size, suits);
	Card* card;



	for( int j = 0; j < atoi(argv[3]); j++)
	{
		deck.shuffle();
		for( int i = 0; i < size*suits; i++)
		{
			Card* card = deck.get_card();
			cout << "Suit: " << card->get_suit() << ". Value: " << card->get_value() << endl;
		}
		cout << "------" << endl;
	}

	return 0;
}
