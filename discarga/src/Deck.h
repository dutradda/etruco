/*  
 * Deck.h
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
 
#ifndef DISCARGA_DECK_H
#define DISCARGA_DECK_H

#include "Card.h"

#include <vector>

namespace discarga
{
	/**
	 * The deck class.
	 */
	class Deck
	{
		public:
			/**
			 * Default Constructor.
			 *
			 * @param _size
			 *  The number of cards per suit.
			 */
			inline Deck( int _size, int _suits = 4 );
			
			/**
			 * Destructor.
			 */
			inline ~Deck();
			
			/**
			 * Shuffle the deck.
			 */
			void shuffle();
			
			/**
			 * Get a card from deck's.
			 */
			inline Card* get_card();
			
		private:
			int cards_geted;
			std::vector <Card*> cards; /**< The deck's cards */
	};
};

/**
* Constructor
*
* @param _size
* The card's numbers
*
* @param _suits
* The card's suits
*/
inline discarga::Deck::Deck(int _size, int _suits)
{	
	cards_geted = 0;
	
	for( int j = 0; j < _suits; j++ )
		for( int i = 0; i < _size; i++ )
			cards.push_back(new Card(i, j));
}

/**
* Destructor
*/
inline discarga::Deck::~Deck()
{
	for( std::vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++ )
		delete *i;
}

/**
* Get a card
* Move a pointer ("removing the card from deck")
*/
inline discarga::Card* discarga::Deck::get_card()
{
	if( cards.size() == cards_geted )
		return NULL;
		
	return *(cards.begin()+(cards_geted++));
}

#endif
