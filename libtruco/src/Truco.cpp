/*  
 * Truco.cpp
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

#include "Truco.h"

#include <config.h>
#include <libxml/xmlreader.h>
#include <iostream>
using namespace std;

Truco::Truco( int num_players = 4, int num_teams = 2 )
{
	int num_team_players = num_players / num_teams;
	
	for( int i = 0; i < num_players; i++ )
		players.push_back( new Player() );
	
	// Cria as equipes e adiciona os jogadores a elas
	for( int i = 0; i < num_teams; i++ )
	{
		vector <Player*> aux;
		// Insere todos os jogadores da mesma equipe de uma vez
		for( int j = 0; j < num_team_players; j++ )
			aux.push_back( players[i+(num_team_players*j)] );
		teams.push_back( new Team(aux) );
	}
			
}

Truco::~Truco()
{
	int size = players.size();
	
	for( int i = 0; i < size; i++ )
		delete players[i];
		
	size = teams.size();
	
	for( int i = 0; i < size; i++ )
		delete teams[i];
		
	size = modules.size();
	
	for( int i = 0; i < size; i++)
		g_module_close(modules[i]);
}

int Truco::check_rule_conflicts( vector <conflict> _conflicts )
{
	for( int i = 0; i < rules.size(); i++ )
		for( int j = 0; j < _conflicts.size(); j++ )
			if( rules[i]->get_name() == _conflicts[j].name &&
				rules[i]->get_truco_type() == _conflicts[j].truco_type )
				return 0;
	return 1;
}

int
Truco::check_rule_dependencies( string _truco_type,
										vector <string> _dependencies,
										vector <Rule*>& _rules_deps )
{
	int depends = 0;
	
	for( int i = 0; i < _dependencies.size(); i++ )
	{
		for( int j = 0; j < rules.size(); j++ )
			if( _dependencies[i] == rules[j]->get_name() &&
				_truco_type == rules[j]->get_truco_type() )
			{
				depends = 1;
				_rules_deps.push_back( rules[j] );
			}

		if( !depends )
			return 0;
	}
	return 1;
}

vector <Rule*> Truco::get_rules_where_apply( const string& _where )
{
	vector <Rule*> _rules;
	for( int i = 0; i < rules.size(); i++ )
		if( rules[i]->get_where_apply() == _where )
			_rules.push_back( rules[i] );
			
	return _rules;
}

int Truco::apply_rule( Rule _rule, vector <void*> _params )
{
	int ( *callback )( Rule, Truco, vector<void*> ) =
		( int (*)( Rule, Truco, vector<void*> ) ) _rule.get_callback();
		
	if( !callback(_rule, *this, _params) )
		return 0;
	else
		return 1;
}

int
Truco::apply_rules( const string& where_apply,
								vector <void*> _params )
{
	vector <Rule*> _rules = get_rules_where_apply( where_apply );
	
	for( int i = 0; i < _rules.size(); i++ )
		if ( !apply_rule( *_rules[i], _params ) )
			return 0;
			
	return 1;
}

int Truco::load_rule( const string& _rule, const string& _truco_type, const string& _file = "" )
{
	LIBXML_TEST_VERSION // Inicia a libxml
	
	int ret; // Retorno da funcao, pode ser -5, -4, -3, -2, -1, 0 e 1
	xmlTextReaderPtr reader;
	Rule* rule = NULL;
	int ( *_callback )( Rule, Truco, vector <void*> );
	
	if( _file != "" )
		reader = xmlReaderForFile( _file.c_str(), NULL, 0 );
	else
		reader = xmlReaderForFile( PACKAGE_DATA_DIR"/rules/default.xml", NULL, 0 );
	
	int file_nfinished = 1;
	
	while( file_nfinished == 1 )
	{
		vector <string> attributes;
		conflict _conflict;
		vector <conflict> conflicts;
		vector <string> dependencies;
		string node;
		
		// Le ate achar a abertura de uma regra
		int i = 0;
		do
		{
			file_nfinished = xmlTextReaderRead( reader );
			if( file_nfinished == 0 )
				break;
			node = (char*) xmlTextReaderConstName( reader );
			
		} while( node != "rule" && reader != NULL );
		// Fim da leitura ate achar uma abertura para uma regra
		
		if( file_nfinished == 0 )
			break;
		
		// Verifica se a regra eh a pedida
		if( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") != _rule )
		{
			if( ret != -1 )
				ret = 0;
			continue;
		}
		else if( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "truco_type") != _truco_type )
		{
			ret = -1;
			continue;
		}
		
		// Pega os atributos da regra
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "truco_type") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "description") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "where_apply") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "cb_name") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "file") );
		
		// Le ate achar o fechamento da regra
		do
		{
			file_nfinished = xmlTextReaderRead( reader );
			if( file_nfinished == 0)
				break;
			node = (char*) xmlTextReaderConstName( reader );
			
			// Pega os conflitos e dependencias da regra	
			if( node == "conflict" )
			{
				_conflict.name = (char*) xmlTextReaderGetAttribute( reader, (xmlChar*) "name" );
				_conflict.truco_type = (char*) xmlTextReaderGetAttribute( reader, (xmlChar*) "truco_type" );
				conflicts.push_back( _conflict );
			}
			else if( node == "dependence" )
				dependencies.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") );
				
		} while( node != "rule" && reader != NULL );
		// Fim da leitura ate o fechamento da regra
		
		vector <Rule*> rules_deps; // vetor de dependencias da regra
		
		if( check_rule_conflicts(conflicts) )
			if( check_rule_dependencies(attributes[1], dependencies, rules_deps) )
			{
				// Adiciona a funcao callback na regra
				if( attributes[5] != "" )		
					modules.push_back( g_module_open( attributes[5].c_str(), G_MODULE_BIND_LAZY ) );
				else
					modules.push_back( g_module_open( PACKAGE_DATA_DIR"/rules/default.so", G_MODULE_BIND_LAZY ) );
				
				if( modules.back() == NULL)
					return -2;
				
				if( !g_module_symbol( modules.back(), attributes[4].c_str(), (gpointer*)& _callback ) )
					return -3;	
	
				rule = new Rule( attributes[0],
					attributes[1],
					attributes[2],
					attributes[3],
					attributes[4],
					conflicts,
					rules_deps,
					attributes[5],
					( int (*)() ) _callback );
				
				break;
			}
			else
				return -4;
		else
			return -5;
	}
	
	// Termina a libxml
	xmlCleanupParser();
	xmlMemoryDump();
	
	if( rule == NULL )
		return ret;
	else
	{
		rules.push_back(rule);
		return 1;
	}

}

int
Truco::load_rules( const string& _truco_type,
						const string& _file,
						multimap <int, string>& _rule_errors )
{
	LIBXML_TEST_VERSION // Inicia a libxml

	multimap <int, string> rule_errors;
	xmlTextReaderPtr reader;
	Rule* rule = NULL;
	int is_rule_loaded = 0;
	int ( *_callback )( Rule, Truco, vector <void*> );
	
	if( _file != "" )
		reader = xmlReaderForFile( _file.c_str(), NULL, 0 );
	else
		reader = xmlReaderForFile( PACKAGE_DATA_DIR"/rules/default.xml", NULL, 0 );
	
	int file_nfinished = 1;
	
	while( file_nfinished == 1 )
	{
		vector <string> attributes;
		vector <conflict> conflicts;
		conflict _conflict;
		vector <string> dependencies;
		string node;
		
		// Le ate achar a abertura da regra
		int i = 0;
		do
		{
			file_nfinished = xmlTextReaderRead( reader );
			if( file_nfinished == 0 )
				break;
			node = (char*) xmlTextReaderConstName( reader );
			
		}
		while( node != "rule" && reader != NULL );
		// Fim da leitura ate achar uma abertura para regra
		
		if( file_nfinished == 0 )
			break;
		
		// Verifica se a regra eh do tipo de truco pedido
		else if( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "truco_type") != _truco_type )
			continue;
		
		// Pega os atributos da regra
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "truco_type") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "description") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "where_apply") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "cb_name") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "file") );
		
		// Le ate achar o fechamento da regra
		do
		{
			file_nfinished = xmlTextReaderRead( reader );
			if( file_nfinished == 0)
				break;
			node = (char*) xmlTextReaderConstName( reader );
			
			// Pega os conflitos e dependencias da regra	
			if( node == "conflict" )
			{
				_conflict.name = (char*) xmlTextReaderGetAttribute( reader, (xmlChar*) "name" );
				_conflict.truco_type = (char*) xmlTextReaderGetAttribute( reader, (xmlChar*) "truco_type" );
				conflicts.push_back( _conflict );
			}
			else if( node == "dependence" )
				dependencies.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") );
				
		}
		while( node != "rule" && reader != NULL );
		// Fim da leitura ate o fechamento da regra
		
		vector <Rule*> rules_deps; // vetor de dependencias da regra
		
		if( check_rule_conflicts(conflicts) )
			if( check_rule_dependencies(attributes[1], dependencies, rules_deps) )
			{
				// Adiciona a funcao callback na regra
				if( attributes[5] != "" )		
					modules.push_back( g_module_open( attributes[5].c_str(), G_MODULE_BIND_LAZY ) );
				else
					modules.push_back( g_module_open( PACKAGE_DATA_DIR"/rules/default.so", G_MODULE_BIND_LAZY ) );
				
				if( modules.back() == NULL)
				{
					rule_errors.insert( pair <int,string>(-2,attributes[0]) );
					continue;
				}
				
				if( !g_module_symbol( modules.back(), attributes[4].c_str(), (gpointer*)& _callback ) )
				{
					rule_errors.insert( pair <int,string>(-3,attributes[0]) );
					continue;
				}
				
				rule = new Rule( attributes[0],
							attributes[1],
							attributes[2],
							attributes[3],
							attributes[4],
							conflicts,
							rules_deps,
							attributes[5],
							( int (*)() ) _callback );
				rules.push_back( rule );
				
				is_rule_loaded = 1;
			}
			else
				rule_errors.insert( pair <int,string>(-4,attributes[0]) );
		else
			rule_errors.insert( pair <int,string>(-5,attributes[0]) );	
	}
	
	// Termina a libxml
	xmlCleanupParser();
	xmlMemoryDump();
	
	_rule_errors = rule_errors;
	
	if( !is_rule_loaded )
		return -1;
		
	if( !rule_errors.empty() )
		return 0;
	
	return 1;
}
