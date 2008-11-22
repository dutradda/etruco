/*  
 * XML_Parser.cpp
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

#include "XML_Parser.h"

using namespace std;

bool _search_child(vector<node*> _nodes, const string& _name)
{
	for( int i = 0; i < _nodes.size(); i++ )
		if( _nodes[i]->name == _name )
			return true;

	return false;
}

void _get_children_nodes( xmlNodePtr _current_node, vector <node*>& nodes_found, const string& _name )
{
	xmlNodePtr current_node = _current_node->xmlChildrenNode;
	
	while( current_node != NULL )
	{
		if( current_node->type != XML_TEXT_NODE )
			// Busca pelo noh recursivamente
			if( xmlStrcmp(current_node->name, (const xmlChar *) _name.c_str()) ) // O noh procurado nao eh o corrente
				_get_children_nodes( current_node, nodes_found, _name);
			else
			{
				node* new_node_found = new node;
				new_node_found->name = (const char*) current_node->name;
				
				// Adiciona o atributos do noh
				struct _xmlAttr*	properties;
				for( properties = current_node->properties;
						properties != NULL; properties = properties->next )
					new_node_found->attributes[(const char*) properties->name] =
												(const char*) properties->children->content;
				
				// Adiciona os filhos noh recursivamente
				xmlNodePtr current_node_child = current_node->xmlChildrenNode;
				while( current_node_child != NULL )
				{
					// Quando eh feita uma busca por um filho, jah se adiciona todos os filhos daquele tipo
					if( current_node_child->type != XML_TEXT_NODE &&
					!_search_child( new_node_found->children, (const char*) current_node_child->name ) )
						_get_children_nodes( current_node,
													new_node_found->children,
													(const char*) current_node_child->name );
					current_node_child = current_node_child->next;
				}
				nodes_found.push_back( new_node_found );
			}
		current_node = current_node->next;
	}
}

vector <node*> get_children_nodes( const string& _xml_file_name, const string& _name )
{
	xmlDocPtr xml_file = xmlParseFile( _xml_file_name.c_str() );
	xmlNodePtr root_node = xmlDocGetRootElement( xml_file );
	vector <node*> nodes;

	_get_children_nodes( root_node, nodes, _name );
	
	xmlFreeDoc(xml_file);
	
	return nodes;
}

vector <node*>
get_children_nodes_by_attribute( const string& _xml_file,
											const string& _name,
											const string& _attribute,
											const string& _attribute_value)
{
}
