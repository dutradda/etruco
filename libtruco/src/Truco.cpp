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

Truco::Truco( int num_players, int num_teams=2 )
{
	int num_team_players = num_players / num_teams;
	
	for( int i = 0; i < num_players; i++ )
		players.push_back( new Player() );
	
	// Cria as equipes e adiciona os jogadores a elas
	for( int i = 0; i < num_teams; i++ )
	{
		vector <Player*> aux;
		// insere todos os jogadores da mesma equipe de uma vez
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

int Truco::load_rule( const string& _rule, const string& _truco_type, const string& _file = "" )
{	
	LIBXML_TEST_VERSION
	
	int ret; // Retorno da funcao, pode ser -1, 0 e 1
	xmlTextReaderPtr reader;
	if( _file != "" )
		reader = xmlReaderForFile( _file.c_str(), NULL, 0 );
	else
		reader = xmlReaderForFile( PACKAGE_DATA_DIR"/rules/default.xml", NULL, 0 );
	
	int file_finished = 1;
	
	while( file_finished == 1 )
	{
		vector <string> attributes;
		vector <string> conflicts;
		vector <string> dependencies;
		string node;
		
		// Leio até achar a abertura da regra
		int i = 0;
		do
		{
			file_finished = xmlTextReaderRead( reader );
			if( file_finished == 0 )
				break;
			node = (char*) xmlTextReaderConstName( reader );
			
		} while( node != "rule" && reader != NULL );
		
		if( file_finished == 0 )
			break;
			
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
		
		// Pego os atributos da regra
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "truco_type") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "description") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "where_apply") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "cb_name") );
		attributes.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "file") );
		
		// Leio até achar o fechamento da regra
		do
		{
			file_finished = xmlTextReaderRead( reader );
			if( file_finished == 0)
				break;
			node = (char*) xmlTextReaderConstName( reader );
			
			// Pego os conflitos e dependencias da regra	
			if( node == "conflict" )
				conflicts.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") );
			else if( node == "dependence" )
				dependencies.push_back( (char*) xmlTextReaderGetAttribute(reader, (xmlChar*) "name") );
				
		} while( node != "rule" && reader != NULL );
		
		Rule rule( attributes[0],
					attributes[1],
					attributes[2],
					attributes[3],
					attributes[4],
					conflicts,
					dependencies,
					attributes[5] );
		
		// Adiciona a funcao callback na regra
		if( attributes[5] != "" )		
			modules.push_back( g_module_open( attributes[5].c_str(), G_MODULE_BIND_LAZY ) );
		else
			modules.push_back( g_module_open( PACKAGE_DATA_DIR"/rules/default.so", G_MODULE_BIND_LAZY ) );
		
		if( modules.back() == NULL)
			return -2;
		
		if( !g_module_symbol( modules.back(), attributes[4].c_str(), (gpointer*)& rule.callback ) )
			return -2;
					
		rules.push_back( rule );
		
		break;
	}
	
	if( rules.empty() )
		return ret;
	else
		return 1;

}
