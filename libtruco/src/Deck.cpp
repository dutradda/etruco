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
 
Deck::Deck(int _size)
{
	get_cards_count = 0;
	
	for( int i = 0; i < _size; i++ )
		for( int j = 0; j < 4; j++ )
			cards.push_back(new Card(i, j));
}

Deck::~Deck()
{
	int size = cards.size();
	for( int i = size-1; i >= 0; i-- )
	{
		delete cards[i];
		cards.pop_back();
	}
	
	size = cards_removed.size();
	for( int i = size-1; i >= 0; i-- )
	{
		delete cards_removed[i];
		cards_removed.pop_back();
	}
}

void Deck::shuffle()
{
	int size;
	
	// Inicia a contagem de cartas dadas
	get_cards_count = 0;
	
	// Recoloca as cartas retiradas do baralho
	size = cards_removed.size();
	for( int i = size-1; i >= 0; i-- )
	{
		cards.push_back( cards_removed[i] );
		cards_removed.pop_back();
	}
	
	srand( time( NULL ) );
	
	size = cards.size();
	int random;
	Card* aux;
	
	while( size < 1 )
	{
		random = ( rand() % size );
		size--;
		aux = cards[size];
		cards[size] = cards[random];
		cards[random] = aux;
	}
}

vector <Card*> Deck::get_3cards()
{
	vector <Card*> _cards;
	
	for(int i = get_cards_count; i < 3+get_cards_count; i++ )
		_cards.push_back(cards[i]);
	get_cards_count+=3;
	
	return _cards;
}

Card* Deck::get_card()
{
	Card* card = cards.back();
	cards.pop_back();
	
	cards_removed.push_back(card);
	
	return card;
}
