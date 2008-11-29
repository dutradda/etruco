/*  
 * Action_Handler.cpp
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

#include "Action_Handler.h"

using namespace std;
using namespace discarga;

multimap <int, string>
Action_Handler::load_actions( const string& _attribute_name,
					const string& _attribute_value,
					const string& _xml_file_name )
{
	string __xml_file_name;
	vector <Node*> nodes;
	
	if( _xml_file_name == "" )
		__xml_file_name = xml_file_name;
	else
		__xml_file_name = _xml_file_name;
	
	nodes = XML_Parser::get_children_nodes( "action", __xml_file_name, _attribute_value, _attribute_name );
	
	multimap <int, string> actions_errors;
	
	if( nodes.size() == 0 )
	{
		actions_errors.insert( pair <int,string>( 0, "empty" ) );
		return actions_errors;
	}
	
	for( vector <Node*>::iterator i = nodes.begin(); i != nodes.end(); i++ )
	{
		Action action;
		action.id = atoi( (*i)->attributes["id"].c_str() );
		action.name = (*i)->attributes["name"];
		
		for( vector <Node*>::iterator j = (*i)->children.begin(); j != (*i)->children.end(); j++ )
			if( (*j)->name == "rule" )
			{
				if( rules.find( (*j)->attributes["name"] ) == rules.end() ) // se a regra nao estah carregada
				{
					actions_errors = load_rules_file( __xml_file_name,
													(*j)->attributes["type"], (*j)->attributes["name"] );
					if( !actions_errors.empty() )
						break;
				}		
				action.rules[ (*j)->attributes["name"] ] = rules[ (*j)->attributes["name"] ];
			}
		
		if( actions_errors.empty() )
			actions[action.id] = action;
	}
	
	return actions_errors;
}
