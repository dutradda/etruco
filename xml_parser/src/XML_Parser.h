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
 * A class with some functions to parse a xml file.
 */
class XML_Parser
{
	public:

		/**
		 * Free a vector of nodes.
		 *	@param nodes
		 *	 A vector of nodes to free.
		 *
		 */
		static void free_nodes( std::vector <Node*>& nodes );

		/**
		 * Get all children of a node and its children too.
		 * @param _name
		 *  The name of the node to get children.
		 * @param _xml_file_name
		 *  The name of xml file.
		 * @param _attributes
		 *  The attributes of node. Could be empty, the pattern is a map of name attribute, value attribute.
		 */
		static std::vector <Node*>
		get_children_nodes( const std::string& _name,
								const std::string& _xml_file_name,
								const std::map <std::string, std::string>& _attributes );

		/**
		 * Get all nodes before the selected node and get its children.
		 * @param _name
		 *  The name of the node to get fathers.
		 * @param _xml_file_name
		 *  The name of xml file.
		 * @param _attributes
		 *  The attributes of node. Could be empty, the pattern is a map of name attribute, value attribute.
		 */
		static std::vector <Node*>
		get_fathers_nodes( const std::string& _name,
								const std::string& _xml_file_name,
								const std::map <std::string, std::string>& _attributes );

		/**
		 * Get all nodes beside the node selected, get all before and get its children too.
		 * @param _name
		 *  The name of the node to get brothers.
		 * @param _xml_file_name
		 *  The name of xml file.
		 * @param _attributes
		 *  The attributes of node. Could be empty, the pattern is a map of name attribute, value attribute.
		 */
		static std::vector <Node*>
		get_brothers_nodes( const std::string& _name,
								const std::string& _xml_file_name,
								const std::map <std::string, std::string>& _attributes );
		
	private:
		
		XML_Parser() { };

		static Node*
		create_node( const xmlNodePtr& current_node );

		static int
		check_node( const xmlNodePtr& _current_node,
							const std::string& _name,
							const std::map <std::string, std::string>& _attributes );

		static void
		get_node_recursive( Node*& node, const xmlNodePtr& current_node );

		static void
		get_children_nodes_recursive( std::vector <Node*>& nodes_found,
								const xmlNodePtr& _current_node,
								const std::string& _name,
								const std::map <std::string, std::string>& _attributes );

		static void
		get_fathers_nodes_recursive( std::vector <Node*>& nodes_found,
								const xmlNodePtr& _current_node,
								const std::string& _name,
								const std::map <std::string, std::string>& _attributes );

		static void
		get_brothers_nodes_recursive( std::vector <Node*>& nodes_found,
								const xmlNodePtr& _current_node,
								const std::string& _name,
								const std::map <std::string, std::string>& _attributes );
};
	
#endif
