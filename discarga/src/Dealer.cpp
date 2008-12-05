/*  
 * Dealer.cpp
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

#include <vector>


#include "Dealer.h"

using namespace std;
using namespace discarga;

/**
* Constructor
*
* @param _port 
* Port's number to connect
*
* @param _xml_file_name
* The xml file name where the rules are.
*/
Dealer::Dealer(const int& _port,	const std::string& _xml_file_name ) :
													Server( _port ), Rule_Handler( _xml_file_name )
{	 
	register_events( this );
}

/**
* Apply the rule throught name
*
* @param _rule_name
* Rules's name
*
* @param _data
* Data's vector
*
* @param _who_sent
* Id of who sent the message
*/
int Dealer::apply_rule( const int& _rule_id, vector<void*>& _data, const int& _who_sent )
{
	for( map<string, Rule*>::iterator i = rules.begin(); i != rules.end(); i++ )
		if( i->second->get_id() == _rule_id )
			return apply_rule( i->first, _data, _who_sent );
	
	return 0;
}

/**
* Apply the rule throught rule's id
*
* @param _rule_id
* Rules's id
*
* @param _data
* Data's vector
*
* @param _who_sent
* Id of who sent the message
*/
int Dealer::apply_rule( const string& _rule_name, vector<void*>& _data, const int& _who_sent )
{
	if( Rule_Handler::apply_rule( _rule_name, _data ) )
	{
		_data.push_back( (void*) &_who_sent );
		_data.push_back( this );
		return rules[_rule_name]->send_my_message( _data );
	}
	else
		return 0;
}

/**
* Message colector
*
* @param _msg_id
* Message's id
*
* @param _data
* Data's vector
*
* @param _who_sent
* Id of who sent the message
*/
int Dealer::handle_message( const int& _msg_id, vector<void*> _data, const int& _who_sent )
{
	apply_rule( _msg_id, _data, _who_sent );
}
