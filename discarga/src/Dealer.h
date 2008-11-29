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

#include "Action_Handler.h"

#include <string>
#include <vector>
#include <ipcpp/Server.h>

namespace discarga
{
	class Dealer : public ipcpp::Server, public Action_Handler
	{	
		public:
			Dealer( const int& _port, const std::string& _xml_file_name );
			
			int do_action( const int& _act_id, std::vector<void*>& _data );
	};
};

#endif