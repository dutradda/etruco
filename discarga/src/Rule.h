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

#ifndef DISCARGA_RULE_H
#define DISCARGA_RULE_H

#include <string>
#include <vector>
#include <map>


namespace discarga
{
	class Conflict
	{
		friend class Rule_Handler;
		
		public:
			inline std::string get_name() { return name; }
			inline std::string get_type() { return type; }
		private:
			std::string name;
			std::string type;
	};
	
	struct Module_Symbol
	{
		std::string name;
		std::string module_file_name;
		void* symbol;
	};

	/**
	 * The game's rule.
	 */
	class Rule
	{
		friend class Rule_Handler;
		
		public:
			/**
			 * Constructor.
			 */
			inline Rule( const std::string& _name,
				const std::string& _type,
				const std::string& _description,
				const std::vector <Conflict>& _conflicts,
				std::map <std::string, Rule*> _dependencies );
			
			/**
			 * Default Constructor.
			 */
			Rule( ) { };
			
			/**
			 * Return the rule's name.
			 */
			inline std::string get_name() { return name; };
			
			/**
			 * Return the rule's id.
			 */
			inline int get_id() { return id; };
			
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
			inline std::map <std::string, Rule*> get_dependencies() { return dependencies; };
			
			/**
			 * Return the rule's module symbol.
			 */
			inline Module_Symbol get_module_symbol() { return module_symbol; };
			
			/**
			 * Execute the rule.
			 * 
			 * @param _data
			 *  The pure data received
			 */
			virtual int execute( std::vector<void*>& _data ) = 0;
			
			/**
			 * Send a message.
			 * 
			 * @param _data
			 *  The data received by the execute method plus specific datas.
			 */
			virtual int send_my_message( std::vector<void*>& _data ) = 0;
		
		protected:
			int id; /**< The rule's identification. */
			std::string name; /**< The rule's name. */
			std::string type; /**< The rule's type. */
			std::string description; /**< The rule's description. */
			std::vector <Conflict> conflicts; /**< Which rules this rule conflits. */
			std::map <std::string, Rule*> dependencies; /**< Which rules this rule depends. */
			Module_Symbol module_symbol; /**< The Module where are the instance of the rule. */
	};
};
inline discarga::Rule::Rule( const std::string& _name,
			const std::string& _type,
			const std::string& _description,
			const std::vector <discarga::Conflict>& _conflicts,
			std::map <std::string, Rule*> _dependencies )
{
	name = _name;
	type = _type;
	description = _description;
	conflicts = _conflicts;
	dependencies = _dependencies;
}

#endif
