/*
 * Card_Game.h
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
 
#ifndef LIBCARDGAME_CARD_GAME_H
#define LIBCARDGAME_CARD_GAME_H

#include "Player.h"
#include "Team.h"
#include "Deck.h"
#include "Rule.h"
#include "Card.h"

#include <XML_Parser.h>
#include <Eina.h>
#include <string>
#include <vector>
#include <map>

using namespace libcardgame;

namespace libcardgame
{
	struct Module_Symbol
	{
		std::string name;
		std::string module_file_name;
		void* symbol;
	};

	/**
	 * The Card Game class.
	 */
	class Card_Game
	{
		public:
			/**
			 * Default Constructor
			 * 
			 * @param _num_team_players
			 * 	The number of players in each team.
			 * @param _num_teams
			 * 	The number of teams, the default is two.
			 */
			Card_Game(const int& _num_team_players,
						const int& _num_teams,
						const std::string& _xml_file_name );
			
			/**
			 * Destructor
			 */
			~Card_Game();
			 
			/**
			 * Loads rules.
			 *
			 * @param _xml_file_name
			 *  The xml file name where the rules are.
			 * 
			 * @param _attribute_name
			 *	 The rule attribute name pre-requisite.
			 * 
			 * @param _attribute_value
			 *  The rule attribute value pre-requisite.
			 * 
			 * @return
			 *  The multistd::map with the errors and rules.
			 *  The errors are:
			 *  -1 if the dependencies dont match.
			 *  -2 if the conflicts match.
			 *  -3 if the module of a rule function dont exist.
			 *  -4 if a rule function dont exist in the module.
			 */
			std::multimap <int, std::string>
			load_rules_file( const std::string& _xml_file_name,
							const std::string& _attribute_name = "",
							const std::string& _attribute_value = "" );
							
			/**
			 * Loads rules.
			 *
			 * @param _attribute_name
			 *	 The rule attribute name pre-requisite.
			 * 
			 * @param _attribute_value
			 *  The rule attribute value pre-requisite.
			 * 
			 * @return
			 *  The multistd::map with the errors and rules.
			 *  The errors are:
			 *  -1 if the dependencies dont match.
			 *  -2 if the conflicts match.
			 *  -3 if the module of a rule function dont exist.
			 *  -4 if a rule function dont exist in the module.
			 */
			std::multimap <int, std::string>
			load_rules( const std::string& _attribute_name = "",
							const std::string& _attribute_value = "" );
			
			/**
			 * Apply a rule.
			 * 
			 * @param _name
			 *  The rule to be applied.
			 * 
			 * @param _params
			 *  The params taken by the rule.
			 * 
			 * @return
			 *  1 if the rule was applied sucessful. 0 if the rule cant be aplied.
			 */
			int apply_rule( const std::string& _name, const std::vector <void*>& _params );
			
			/**
			 * Return the rules
			 */		
			inline std::vector <Rule*> get_rules() { return rules; };
			
			/**
			 * Return the players
			 */		
			inline std::vector <Player*> get_players() { return players; };
			
			/**
			 * Return the teams
			 */		
			inline std::vector <Team*> get_teams() { return teams; };
			
			/**
			 * Return the team of the player
			 */		
			Team* get_player_team( const Player* _player );
			
			/**
			 * Return the deck
			 */		
			inline Deck* get_deck() { return deck; };
		
		protected:
			std::vector <Player*> players; /**< The players of the game */
			std::vector <Team*> teams; /**< The teams of the game */
			Deck* deck; /**< The game's deck */
			
		
		private:
			std::string xml_file_name; // The name of the xml file
			XML_Parser xml_parser; // The xml document parser
			std::vector <Rule*> rules; // The rules loaded in the game
			std::vector <Eina_Module*> modules; // The modules where the rules functions are in
			
			/*
			 * Checks for conflicts with the rules already loaded.
			 * 
			 * @param _conflicts
			 *  The conflicts to check for.
			 * 
			 * @return
			 *	 1 if there is no conflicts.
			 *  0 if have conflicts.
			 */
			int check_rule_conflicts( const std::vector <Conflict>& _conflicts );
			
			/*
			 * Checks for dependencies with the rules already loaded.
			 * 
			 * @param _type
			 *  The type of the rules.
			 * 
			 * @param _dependencies
			 *  The dependencies to check for.
			 * 
			 * @param _rules_deps
			 *  The rules dependencies.
			 * 
			 * @return
			 *  1 if all dependencies are satisfied.
			 *  0 if are missing dependencies.
			 */
			int check_rule_dependencies( std::vector <Rule*>& _rules_deps,
												const std::string& _type,
												const std::vector <std::string>& _dependencies );
	};
};

#endif
