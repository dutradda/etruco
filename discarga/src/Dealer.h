/*  
 * Dealer.h
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

#ifndef DISCARGA_DEALER_H
#define DISCARGA_DEALER_H

#include "Rule_Handler.h"

#include <string>
#include <vector>
#include <ipcpp/Server.h>

namespace discarga
{
	/**
	 * The Dealer of the game.
	 */
	class Dealer : public ipcpp::Server, public Rule_Handler
	{	
		public:
			/**
			* Constructor
			*
			* @param _port 
			* Port's number to connect
			*
			* @param _xml_file_name
			* The xml file name where the rules are.
			*/
			Dealer( const int& _port, const std::string& _xml_file_name );
			
			/**
			* Apply the rule throught name
			*
			* @param _rule_name
			* Rules's name
			*
			* @param _data
			* Data's vector
			*
			* @param _who_sent
 			* Id of who sent the message
			*/
			int apply_rule( const std::string& _rule_name, std::vector<void*>& _data, const int& _who_sent = -1 );
			

			/**
			* Apply the rule throught rule's id
			*
			* @param _rule_id
			* Rules's id
			*
			* @param _data
			* Data's vector
			*
			* @param _who_sent
 			* Id of who sent the message
			*/
			int apply_rule( const int& _rule_id, std::vector<void*>& _data, const int& _who_sent = -1 );
			
		protected:
			
			/**
			* Message colector
			*
			* @param _msg_id
			* Message's id
			*
			* @param _data
			* Data's vector
			*
			* @param _who_sent
 			* Id of who sent the message
			*/
			int handle_message( const int& _msg_id, std::vector<void*> _data, const int& _who_sent );
	};
};

#endif
