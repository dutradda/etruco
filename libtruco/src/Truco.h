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

#include <Eina.h>
#include <string>
#include <vector>
#include <map>
using namespace std;

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
		 *  -2 if the module of the rule function dont exist.
		 *  -3 if the rule function dont exist in the module.
		 *  -4 if the dependencies dont match.
		 *  -5 if the conflicts match.
		 */
		int load_rule( const string& _rule, const string& _truco_type, const string& _file );
		 
		/**
		 * Loads a set of rules.
		 *
		 * @param _rule
		 *	 The rule's name.
		 * 
		 * @param _truco_type
		 *  The truco type of the rules.
		 * 
		 * @param _file
		 *  The xml file where the rule is. Is a optional param.
		 * 
		 * @param _rule_errors
		 *  The vector with the errors and rules.
		 *  The errors are:
		 *  -4 if the dependencies dont match.
		 *  -5 if the conflicts match.
		 *
		 * @return
		 *  1 if the set of rules was loaded with sucess.
		 *  -1 if nothing rule was loaded.
		 *  -2 if the module of a rule function dont exist.
		 *  -3 if a rule function dont exist in the module.
		 */
		int
		load_rules( const string& _truco_type,
						const string& _file,
						multimap <int, string>& _rule_errors );
		
		/**
		 * Apply a rule.
		 * 
		 * @param _rule
		 *  The rule to be applied.
		 * 
		 * @param _params
		 *  The params taken by the rule.
		 * 
		 * @return
		 *  1 if the rule was applied sucessful. 0 if the rule cant be aplied.
		 */
		int apply_rule( Rule* _rule, vector <void*> _params );
		
		/**
		 * Apply rules by where_apply.
		 * 
		 * @param _where_apply
		 *  The group choosen to select rules.
		 * 
		 * @param _params
		 *  The params taken by the rules.
		 * 
		 * @param _returns
		 *  The returns of the rules applied.
		 * 
		 * @return
		 *  1 if all rules were applied sucessful. 0 if a rule cant be aplied.
		 */
		int apply_rules( const string& where_apply, vector <void*> _params );
		
		/**
		 * Return the rules
		 */		
		inline vector <Rule*> get_rules() { return rules; };
		
		/**
		 * Return the players
		 */		
		inline vector <Player*> get_players() { return players; };
		
		/**
		 * Return the teams
		 */		
		inline vector <Team*> get_teams() { return teams; };
		
		/**
		 * Return the deck
		 */		
		inline Deck* get_deck() { return deck; };
	
	protected:
		vector <Player*> players; /**< The players of the game */
		vector <Team*> teams; /**< The teams of the game */
		Deck* deck; /**< The game's deck */
		
	
	private:
		vector <Rule*> rules; /**< The rules loaded in the game */
		vector <Eina_Module*> modules; /**< The modules where the rules functions are in. */
		
		/**
		 * Checks for conflicts with the rules already loaded.
		 * 
		 * @param _conflicts
		 *  The conflicts to check for.
		 * 
		 * @return
		 *	 1 if there is no conflicts.
		 *  0 if have conflicts.
		 */
		int check_rule_conflicts( vector <conflict> _conflicts );
		
		/**
		 * Checks for dependencies with the rules already loaded.
		 * 
		 * @param _truco_type
		 *  The truco type of the rules.
		 * 
		 * @param _dependencies
		 *  The dependencies to check for.
		 * 
		 * @param _rules_deps
		 *  The rules dependencies.
		 * 
		 * @return
		 *  1 if all dependencies are satisfied.
		 *  2 if are missing dependencies.
		 */
		int check_rule_dependencies( string _truco_type,
											vector <string> _dependencies,
											vector <Rule*>& _rules_deps );
		
		/**
		 * Get rules by where they are appliable.
		 * 
		 * @param _where
		 *  Where the rules are appliable.
		 * 
		 * @return
		 *  The founded rules.
		 */
		vector <Rule*> get_rules_where_apply( const string& _where );
		
};

#endif
