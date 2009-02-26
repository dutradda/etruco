/*
 * Rule_Handler.h
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
 
#ifndef DISCARGA_RULE_HANDLER_H
#define DISCARGA_RULE_HANDLER_H

#include "Rule.h"

#include <XML_Parser.h>
#include <eina-0/Eina.h>
#include <string>
#include <vector>
#include <map>

namespace discarga
{
	/**
	 * The Card Game class.
	 */
	class Rule_Handler
	{	
		public:
			/**
			 * Default Constructor
			 * 
			 * @param _xml_file_name
			 * The name of the xml file where are the rules.
			 */
			Rule_Handler( const std::string& _xml_file_name );
			
			/**
			 * Destructor
			 */
			~Rule_Handler();
			 
			/**
			 * Loads rules.
			 *
			 * @param _xml_file_name
			 * The xml file name where the rules are.
			 * 
			 * @param _type
			 *	The truco type of the rule.
			 * 
			 * @param _name
			 * The name of the rule.
			 * 
			 * @return
			 * The multistd::map with the errors and rules.
			 * @n The errors are:
			 *  - -1 if the dependencies dont match.
			 *  - -2 if the conflicts match.
			 *  - -3 if the module of a rule function dont exist.
			 *  - -4 if a rule function dont exist in the module.
			 *
			 */
			std::multimap <int, std::string>
			load_rules_file( const std::string& _xml_file_name,
							const std::string& _type = "",
							const std::string& _name = "" );
							
			/**
			 * Loads rules.
			 * 
			 * @param _type
			 * The truco type of the rule.
			 * 
			 * @param _name
			 * The name of the rule.
			 * 
			 * @return
			 * The multistd::map with the errors and rules.
			 * @n The errors are:
			 *  - -1 if the dependencies dont match.
			 *  - -2 if the conflicts match.
			 *  - -3 if the module of a rule function dont exist.
			 *  - -4 if a rule function dont exist in the module.
			 */
			std::multimap <int, std::string>
			load_rules( const std::string& _type = "",
							const std::string& _name = "" );
			
			/**
			 * Apply a rule.
			 * 
			 * @param _name
			 * The rule to be applied.
			 * 
			 * @param _data
			 * The params taken by the rule.
			 * 
			 * @return
			 * 1 if the rule was applied sucessful. 0 if the rule cant be aplied.
			 */
			virtual int apply_rule( const std::string& _name, std::vector <void*>& _data );
			
			/**
			 * Unload a rule.
			 *
			 * @param _name
			 * The rule's name.
			 */
			int unload_rule( const std::string& _name );
			
			/**
			 * Unload rules by a type.
			 *
			 * @param _type
			 * The rules's type.
			 */
			int unload_rule_type( const std::string& _type );
			
			/** Return the rules loaded. */
			inline std::map <std::string, Rule*> get_rules() { return rules; }
		
		protected:
			std::string xml_file_name; /**< The name of the xml file. */
			std::map <std::string, Rule*> rules; /**< The rules loaded in the game. */
			std::vector <Eina_Module*> modules; /**< The modules where the rules functions are in. */
			
			/**
			 * Check for conflicts.
			 *
			 * @param _conflicts
			 * Vector that have a rules conflicts's list.
			 * 
			 * @param _name
			 * The name of the rule that are checking the conflicts.
			 */
			int check_rule_conflicts( const std::vector <Conflict>& _conflicts, const std::string& _name );
			
			/**
			 * Check the rule's dependencies.
			 *
			 * @param _rules_deps
			 * A vector of pointers to the rule dependencies. This is a return parameter.
			 *
			 * @param _type
			 * The rules's type.
 			 * 
			 * @param _dependencies
			 * Vector with dependencies to check.
			 * 
			 * @param _xml_file_name
			 * The xml file name where the rules are.
			 */
			int check_rule_dependencies( std::map <std::string, Rule*>& _rules_deps,
												const std::string& _type,
												const std::vector <std::string>& _dependencies,
												const std::string& _xml_file_name );
	};
};

#endif
