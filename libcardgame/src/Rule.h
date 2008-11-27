/*  
 * Rule.h
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

#ifndef LIBCARDGAME_RULE_H
#define LIBCARDGAME_RULE_H

#include <string>
#include <vector>
#include <map>


namespace libcardgame
{
	class Conflict
	{
		friend class Card_Game;
		
		public:
			inline std::string get_name() { return name; }
			inline std::string get_type() { return type; }
		private:
			std::string name;
			std::string type;
	};

	/**
	 * The game's rule.
	 */
	class Rule
	{
		friend class Card_Game;
		
		public:
			/**
			 * Constructor.
			 */
			inline Rule( const std::string& _name,
				const std::string& _type,
				const std::string& _description,
				const std::vector <Conflict>& _conflicts,
				std::vector <Rule*> _dependencies );
				
			/*
			 * Sets rule's callback state
			 */
			//inline void set_state( std::string _name, void* _value )  { state[_name.c_str()] = _value; };
			
			/**
			 * Return the rule's name.
			 */
			inline std::string get_name() { return name; };
			
			/**
			 * Return the rule's type.
			 */
			inline std::string get_type() { return type; };
			
			/**
			 * Return the rule's description.
			 */
			inline std::string get_description() { return description; };
			
			/**
			 * Return the rule's conflicts.
			 */
			inline std::vector <Conflict> get_conflicts() { return conflicts; };
			
			/**
			 * Return the rule's dependencies.
			 */
			inline std::vector <Rule*> get_dependencies() { return dependencies; };
			
			/**
			 * Return the a std::map of rule's dependencies.
			 */
			inline std::map <std::string, Rule*> get_dependencies_map();
			
			/**
			 * Execute the rule.
			 * 
			 * @param _card_game
			 *  The Card Game are executing the rule.
			 * 
			 * @param _params
			 *  The parameters of the execution.
			 */
			virtual int execute( void*  _card_game, std::vector<void*> _params ) = 0;
			
			/**
			 * Return the rule's state.
			 */
			inline std::map <std::string, void*> get_state()  { return state; };
		
		private:
			std::string name; /**< The rule's name */
			std::string type; /**< The rule's type */
			std::string description; /**< The rule's description */
			std::vector <Conflict> conflicts; /**< Which rules this rule conflits */
			std::vector <Rule*> dependencies; /**< Which rules this rule depends */
			std::map <std::string, void*> state; /**< The variables defines the rule's state */
	};
};
inline libcardgame::Rule::Rule( const std::string& _name,
			const std::string& _type,
			const std::string& _description,
			const std::vector <libcardgame::Conflict>& _conflicts,
			std::vector <libcardgame::Rule*> _dependencies )
{
	name = _name;
	type = _type;
	description = _description;
	conflicts = _conflicts;
	dependencies = _dependencies;
}

inline std::map <std::string, libcardgame::Rule*> libcardgame::Rule::get_dependencies_map()
{
	std::map <std::string, libcardgame::Rule*> _return;
	
	for( std::vector<libcardgame::Rule*>::iterator i = dependencies.begin(); i != dependencies.end(); i++ )
		_return[(*i)->get_name()] = *i;
	
	return _return;
}

#endif
