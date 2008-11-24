/*  
 * Messages_Handler.h
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
 
#ifndef IPCPP_MESSAGES_HANDLER_H
#define IPCPP_MESSAGES_HANDLER_H

#include <XML_Parser.h>
#include <Eina.h>

namespace ipcpp
{
	struct Callback
	{
		string name;
		string module_file_name;
		void* func;
	};

	struct Message
	{
		int id;
		string name;
		void* callback;
	};

	class Messages_Handler
	{
		public:
			/**
			 * Constructor.
			 *
			 * @param _xml_file_name
			 *  The xml file that contain a list of messages.
			 */
			Messages_Handler( const string& _xml_file_name );
			
			/**
			 * Destructor.
			 */
			virtual ~Messages_Handler();
			
			/*int run_message_rcv( const int& _msg_id, void* _data );
			
			int run_message_send( const int& _msg_id, void* _data );*/
			
		protected:
			vector <Message> messages_to_receive;
			vector <Message> messages_to_send;
			
			int run_message( const vector <Message>& _messages, const int& _msg_id, void*& _data );
			
			int run_message( const vector <Message>& _messages, const string& _msg_name, void*& _data );
			
			Message get_message_by_id( const int& _msg_id );
			
		private:
			XML_Parser xml_parser;
			string xml_file_name;
			vector <Eina_Module*> modules; // The modules where the rules functions are in
			
			/*
			 * Register all messages to be handled.
			 * 
			 * @return
			 *  The multimap with the errors and messages.
			 *  The errors are:
			 *  -1 if the module of a rule function dont exist.
			 *  -2 if a rule function dont exist in the module.
			 */
			multimap <int, string> register_messages();
			
			multimap <int, string>
			register_messages( vector <Message>& _messages, const string& _msg_type );
	};
};
#endif
