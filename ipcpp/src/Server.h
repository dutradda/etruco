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
 
#ifndef IPCPP_SERVER_H
#define IPCPP_SERVER_H

#include <string>
#include <vector>

#include <Ecore.h>
#include <Ecore_Ipc.h>

namespace ipcpp
{
	int handle_client_connect( void* _server, int _event_type, void* _client );
	int handle_client_disconnect( void* _server, int _event_type, void* _client );
	int handle_messages_server_received( void* _server, int _event_type, void* _full_message );

	class Server
	{
		public:
			int send( const int& _client_id, const int& _msg_id, void* _data, const int& _size );
			
		protected:
			Server( const int& _port );
			
			~Server();
			
			void register_events( void* _data );
			
			Ecore_Ipc_Server* server;
			std::vector <Ecore_Ipc_Client*> clients;
			
			virtual int handle_message( const int& _msg_id, std::vector <void*> _data , const int& _who_sent ) { };
			
			friend int handle_client_connect( void* _server, int _event_type, void* _full_message );
			
			friend int handle_client_disconnect( void* _server, int _event_type, void* _full_message );
			
			friend int handle_messages_server_received( void* _data, int _event_type, void* _full_message );
	};
};
#endif
