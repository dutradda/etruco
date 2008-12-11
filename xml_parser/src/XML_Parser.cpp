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

#include <map>
#include <iostream>

#include "XML_Parser.h"

using namespace std;

bool XML_Parser::has_child( const vector<Node*>& _nodes, const string& _name )
{
	for( vector<Node*>::const_iterator i = _nodes.begin(); i != _nodes.end(); i++ )
		if( (*i)->name == _name )
			return true;

	return false;
}

void
XML_Parser::get_nodes_recursive_reverse( vector <Node*>& nodes_found,
											const xmlNodePtr& _current_node,
											const string& _name,
											const string& _attribute_name,
											const string& _attribute_value )
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
					!has_child( new_node_found->children, (const char*) current_node_child->name ) )
						get_nodes_recursive_reverse( new_node_found->children,
													current_node,
													(const char*) current_node_child->name );
					current_node_child = current_node_child->next;
				}
				nodes_found.push_back( new_node_found );
			}
			else if( current_node->xmlChildrenNode != NULL )
			{
				vector <Node*> node_children;
				get_nodes_recursive_reverse( node_children, current_node, _name, _attribute_name, _attribute_value );
				
				if( !node_children.empty() )
				{
					Node* new_node = new Node;
					new_node->name = (const char*) current_node->name;

					// Adiciona o atributos do noh
					struct _xmlAttr*	properties;
					for( properties = current_node->properties;
							properties != NULL; properties = properties->next )
						new_node->attributes[(const char*) properties->name] =
													(const char*) properties->children->content;
					new_node->children = node_children;
					nodes_found.push_back( new_node );
				}
			}
			else
				get_nodes_recursive_reverse( nodes_found, current_node, _name, _attribute_name, _attribute_value );
		current_node = current_node->next;
	}
}

void
XML_Parser::get_node_recursive( vector <Node*>& nodes_found,
											const xmlNodePtr& _current_node )
{
	xmlNodePtr current_node = _current_node->xmlChildrenNode;
	
	while( current_node != NULL )
	{
		if( current_node->type != XML_TEXT_NODE )
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
				!has_child( new_node_found->children, (const char*) current_node_child->name ) )
					get_nodes_recursive( new_node_found->children,
												current_node,
												(const char*) current_node_child->name );
				current_node_child = current_node_child->next;
			}
			nodes_found.push_back( new_node_found );
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
	
	while( current_node != NULL )
	{
		if( current_node->type != XML_TEXT_NODE )
			if( (xmlStrcmp( current_node->name, (const xmlChar *) _name.c_str() ) == 0) )
			{
				int has_attribute = 1;
				for( map <string, string>::const_iterator i = _attributes.begin(); i != _attributes.end(); i++ )
				{
					/* Se o noh for o corrente e tem o atributo pedido e o valor dele nao foi setado ou
					 * tem o atributo pedido e o valor foi setado corretamente */
					if( (xmlHasProp( current_node, (const xmlChar*) i->first.c_str() ) && i->second == "") ||
						 (xmlHasProp( current_node, (const xmlChar*) i->first.c_str() ) &&
							  i->second == (const char*) xmlGetProp( current_node,
																				(const xmlChar*) i->first.c_str() )) )
						has_attribute = 2;
					else
					{
						has_attribute = 0;
						break;
					}
				}

				// Se um atributo pedido nao foi encontrado ele nao adiciona
				if( has_attribute == 2 )
					get_node_recursive(nodes_found, _current_node );
				else if( has_attribute == 1 )
				{
					Node* new_node_found = new Node;
					new_node_found->name = (const char*) current_node->name;

					// Adiciona os atributos do noh
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
						!has_child( new_node_found->children, (const char*) current_node_child->name ) )
							get_brothers_nodes_recursive( new_node_found->children,
														current_node,
														(const char*) current_node_child->name, map <string,string>() );
						current_node_child = current_node_child->next;
					}
					nodes_found.push_back( new_node_found );
				}
				else
					goto GET_FATHER;
			}
			else
				GET_FATHER:
				if( current_node->xmlChildrenNode != NULL )
				{
					vector <Node*> node_children;
					get_brothers_nodes_recursive( node_children, current_node, _name, _attributes );

					if( !node_children.empty() )
					{
						Node* new_node = new Node;
						new_node->name = (const char*) current_node->name;

						// Adiciona o atributos do noh
						struct _xmlAttr*	properties;
						for( properties = current_node->properties;
								properties != NULL; properties = properties->next )
							new_node->attributes[(const char*) properties->name] =
														(const char*) properties->children->content;
						new_node->children = node_children;
						nodes_found.push_back( new_node );
					}
				}
				else
					get_brothers_nodes_recursive( nodes_found, current_node, _name, _attributes );
		current_node = current_node->next;
	}
}


