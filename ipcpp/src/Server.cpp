/*
 * Server.cpp
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

#include "Server.h"

using namespace std;
using namespace ipcpp;

ipcpp::Server::Server( const int& port )
{
	ecore_init();
	ecore_ipc_init();
	
	server = ecore_ipc_server_add( ECORE_IPC_REMOTE_SYSTEM, "localhost", port, NULL );
}

ipcpp::Server::~Server()
{

	for( vector <Ecore_Ipc_Client*>::iterator i = clients.begin(); i != clients.end(); i++ )
		ecore_ipc_client_del(*i);

	ecore_ipc_server_del( server );
	
	ecore_ipc_shutdown();
	ecore_shutdown();
}

void ipcpp::Server::register_events( void* _data )
{
		
	ecore_event_handler_add( ECORE_IPC_EVENT_CLIENT_ADD,
									handle_client_connect, _data );
									
	ecore_event_handler_add( ECORE_IPC_EVENT_CLIENT_DEL,
							handle_client_disconnect, _data );
	
	ecore_event_handler_add( ECORE_IPC_EVENT_CLIENT_DATA,
							ipcpp::handle_messages_server_received, _data );
}

int ipcpp::Server::send( const int& _client_id, const int& _msg_id, void* _data, const int& _size )
{
		return ecore_ipc_client_send( clients.at(_client_id), 0, 0, _msg_id, 0, 0, _data, _size );
}

int ipcpp::handle_client_connect( void* _server, int _event_type, void* _client )
{
	Server* server = (Server*) _server;
	Ecore_Ipc_Event_Client_Add* e_client = (Ecore_Ipc_Event_Client_Add*) _client;
	
	server->clients.push_back( e_client->client );
	
	return 1;
}

int ipcpp::handle_client_disconnect( void* _server, int _event_type, void* _client )
{
	Server* server = (Server*) _server;
	Ecore_Ipc_Event_Client_Del* e_client = (Ecore_Ipc_Event_Client_Del*) _client;

	vector <Ecore_Ipc_Client*>::iterator client = find( server->clients.begin(),
																	server->clients.end(), e_client->client );
	
	if( client != server->clients.end() )
	{
		ecore_ipc_client_del( *client );
		server->clients.erase( client );
	}
	else
		return 0;

	return 1;
}
#include <iostream>
int ipcpp::handle_messages_server_received( void* _server, int _event_type, void* _full_message )
{	
	Server* server = (Server*) _server;
	Ecore_Ipc_Event_Client_Data *full_message = (Ecore_Ipc_Event_Client_Data*) _full_message;
	
	int i;
	for( i = 0; i < server->clients.size(); i++ )
		if ( server->clients.at(i) == full_message->client )
			break;
	
	vector<void*> data;
	data.push_back( full_message->data );
	return server->handle_message( full_message->ref, data, i );
}
