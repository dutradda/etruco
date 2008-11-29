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

#ifndef DISCARGA_PLAYER_H
#define DISCARGA_PLAYER_H

#include "Action_Handler.h"
#include "Card.h"

#include <string>
#include <vector>
#include <ipcpp/Client.h>

namespace discarga
{
	class Player : public ipcpp::Client, public Action_Handler
	{
		public:
			Player(const int& _port,
					const std::string& _host,
					const std::string& _xml_file_name );
			
			int do_action( const int& _act_id, std::vector<void*>& _data );
			
			/**
			 * Receive new cards.
			 *
			 * @param _cards
			 *  A std::vector with three cards.
			 */
			inline void receive_card( discarga::Card _card ) { cards.push_back( _card ); };
			
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
			int plays_card( const Card& _card );
			
			/**
			 * Get the player's cards.
			 *
			 * @return
			 *  The cards.
			 */
			inline std::vector <Card> get_cards() { return cards; };
		
		private:
			int id; /**< The id of the player */
			int team; /**< The team of the player */
			std::vector <discarga::Card> cards; /**< The player's cards */
	};
};

#endif
