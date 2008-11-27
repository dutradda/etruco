/*
 * Client.cpp
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

#include "Client.h"
using namespace std;

ipcpp::Client::Client( const int& port, const string& _xml_file_name ) : Messages_Handler( _xml_file_name )
{
	ecore_init();
	ecore_ipc_init();
	
	server = ecore_ipc_server_connect( ECORE_IPC_REMOTE_SYSTEM, (char*) "localhost", port, NULL );
	
	ecore_event_handler_add( ECORE_IPC_EVENT_SERVER_ADD,
									handle_server_connect, this );
									
   ecore_event_handler_add( ECORE_IPC_EVENT_SERVER_DEL,
   								handle_server_disconnect, this );
   
   ecore_event_handler_add( ECORE_IPC_EVENT_SERVER_DATA,
   								handle_messages_client_received, this );
}

ipcpp::Client::~Client()
{
	ecore_ipc_server_del( server );
	
	ecore_ipc_shutdown();
	ecore_shutdown();
}

int ipcpp::Client::send_message( const int& _msg_id, void* _data )
{
	if( run_message( messages_to_send, _msg_id, _data ) )
		return ecore_ipc_server_send( server, 0, 0, _msg_id, 0, 0, _data, sizeof(_data) );
	else
		return 0;
}

int ipcpp::handle_server_connect( void* _client, int _event_type, void* _server )
{
	Client* client = (Client*) _client;
	Ecore_Ipc_Event_Server_Add* e_server = (Ecore_Ipc_Event_Server_Add*) _server;
	

	client->server = e_server->server;
	
	return 1;
}

int ipcpp::handle_server_disconnect( void* _client, int _event_type, void* _server )
{
	Client* client = (Client*) _client;
	Ecore_Ipc_Event_Server_Del* e_server = (Ecore_Ipc_Event_Server_Del*) _server;
	
	ecore_ipc_server_del( client->server );

	return 1;
}

int ipcpp::handle_messages_client_received( void* _client, int _event_type, void* _full_message )
{
	Client* client = (Client*) _client;
	Ecore_Ipc_Event_Server_Data *full_message = (Ecore_Ipc_Event_Server_Data*) _full_message;
	
	return client->run_message( client->messages_to_receive, full_message->ref, full_message->data );
}
