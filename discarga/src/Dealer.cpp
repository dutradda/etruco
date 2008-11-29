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

#include "Dealer.h"

using namespace std;
using namespace ipcpp;
using namespace discarga;

Dealer::Dealer(const int& _port,	const std::string& _xml_file_name ) :
													Server( _port ), Action_Handler( _xml_file_name )
{	
	register_events();
}

int Dealer::do_action( const int& _act_id, vector<void*>& _data )
{
	map <int, Action>::iterator result = actions.find( _act_id );
	if( result != actions.end() )
	{
		for( map <string, Rule*>::iterator j = result->second.rules.begin(); j != result->second.rules.end(); j++ )
			apply_rule( j->second->get_name(), _data );
		
		void* data_send = _data.back();
		vector <pair <int, int> >* send_to = (vector <pair <int, int> >*) *(_data.end()-2);
		
		for( vector <pair <int, int> >::iterator j = send_to->begin(); j != send_to->end(); j++ )
			send( (*j).first, (*j).second, data_send );
			
		delete send_to;
		delete (char*) data_send;
		_data.pop_back();
		_data.pop_back();
		
		return 1;
	}
	else
		return 0;
}

int ipcpp::handle_messages_server_received( void* _server, int _event_type, void* _full_message )
{	
	Dealer* server = (Dealer*) _server;
	Ecore_Ipc_Event_Client_Data *full_message = (Ecore_Ipc_Event_Client_Data*) _full_message;
	
	vector<void*> data;
	data.push_back( full_message->data );
	return server->do_action( full_message->ref, data );
}
