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

XML_Parser::XML_Parser( const string& _xml_file_name )
{
	xml_document = xmlParseFile( _xml_file_name.c_str() );
}

XML_Parser::~XML_Parser()
{
	xmlFreeDoc( xml_document );
	xmlCleanupParser();
	xmlMemoryDump();

}

bool XML_Parser::search_child( vector<Node*> _nodes, const string& _name )
{
	for( int i = 0; i < _nodes.size(); i++ )
		if( _nodes[i]->name == _name )
			return true;

	return false;
}

void
XML_Parser::get_nodes_recurvise( xmlNodePtr _current_node,
											vector <Node*>& nodes_found,
											const string& _name,
											const string& _attribute_name,
											const string& _attribute_value)
{
	xmlNodePtr current_node = _current_node->xmlChildrenNode;
	
	while( current_node != NULL )
	{
		if( current_node->type != XML_TEXT_NODE )
			/* Busca pelo noh recursivamente.
			 * Se o noh for o corrente e tem o atributo e o valor dele nao foi setado ou
			 * tem o atributo e tem o valor ou
			 * nem o atributo nem o valor foi setado, entao ele entra na condicao */
			if( (xmlStrcmp( current_node->name, (const xmlChar *) _name.c_str() ) == 0) &&
					((_attribute_name != "" && xmlHasProp( current_node, (const xmlChar*) _attribute_name.c_str() ) &&
					_attribute_value == "") ||
					(_attribute_name != "" && xmlHasProp( current_node, (const xmlChar*) _attribute_name.c_str() ) &&
					_attribute_value != "" &&
					_attribute_value == (const char*) xmlGetProp( current_node,
																				(const xmlChar*) _attribute_name.c_str() )) ||
					((_attribute_name == "") && (_attribute_value == ""))) )
			{
				Node* new_node_found = new Node;
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
					!search_child( new_node_found->children, (const char*) current_node_child->name ) )
						get_nodes_recurvise( current_node,
													new_node_found->children,
													(const char*) current_node_child->name );
					current_node_child = current_node_child->next;
				}
				nodes_found.push_back( new_node_found );
			}
			else
				get_nodes_recurvise( current_node, nodes_found, _name, _attribute_name, _attribute_value );
		current_node = current_node->next;
	}
}

vector <Node*>
XML_Parser::get_children_nodes( const string& _name,
											const string& _attribute_name,
											const string& _attribute_value)
{
	xmlNodePtr root_node = xmlDocGetRootElement( xml_document );
	vector <Node*> nodes;
	
	if( _attribute_name == "" && _attribute_value == "" )
		get_nodes_recurvise( root_node, nodes, _name );
	else if( _attribute_value == "" )
		get_nodes_recurvise( root_node, nodes, _name, _attribute_name );
	else
		get_nodes_recurvise( root_node, nodes, _name, _attribute_name, _attribute_value );

	return nodes;
}

void XML_Parser::free_nodes( vector <Node*> nodes )
{
	vector <Node*>::iterator i;
	for( i = nodes.begin(); i != nodes.end(); i++ )
	{
		free_nodes( (*i)->children );
		delete (*i);
	}
		
}
