/*  
 * XML_Parser.h
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

#ifndef XML_PARSER_H
#define XML_PARSER_H

#include <libxml2/libxml/xmlreader.h>
#include <vector>
#include <string>
#include <map>

struct Node
{
	std::string name;
	std::map <std::string, std::string> attributes;
	std::vector <Node*> children;
};

/**
 * The class who parses the xml.
 */
class XML_Parser
{
	public:
		static void free_nodes( std::vector <Node*>& nodes );
		
		static std::vector <Node*>
		get_children_nodes( const std::string& _name,
								const std::string& _xml_file_name,
								const std::string& _attribute_name = "",
								const std::string& _attribute_value = "" );
		
		static std::vector <Node*>
		get_father_nodes( const std::string& _name,
								const std::string& _xml_file_name,
								const std::string& _attribute_name = "",
								const std::string& _attribute_value = "" );
								
		static std::vector <Node*>
		get_children_nodes( const Node* _node,
								const std::string& _name,
								const std::string& _attribute_name = "",
								const std::string& _attribute_value = "" );
		
	private:
		//std::vector <std::vector <Node*> > nodes_created;
		
		static bool search_child( const std::vector<Node*>& _nodes, const std::string& _name );
		
		static void
		get_nodes_recursive_reverse( std::vector <Node*>& nodes_found,
								const xmlNodePtr& _current_node,
								const std::string& _name,
								const std::string& _attribute_name = "",
								const std::string& _attribute_value = "" );
		
		static void
		get_nodes_recursive( std::vector <Node*>& nodes_found,
								const xmlNodePtr& _current_node,
								const std::string& _name,
								const std::string& _attribute_name = "",
								const std::string& _attribute_value = "" );
								
		static void
		get_nodes_recursive( std::vector <Node*>& nodes_found,
								const Node* _current_node,
								const std::string& _name,
								const std::string& _attribute_name = "",
								const std::string& _attribute_value = "" );
		
		
};
	
#endif
