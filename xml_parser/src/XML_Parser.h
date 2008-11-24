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

#include <libxml/xmlreader.h>
#include <vector>
#include <string>
#include <map>
using namespace std;

struct Node
{
	string name;
	map <string, string> attributes;
	vector <Node*> children;
};

class XML_Parser
{
	public:
		void free_nodes( vector <Node*>& nodes );
		
		vector <Node*>
		get_children_nodes( const string& _name,
								const string& _xml_file_name,
								const string& _attribute_name = "",
								const string& _attribute_value = "" );
								
		vector <Node*>
		get_children_nodes( const Node* _node,
								const string& _name,
								const string& _attribute_name = "",
								const string& _attribute_value = "" );
		
	private:
		//vector <vector <Node*> > nodes_created;
		
		bool search_child( const vector<Node*>& _nodes, const string& _name );
		
		void
		get_nodes_recurvise( vector <Node*>& nodes_found,
								const xmlNodePtr& _current_node,
								const string& _name,
								const string& _attribute_name = "",
								const string& _attribute_value = "" );
								
		void
		get_nodes_recurvise( vector <Node*>& nodes_found,
								const Node* _current_node,
								const string& _name,
								const string& _attribute_name = "",
								const string& _attribute_value = "" );
		
		
};
	
#endif
