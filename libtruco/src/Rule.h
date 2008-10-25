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
 
#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>
#include <map>
using namespace std;

/**
 * The truco's rule
 */
class Rule
{
	public:
		/**
		 * Constructor
		 */
		Rule( string _name,
			string _truco_type,
			string _description,
			string _where_apply,
			string _cb_name,
			vector <string> _conflicts,
			vector <string> _dependencies,
			string _file);
		
		/**
		 * Return the rule's name
		 */
		inline string get_name() { return name; };
		
		/**
		 * Return the rule's truco type
		 */
		inline string get_truco_type() { return truco_type; };
		
		/**
		 * Return the rule's description
		 */
		inline string get_description() { return description; };
		
		/**
		 * Return where the rule applies
		 */
		inline string get_where_apply() { return where_apply; };
		
		/**
		 * Return the rule's conflicts
		 */
		inline vector <string> get_conflicts() { return conflicts; };
		
		/**
		 * Return the rule's dependencies
		 */
		inline vector <string> get_dependencies() { return dependencies; };
		
		/**
		 * Return the rule's callback name
		 */
		inline string get_cb_name() { return cb_name; };
		
		/**
		 * Return the rule's callback state
		 */
		inline map <string, void*> get_state()  { return state; };
		
		int ( *callback )( vector <void*> ); /**< The function callback to the rule */
	
	private:
		string name; /**< The rule's name */
		string truco_type; /**< The rule's truco type */
		string description; /**< The rule's description */
		string where_apply; /**< Which game part this rule is appliable */
		string cb_name; /**< The callback's name */
		vector <string> conflicts; /**< Which rules this rule conflits */
		vector <string> dependencies; /**< Which rules this rule depends */
		string file; /**< The library file contain the callback */
		map <string, void*> state; /**< The variables defines the rule's state */
};

#endif
