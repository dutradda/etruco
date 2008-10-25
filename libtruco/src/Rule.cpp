/*  
 * Rule.cpp
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

#include "Rule.h"

Rule::Rule( string _name,
			string _truco_type,
			string _description,
			string _where_apply,
			string _cb_name,
			vector <string> _conflicts,
			vector <string> _dependencies,
			string _file = "" )
{
	name = _name;
	truco_type = _truco_type;
	description = _description;
	where_apply = _where_apply;
	conflicts = _conflicts;
	dependencies = _dependencies;
	cb_name = _cb_name;
	file = _file;
}
