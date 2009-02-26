 /*  
 * Player.cpp
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

#include "Player.h"

using namespace std;
using namespace discarga;

Player::Player(const int& _port,
				const std::string& _host,
				const std::string& _xml_file_name ) : Client( _port, _host ), Rule_Handler( _xml_file_name )
{	
	register_events( this );
}

int Player::apply_rule( const int& _rule_id, vector<void*>& _data )
{
	for( map<string, Rule*>::iterator i = rules.begin(); i != rules.end(); i++ )
		if( i->second->get_id() == _rule_id )
			return apply_rule( i->first, _data );
	
	return 0;
}

int Player::apply_rule( const string& _rule_name, vector<void*>& _data )
{
	if( Rule_Handler::apply_rule( _rule_name, _data ) )
	{
		_data.push_back(this);
		return rules[_rule_name]->send_my_message( _data );
	}
	else
		return 0;
}

int Player::handle_message( const int& _msg_id, vector<void*> _data )
{
	apply_rule( _msg_id, _data );
}
