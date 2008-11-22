/*  
 * Message.h
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
 
#ifndef MESSAGE_H
#define MESSAGE_H

/**
 * The message class.
 */
class Message
{
	public:
		/**
		 * Constructor.
		 *
		 * @param _id
		 *  The message id
		 *
		 * @param _name
		 *  The message name
		 * 
		 * @param _callback
		 *  The function callback to this message.
		 */
		Message( const& int _id, const& string _name, void* _callback ) : 
					id( _id ), name( _name ), callback( _callback ) { };

		/**
		 * Gets the message id.
		 */
		inline int get_id() { return id; };
		
		/**
		 * Gets the message name.
		 */
		inline string get_name() { return name; };
		
		/**
		 * Gets the function callback.
		 */
		inline void* get_callback() { return callback; };
	
	private:
		int id;
		string name;
		void* callback;
		
}

#endif
