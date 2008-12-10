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
 
#ifndef IPCPP_CLIENT_H
#define IPCPP_CLIENT_H

#include <string>
#include <vector>

#include <Ecore.h>
#include <Ecore_Ipc.h>

namespace ipcpp
{
	int handle_server_connect( void* _server, int _event_type, void* _client );
	int handle_server_disconnect( void* _server, int _event_type, void* _client );
	int handle_messages_client_received( void* _server, int _event_type, void* _full_message );

	/**
	 * The Client class
	 */
	class Client
	{
		public:
			int send( const int& _msg_id, void* _data, const int& _size );
		
		protected:
			Client( const int& _port, const std::string& _host );
			
			~Client();
			
			void register_events( void* _data );
			
			Ecore_Ipc_Server* server;
			
			virtual int handle_message( const int& _msg_id, std::vector <void*> _data ) { };
			
			friend int handle_server_connect( void* _client, int _event_type, void* _full_message );
			
			friend int handle_server_disconnect( void* _client, int _event_type, void* _full_message );
			
			friend int handle_messages_client_received( void* _data, int _event_type, void* _full_message );
	};
};
#endif
