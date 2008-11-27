/*  
 * Player.h
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
 
#ifndef LIBCARDGAME_PLAYER_H
#define LIBCARDGAME_PLAYER_H

#include "Card.h"

#include <vector>

namespace libcardgame
{
	/**
	 * The player class.
	 */
	class Player
	{
		public:
			/**
			 * Default Constructor
			 */
			inline Player( ) { };
		
			/**
			 * Constructor
			 *
			 * @param _cards
			 *  The new cards of the player.
			 */
			inline Player( std::vector <Card*> _cards ) { cards = _cards; };
		
			/**
			 * Get the player's cards.
			 *
			 * @return
			 *  The cards.
			 */
			inline std::vector <Card*> get_cards() { return cards; };
			
			/**
			 * Play a card.
			 *
			 * @param _card
			 *  The card will played.
			 *
			 * @return
			 *  1 if the card was played with sucess.
			 *  0 if the player dont have the card.
			 *  -1 if the player dont have any card.
			 */
			inline int plays_card( Card& _card );
			
			/**
			 * Receive new cards.
			 *
			 * @param _cards
			 *  A std::vector with three cards.
			 */
			inline void receive_cards( std::vector <Card*> _cards ) { cards = _cards; };
		
		private:
			std::vector <Card*> cards; /**< The player's cards */
	};
};
 
inline int libcardgame::Player::plays_card( Card& _card )
{
	if( cards.empty() )
		return -1;
	
	for( std::vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
	{
		if( _card == *(*i) )
		{
			cards.erase(i);
			return 1;
		}
	}
	
	return 0;
}
 
#endif
