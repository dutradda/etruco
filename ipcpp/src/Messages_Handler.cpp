/*  
 * Messages_Handler.cpp
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

#include "Messages_Handler.h"


Messages_Handler::Messages_Handler( const string& _xml_file_name )
{
	xml_file_name = _xml_file_name;
	eina_module_init();
	register_messages();
}

Messages_Handler::~Messages_Handler()
{
	/*for( vector <Message>::iterator i = messages_to_send.begin(); i != messages_to_send.end(); i++ )
		delete *i;
		
	for( vector <Message>::iterator i = messages_to_receive.begin(); i != messages_to_receive.end(); i++ )
		delete *i;*/
	
	for( vector <Eina_Module*>::iterator i = modules.begin(); i != modules.end(); i++ )
	{
		eina_module_unload(*i);
		eina_module_delete(*i);
	}
	
	eina_module_shutdown();
}

multimap <int, string> Messages_Handler::register_messages()
{
	multimap <int, string> messages_errors = register_messages( messages_to_receive, "receive" );
	multimap <int, string> messages_errors2 = register_messages( messages_to_send, "send" );
	
	for( multimap <int, string>::iterator i = messages_errors2.begin(); i != messages_errors2.begin(); i++)
		messages_errors.insert( *i );
		
	return messages_errors;
}

multimap <int, string>
Messages_Handler::register_messages( vector <Message>& _messages,
												const string& _msg_type )
{
	vector <Node*> nodes = xml_parser.get_children_nodes( "message", xml_file_name, "type", _msg_type );
	multimap <int, string> messages_errors;
	
	bool have_module;
	Callback callback;
	vector <Node*> node_callback;
	Message message;
	for( vector <Node*>::iterator i = nodes.begin(); i != nodes.end(); i++ )
	{
		// Pega a callback	
		node_callback = xml_parser.get_children_nodes(*i, "callback");
		callback.name = (*(node_callback.begin()))->attributes["name"];
		callback.module_file_name = (*(node_callback.begin()))->attributes["module_file_name"];

		// Verifica se o modulo ja esta carregado e pega a funcao
		have_module = false;
		for( vector<Eina_Module*>::iterator j = modules.begin(); j != modules.end(); j++ )
		{
			callback.func = eina_module_symbol_get( *j, callback.name.c_str() );
			if( callback.func != NULL )
			{
				have_module = true;
				break;
			}
		}
		
		// Carrega o modulo e pega a funcao
		if( !have_module )
		{
			modules.push_back( eina_module_new( callback.module_file_name.c_str() ) );
			if( modules.back() == NULL )
			{
				messages_errors.insert( pair <int,string>( -1, (*i)->attributes["name"] ) );
				modules.pop_back();
				continue;
			}
			eina_module_load( modules.back() );
			callback.func = eina_module_symbol_get( modules.back(), callback.name.c_str() );
		}
		
		if( callback.func == NULL )
		{
			messages_errors.insert( pair <int,string>( -2, (*i)->attributes["name"] ) );
			continue;
		}
		
		message.id = atoi( (*i)->attributes["id"].c_str() );
		message.name = (*i)->attributes["name"];
		message.callback = callback.func;
		
		_messages.push_back( message );
	}
	
	xml_parser.free_nodes(nodes);
	
	return messages_errors;
}

/*int Messages_Handler::run_message_rcv( const int& _msg_id, void* _data )
{
	return run_message( messages_to_receive, _msg_id, _data );
}

int Messages_Handler::run_message_send( const int& _msg_id, void* _data )
{
	return run_message( messages_to_send, _msg_id, _data );
}*/

int Messages_Handler::run_message( const vector <Message>& _messages, const int& _msg_id, void*& _data )
{
	for( vector<Message>::const_iterator i = _messages.begin(); i != _messages.end(); i++ )
		if( (*i).id == _msg_id )
		{
			int (*callback)( void* ) = (int (*)( void* )) (*i).callback;
			return callback(_data);
		}
}

int Messages_Handler::run_message( const vector <Message>& _messages, const string& _msg_name, void*& _data )
{
	for( vector<Message>::const_iterator i = _messages.begin(); i != _messages.end(); i++ )
		if( (*i).name == _msg_name )
		{
			int (*callback)( void* ) = (int (*)( void* )) (*i).callback;
			return callback(_data);
		}
}
