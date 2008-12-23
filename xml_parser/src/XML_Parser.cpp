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

#include <vector>
#include <map>

#include "XML_Parser.h"

using namespace std;

Node*
XML_Parser::create_node( const xmlNodePtr& current_node )
{
	Node* node = new Node;
	node->name = (const char*) current_node->name;

	// Adiciona os atributos do noh
	struct _xmlAttr*	properties;
	for( properties = current_node->properties; properties != NULL; properties = properties->next )
		node->attributes[(const char*) properties->name] = (const char*) properties->children->content;

	return node;
}

int
XML_Parser::check_node( const xmlNodePtr& _current_node,
							const string& _name,
							const map <string, string>& _attributes )
{
	if( (_current_node->type != XML_TEXT_NODE) && (xmlStrcmp( _current_node->name, (const xmlChar *) _name.c_str() ) == 0) )
		for( map <string, string>::const_iterator i = _attributes.begin(); i != _attributes.end(); i++ )
			/* Se o noh for o corrente e tem o atributo pedido e o valor dele nao foi setado ou
			 * tem o atributo pedido e o valor foi setado corretamente */
			if( (xmlHasProp( _current_node, (const xmlChar*) i->first.c_str() ) && i->second == "") ||
				 (xmlHasProp( _current_node, (const xmlChar*) i->first.c_str() ) &&
					  i->second == (const char*) xmlGetProp( _current_node,
																		(const xmlChar*) i->first.c_str() )) )
				continue;
			else
				return -1;
	else
		return 0;
	return 1;
}

/*
 * Adiciona tudo recursivamente a partir de _current_node
 */
void
XML_Parser::get_node_recursive( Node*& node, const xmlNodePtr& current_node )
{
	if( current_node->type != XML_TEXT_NODE && current_node != NULL )
	{
		node = create_node( current_node );
		// Adiciona os filhos do noh recursivamente
		xmlNodePtr current_node_child = current_node->xmlChildrenNode;
		Node* node_child;
		while( current_node_child != NULL )
		{
			node_child = NULL;
			get_node_recursive( node_child, current_node_child );
			if( node_child != NULL )
				node->children.push_back( node_child );
			current_node_child = current_node_child->next;
		}
	}
}

/*
 * Procura recursivamente pelo noh _name a partir de _current_node, e caso encontre adiciona todos seus filhos
 */
void
XML_Parser::get_children_nodes_recursive( vector <Node*>& nodes_found,
											const xmlNodePtr& _current_node,
											const string& _name,
											const map <string, string>& _attributes )
{
	xmlNodePtr current_node = _current_node->xmlChildrenNode;
	Node* node;

	while( current_node != NULL )
	{
		node = NULL;
		if( check_node( current_node, _name, _attributes ) == 1 )
		{
			get_node_recursive( node, current_node );
			if( node != NULL )
				nodes_found.push_back( node );
		}
		else
			get_children_nodes_recursive( nodes_found, current_node, _name, _attributes );

		current_node = current_node->next;
	}
}

void
XML_Parser::get_fathers_nodes_recursive( vector <Node*>& nodes_found,
											const xmlNodePtr& _current_node,
											const string& _name,
											const map <string, string>& _attributes )
{
	xmlNodePtr current_node = _current_node->xmlChildrenNode;
	Node* node;

	while( current_node != NULL )
	{
		node = NULL;
		if( check_node( current_node, _name, _attributes ) == 1 )
		{
			get_node_recursive( node, current_node );
			if( node != NULL )
				nodes_found.push_back( node );
		}
		else if( current_node->xmlChildrenNode != NULL )
		{
				vector <Node*> node_children;
				get_fathers_nodes_recursive( node_children, current_node, _name, _attributes );

				if( !node_children.empty() )
				{
					Node* new_node = create_node( current_node );
					new_node->children = node_children;
					nodes_found.push_back( new_node );
				}
		}
		current_node = current_node->next;
	}
}

void
XML_Parser::get_brothers_nodes_recursive( vector <Node*>& nodes_found,
											const xmlNodePtr& _current_node,
											const string& _name,
											const map <string, string>& _attributes )
{
	xmlNodePtr current_node = _current_node->xmlChildrenNode;
	Node* node;

	while( current_node != NULL )
	{
		node = NULL;
		if( check_node( current_node, _name, _attributes ) == 1 )
		{
			get_node_recursive( node, _current_node );
			if( node != NULL )
				nodes_found.insert( nodes_found.end(), node->children.begin(), node->children.end() );
		}
		else if( current_node->xmlChildrenNode != NULL )
		{
				vector <Node*> node_children;
				get_brothers_nodes_recursive( node_children, current_node, _name, _attributes );

				if( !node_children.empty() )
				{
					Node* new_node = create_node( current_node );
					new_node->children = node_children;
					nodes_found.push_back( new_node );
				}
		}
		current_node = current_node->next;
	}
}

vector <Node*>
XML_Parser::get_children_nodes( const string& _name,
										const string& _xml_file_name,
										const map <string, string>& _attributes )
{
	xmlDocPtr xml_document = xmlParseFile( _xml_file_name.c_str() );
	xmlNodePtr root_node = xmlDocGetRootElement( xml_document );
	vector <Node*> nodes;
	
	get_children_nodes_recursive( nodes, root_node, _name, _attributes );

	xmlFreeDoc( xml_document );
	xmlCleanupParser();
	xmlMemoryDump();

	return nodes;
}

std::vector <Node*>
XML_Parser::get_fathers_nodes( const string& _name,
										const string& _xml_file_name,
										const map <string, string>& _attributes )
{
	xmlDocPtr xml_document = xmlParseFile( _xml_file_name.c_str() );
	xmlNodePtr root_node = xmlDocGetRootElement( xml_document );
	vector <Node*> nodes;

	get_fathers_nodes_recursive( nodes, root_node, _name, _attributes );

	xmlFreeDoc( xml_document );
	xmlCleanupParser();
	xmlMemoryDump();

	return nodes;
}

std::vector <Node*>
XML_Parser::get_brothers_nodes( const string& _name,
										const string& _xml_file_name,
										const map <string, string>& _attributes )
{
	xmlDocPtr xml_document = xmlParseFile( _xml_file_name.c_str() );
	xmlNodePtr root_node = xmlDocGetRootElement( xml_document );
	vector <Node*> nodes;

	get_brothers_nodes_recursive( nodes, root_node, _name, _attributes );

	xmlFreeDoc( xml_document );
	xmlCleanupParser();
	xmlMemoryDump();

	return nodes;
}


void XML_Parser::free_nodes( vector <Node*>& nodes )
{
	vector <Node*>::iterator i;
	for( i = nodes.begin(); i != nodes.end(); i++ )
	{
		free_nodes( (*i)->children );
		delete (*i);
	}
		
}
