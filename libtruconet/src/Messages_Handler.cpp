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

int Messages_Handler::register_messages_to_receive( const& string _file="" )
{
	if( !load_xml_file(_file) )
		return 0;
	
	
	
	unload_xml_file();
}

int Messages_Handler::load_xml_file( const& string _file="" )
{
	LIBXML_TEST_VERSION
	if( _file == "" || _file.is_empty() )
		if( file != "" || !file.is_empty() )
			xml_file_reader = xmlReaderForFile( file.c_str(), NULL, 0 );
		else
			return 0;
	else
	{
		xml_file_reader = xmlReaderForFile( _file.c_str(), NULL, 0 );
		file = _file;
	}
		
	return 1;
}

void Messages_Handler::unload_xml_file()
{
	if ( xml_file_reader != NULL )
		xmlFreeTextReader(xml_file_reader);
		
	xmlCleanupParser();
	xmlMemoryDump();
}
