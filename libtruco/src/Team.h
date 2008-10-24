/*  
 * Team.h
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
 
#ifndef TEAM_H
#define TEAM_H

#include "Player.h"

#include <vector>
using namespace std;

/**
 * The team who plays truco
 */
class Team
{
	public:
		/**
		 * Constructor
		 */
		Team( vector <Player*> _players ) : players( _players ) { };
		
		/**
		 * Get the player's cards.
		 *
		 * @return
		 *  A copy of the cards.
		 */
		vector <Player> get_players();
	
	private:
		vector <Player*> players; /**< The team's players */
};

#endif