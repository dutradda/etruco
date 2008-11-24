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
using namespace std;

namespace libcardgame
{
	struct Conflict
	{
		string name;
		string type;
	};

	/**
	 * The game's rule
	 */
	class Rule
	{
		public:
			/**
			 * Constructor
			 */
			inline Rule( const string& _name,
				const string& _type,
				const string& _description,
				const vector <Conflict>& _conflicts,
				vector <Rule*> _dependencies,
				void* _callback );
				
			/**
			 * Sets rule's callback state
			 */
			inline void set_state( string _name, void* _value )  { state[_name.c_str()] = _value; };
			
			/**
			 * Return the rule's name
			 */
			inline string get_name() { return name; };
			
			/**
			 * Return the rule's type
			 */
			inline string get_type() { return type; };
			
			/**
			 * Return the rule's description
			 */
			inline string get_description() { return description; };
			
			/**
			 * Return the rule's conflicts
			 */
			inline vector <Conflict> get_conflicts() { return conflicts; };
			
			/**
			 * Return the rule's dependencies
			 */
			inline vector <Rule*> get_dependencies() { return dependencies; };
			
			/**
			 * Return the a map of rule's dependencies
			 */
			inline map <string, Rule*> get_dependencies_map();
			
			/**
			 * Return the rule's callback
			 */
			inline void* get_callback() { return callback; };
			
			/**
			 * Return the rule's callback state
			 */
			inline map <string, void*> get_state()  { return state; };
		
		private:
			string name; /**< The rule's name */
			string type; /**< The rule's type */
			string description; /**< The rule's description */
			vector <Conflict> conflicts; /**< Which rules this rule conflits */
			vector <Rule*> dependencies; /**< Which rules this rule depends */
			void* callback; /**< The function callback to the rule */
			map <string, void*> state; /**< The variables defines the rule's state */
	};
};
inline Rule::Rule( const string& _name,
			const string& _type,
			const string& _description,
			const vector <Conflict>& _conflicts,
			vector <Rule*> _dependencies,
			void* _callback )
{
	name = _name;
	type = _type;
	description = _description;
	conflicts = _conflicts;
	dependencies = _dependencies;
	callback = _callback;
}

inline map <string, Rule*> Rule::get_dependencies_map()
{
	map <string, Rule*> _return;
	
	for( vector<Rule*>::iterator i = dependencies.begin(); i != dependencies.end(); i++ )
		_return[(*i)->get_name()] = *i;
	
	return _return;
}

#endif
