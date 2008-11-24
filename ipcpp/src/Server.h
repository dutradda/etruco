/*
 * Server.h
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
 
#ifndef LIBTRUCONET_SERVER_H
#define LIBTRUCONET_SERVER_H

#include <Messages_Handler.h>
#include <Ecore.h>
#include <Ecore_Ipc.h>

int handle_client_connect( void* _server, int _event_type, void* _client );
int handle_client_disconnect( void* _server, int _event_type, void* _client );
int handle_messages_server_received( void* _server, int _event_type, void* _full_message );

class Server : public Messages_Handler
{
	public:
		Server( const int& _port, const string& _xml_file_name );
		
		~Server();
		
		int send_message( const int& _client, const int& _msg_id, void* _data );
		
	private:
		Ecore_Ipc_Server* server;
		vector <Ecore_Ipc_Client*> clients;
		
		friend int handle_client_connect( void* _server, int _event_type, void* _full_message );
		
		friend int handle_client_disconnect( void* _server, int _event_type, void* _full_message );
		
		friend int handle_messages_server_received( void* _data, int _event_type, void* _full_message );
};

#endif
