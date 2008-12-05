/*  
 * Deck.cpp
 *
 * Copyright 2008 Diogo Dutra Albuquerque <diogo.comp@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Library General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor Boston, MA 02110-1301,  USA
 */

#include "Deck.h"

#include <cstdlib>
using namespace discarga;
using namespace std;

/**
*This function shuffle the card's vector
*/

void Deck::shuffle()
{
	cards_geted = 0;
	
	int size = cards.size();
	int random;
	Card* temp;
	vector<Card*>::iterator randomized;
	srand( time(NULL) );
	
	for( vector<Card*>::iterator i = cards.end()-1; i > cards.begin(); i--, size-- )
	{
		random = ( rand() % size );
		randomized = (cards.begin()+random);
		temp = *i;
		*i = *randomized;
		*randomized = temp;
	}
}

