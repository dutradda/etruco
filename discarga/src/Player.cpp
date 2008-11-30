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
	register_events();
	
	ecore_event_handler_add( ECORE_IPC_EVENT_SERVER_DATA,
 								ipcpp::handle_messages_client_received, this );
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
		void* data_send = _data.back();
		
		int* msg_size = (int*) *(_data.end()-3);
		
		int* msg_to_send = (int*) *(_data.end()-2);
		if( *msg_to_send != -1 )
			send( *msg_to_send, data_send, *msg_size );
		
		delete msg_size;
		delete msg_to_send;
		delete (char*) data_send;
		_data.pop_back();
		_data.pop_back();
		
		return 1;
	}
	else
		return 0;
}

int Player::plays_card( const Card& _card )
{
	if( cards.empty() )
		return -1;
	
	vector<Card>::iterator result = find( cards.begin(), cards.end(), _card);		
	if( result != cards.end() )
		cards.erase( result );
	else
		return 0;

	return 1;
}

int ipcpp::handle_messages_client_received( void* _client, int _event_type, void* _full_message )
{
	Player* player = (Player*) _client;
	Ecore_Ipc_Event_Server_Data *full_message = (Ecore_Ipc_Event_Server_Data*) _full_message;
	
	vector<void*> data;
	data.push_back( full_message->data );
	return player->apply_rule( full_message->ref, data );
}
