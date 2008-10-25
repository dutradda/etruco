/*
 * Truco.h
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
 
#ifndef TRUCO_H
#define TRUCO_H

#include "Player.h"
#include "Team.h"
#include "Deck.h"
#include "Rule.h"
#include "Card.h"

#include <gmodule.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

extern "C"

/**
 * The main class for the game Truco.
 */
class Truco
{
	public:
		/**
		 * Default Constructor
		 * 
		 * @param num_players
		 * 	The number of players.
		 * @param num_teams
		 * 	The number of teams, the default is two.
		 */
		Truco(int num_players, int num_teams );
		
		/**
		 * Destructor
		 */
		~Truco();
		
		/**
		 * Start a new hand in the game.
		 *
		 * @return
		 *  1 if start a new hand with sucess.	 
		 *  0 if isnt time to start a new hand.
		 */
		int start_hand();
	
		/**
		 * Start a new round in a hand.
		 *
		 * @return
		 *  1 if start a new round with sucess.	 
		 *  0 if isnt time to start a new round.
		 */
		int start_round();
	
		/**
		 * Finish the round and determines the winner.
		 *
		 * @param _player
		 *  The winner player.
		 *
		 * @return
		 *  1 if finish the round with sucess.
		 *  0 if all the players havent played yet.
		 *  -1 if has a draw round.
		 *  -n where n is a rule return.
		 */
		int finish_round( Player& _player );
		 
		/**
		 * Finish the hand and determines the winner.
		 *
		 * @param _team
		 *  The winner team.
		 *
		 * @return
		 *  1 if finish the hand with sucess.
		 *  0 if have rounds to be played.
		 *  -1 if has a draw hand.
		 *  -n where n is a rule return.
		 */
		int finish_hand( Team& _team );
		 
		/**
		 * Finish the game and determines the winner.
		 *
		 * @param _team
		 *  The winner team.
		 *
		 * @return
		 *  1 if finish the game with sucess.
		 *  0 if isnt time to finish the game.
		 */
		int finish_game( Team& _team );
	
		/**
		 * Receive a card played by a player.
		 *
		 * @param _card
		 *  The card played.
		 *
		 * @param _player
		 *  The player who played the card.
		 *
		 * @return
		 *  1 if the card was played with sucess.
		 *  0 if isnt time of this player to play the card.
		 *  -1 if the card dont belongs the player.
		 */
		int card_played( const Card& _card, const Player& _player );
		 
		/**
		 * Increases the bet.
		 *
		 * @param _team
		 *  The team who accepted the increase.
		 *
		 * @return
		 *  1 if the bet was increased with sucess.
		 *  0 if isnt time of this team to increase the bet.
		 */
		int betting_increase( const Team& _team );
		 
		/**
		 * Finish the hand by a betting increase rejected.
		 *
		 * @param _team
		 *  The team who rejected the increase.
		 *
		 * @return
		 *  1 if the betting increase was rejected with sucess.
		 *  0 if was nothing betting increase to reject.
		 */
		int betting_increase_reject( const Team& _team );
		 
		/**
		 * Loads a rule in the Truco to be processed.
		 *
		 * @param _rule
		 *  The rule name in the XML.
		 *
		 * @param _truco_type
		 *  The truco type of the rule.
		 * 
		 * @param _file
		 *  The xml file. Is optional.
		 *
		 * @return
		 *  1 if the rule was loaded with sucess.
		 *  0 if this rule dont exist.
		 *  -1 if the rule havent this truco type.
		 */
		int load_rule( const string& _rule, const string& _truco_type, const string& _file );
		 
		/**
		 * Loads a set of rules.
		 *
		 * @param _truco_type
		 *  The truco type of the rules.
		 *
		 * @return
		 *  1 if the set of rules was loaded with sucess.
		 *  0 if this truco type dont exist.
		 */
		int load_rules( const string& _truco_type );
	
	protected:
		vector <Player*> players; /**< The players of the game */
		vector <Team*> teams; /**< The teams of the game */
		Deck* deck; /**< The game's deck */
		
	
	private:
		vector <Rule> rules; /**< The rules loaded in the game */
		vector <GModule*> modules;
		
};

#endif