void
XML_Parser::get_nodes_recursive_reverse( vector <Node*>& nodes_found,
											const xmlNodePtr& _current_node,
											const string& _name,
											const map <string, string>& _attributes )
{
	xmlNodePtr current_node = _current_node->xmlChildrenNode;

	while( current_node != NULL )
	{
		if( current_node->type != XML_TEXT_NODE )
			if( (xmlStrcmp( current_node->name, (const xmlChar *) _name.c_str() ) == 0) )
			{
				int has_attribute = 1;
				for( map <string, string>::const_iterator i = _attributes.begin(); i != _attributes.end(); i++ )
				{
					/* Se o noh for o corrente e tem o atributo pedido e o valor dele nao foi setado ou
					 * tem o atributo pedido e o valor foi setado corretamente */
					if( (xmlHasProp( current_node, (const xmlChar*) i->first.c_str() ) && i->second == "") ||
						 (xmlHasProp( current_node, (const xmlChar*) i->first.c_str() ) &&
							  i->second == (const char*) xmlGetProp( current_node,
																				(const xmlChar*) i->first.c_str() )) )
						continue;
					else
					{
						has_attribute = 0;
						break;
					}
				}

				// Se um atributo pedido nao foi encontrado ele nao adiciona
				if( has_attribute )
				{
					Node* new_node_found = new Node;
					new_node_found->name = (const char*) current_node->name;

					// Adiciona os atributos do noh
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
						!has_child( new_node_found->children, (const char*) current_node_child->name ) )
							get_nodes_recursive_reverse( new_node_found->children,
														current_node,
														(const char*) current_node_child->name, map<string,string>() );
						current_node_child = current_node_child->next;
					}
					nodes_found.push_back( new_node_found );
				}
				else
					goto GET_FATHER;
			}
			else
				GET_FATHER:
				if( current_node->xmlChildrenNode != NULL )
				{
					vector <Node*> node_children;
					get_nodes_recursive_reverse( node_children, current_node, _name, _attributes );

					if( !node_children.empty() )
					{
						Node* new_node = new Node;
						new_node->name = (const char*) current_node->name;

						// Adiciona o atributos do noh
						struct _xmlAttr*	properties;
						for( properties = current_node->properties;
								properties != NULL; properties = properties->next )
							new_node->attributes[(const char*) properties->name] =
														(const char*) properties->children->content;
						new_node->children = node_children;
						nodes_found.push_back( new_node );
					}
				}
				else
					get_nodes_recursive_reverse( nodes_found, current_node, _name, _attributes );
		current_node = current_node->next;
	}
}


void
XML_Parser::get_nodes_recursive( vector <Node*>& nodes_found,
											const xmlNodePtr& _current_node,
											const string& _name,
											const string& _attribute_name,
											const string& _attribute_value )
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
					!has_child( new_node_found->children, (const char*) current_node_child->name ) )
						get_nodes_recursive( new_node_found->children,
													current_node,
													(const char*) current_node_child->name );
					current_node_child = current_node_child->next;
				}
				nodes_found.push_back( new_node_found );
			}
			else
				get_nodes_recursive( nodes_found, current_node, _name, _attribute_name, _attribute_value );
		current_node = current_node->next;
	}
}

void
XML_Parser::get_nodes_recursive( vector <Node*>& nodes_found,
											const Node* _current_node,
											const string& _name,
											const string& _attribute_name,
											const string& _attribute_value )
{
	vector <Node*> children = _current_node->children;
	
	for( vector <Node*>::iterator i = children.begin(); i != children.end(); i++ )
	{
		/* Busca pelo noh recursivamente.
		 * Se o noh for o corrente e tem o atributo e o valor dele nao foi setado ou
		 * tem o atributo e tem o valor ou
		 * nem o atributo nem o valor foi setado, entao ele entra na condicao */
		if( ((*i)->name == _name) &&
				((_attribute_name != "" && (*i)->attributes.find(_attribute_name) != (*i)->attributes.end() &&
				_attribute_value == "") ||
				(_attribute_name != "" && (*i)->attributes.find(_attribute_name) != (*i)->attributes.end() &&
				_attribute_value != "" && (*i)->attributes[_attribute_name] == _attribute_value) ||
				((_attribute_name == "") && (_attribute_value == ""))) )
			nodes_found.push_back( *(i) );
		else
			get_nodes_recursive( nodes_found, *i, _name, _attribute_name, _attribute_value );
	}
}

vector <Node*>
XML_Parser::get_children_nodes( const string& _name,
											const string& _xml_file_name,
											const string& _attribute_name,
											const string& _attribute_value )
{
	xmlDocPtr xml_document = xmlParseFile( _xml_file_name.c_str() );
	xmlNodePtr root_node = xmlDocGetRootElement( xml_document );
	vector <Node*> nodes;
	
	get_nodes_recursive( nodes, root_node, _name, _attribute_name, _attribute_value );

	xmlFreeDoc( xml_document );
	xmlCleanupParser();
	xmlMemoryDump();

	return nodes;
}

vector <Node*>
XML_Parser::get_children_nodes( const Node* _node,
											const string& _name,
											const string& _attribute_name,
											const string& _attribute_value )
{
	vector <Node*> new_nodes;
	
	get_nodes_recursive( new_nodes, _node, _name, _attribute_name, _attribute_value );

	return new_nodes;
}

vector <Node*>
XML_Parser::get_father_nodes( const string& _name,
											const string& _xml_file_name,
											const string& _attribute_name,
											const string& _attribute_value )
{
	xmlDocPtr xml_document = xmlParseFile( _xml_file_name.c_str() );
	xmlNodePtr root_node = xmlDocGetRootElement( xml_document );
	vector <Node*> nodes;
	
	get_nodes_recursive_reverse( nodes, root_node, _name, _attribute_name, _attribute_value );

	xmlFreeDoc( xml_document );
	xmlCleanupParser();
	xmlMemoryDump();

	return nodes;
}

std::vector <Node*>
		XML_Parser::get_father_nodes( const string& _name,
								const string& _xml_file_name,
								const map <string, string>& _attributes )
{
	xmlDocPtr xml_document = xmlParseFile( _xml_file_name.c_str() );
	xmlNodePtr root_node = xmlDocGetRootElement( xml_document );
	vector <Node*> nodes;

	get_nodes_recursive_reverse( nodes, root_node, _name, _attributes );

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
