/*  
 * Action_Handler.h
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

#ifndef DISCARGA_ACTION_HANDLER_H
#define DISCARGA_ACTION_HANDLER_H

#include "Rule_Handler.h"

#include <string>
#include <vector>
#include <map>

namespace discarga
{
	class Action_Handler : public Rule_Handler
	{
		struct Action
		{
			int id;
			std::string name;
			std::map <std::string, Rule*> rules;
		};
		
		public:
			Action_Handler( const std::string& _xml_file_name ) : Rule_Handler( _xml_file_name ) { };
			
			std::multimap <int, std::string>
			load_actions( const std::string& _attribute_name = "",
						const std::string& _attribute_value = "",
						const std::string& _xml_file_name = "" );
			
			virtual int do_action( const int& _act_id, std::vector<void*>& _data ) = 0;
		
		protected:
			std::map <int, Action> actions;
	};
};

#endif
