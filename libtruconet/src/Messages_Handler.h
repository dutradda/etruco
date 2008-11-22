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
 
#ifndef MESSAGES_HANDLER_H
#define MESSAGES_HANDLER_H

#include <libxml/xmlreader.h>

class Messages_Handler
{
	public:
		/**
		 * Constructor.
		 *
		 * @param _file
		 *  The xml file that contain a list of messages.
		 */
		Messages_Handler( const& string _file="" ) : file( _file ), xml_file_reader( NULL ) { };
		
		/**
		 * Destructor.
		 */
		virtual ~Messages_Handler();
		
		/**
		 * Register all messages in the file _file to be handled on receive event.
		 *
		 * @param _file
		 *  The xml file that contain a list of messages.
		 */
		int register_messages_to_receive( const& string _file="" );
		
		/**
		 * Register a messsage in the file _file to be handled on receive event.
		 *
		 * @param _message
		 *  The message to register.
		 * 
		 * @param _file
		 *  The xml file that contain a list of messages.
		 */
		int register_message_to_receive( const& string _message, const& string _file="" );
		
		/**
		 * Register all messages in the file _file to be handled on send event.
		 *
		 * @param _file
		 *  The xml file that contain a list of messages.
		 */
		int register_messages_to_send( const& string _file="" );
		
		/**
		 * Register a message in the file _file to be handled on send event.
		 * 
		 * @param _message
		 *  The message to register.
		 *
		 * @param _file
		 *  The xml file that contain a list of messages.
		 */
		int register_message_to_send( const& string _message, const& string _file="" );
		
	protected:
		vector <Message*> messages_to_receive;
		vector <Message*> messages_to_send;
		int handle_messages_received( void* _data, int _event_type, void* _full_message );
		
	private:
		string file;
		xmlTextReaderPtr xml_file_reader;
		int load_xml_file( const& string _file="" );
		void unload_xml_file();
		Message get_message_by_id( const& int _msg_id );
}

#endif
