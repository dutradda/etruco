/*  
 * Card_Game.cpp
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

#include "Card_Game.h"

using namespace std;
using namespace libcardgame;

Card_Game::Card_Game( const int& _num_team_players,
							const int& _num_teams,
							const string& _xml_file_name )
{
	xml_file_name = _xml_file_name;
	int num_players = _num_team_players*_num_teams;
	
	for( int i = 0; i < num_players; i++ )
		players.push_back( new Player( ) );
	
	vector<Player*>::iterator i = players.begin();
	// Cria as equipes e adiciona os jogadores a elas
	for( int cont = 0; cont < _num_teams; i++, cont++ )
	{
		vector <Player*> aux;
		// Insere todos os jogadores da mesma equipe de uma vez
		for( int j = 0; j < _num_team_players; j++ )
			aux.push_back( *(i+(_num_team_players*j)) );
		teams.push_back( new Team(aux) );
	}
	
	eina_module_init();
}

Card_Game::~Card_Game()
{
	for( vector <Player*>::iterator i = players.begin(); i != players.end(); i++ )
		delete *i;
		
	
	for( vector <Team*>::iterator i = teams.begin(); i != teams.end(); i++ )
		delete *i;
	
	for( vector <Eina_Module*>::iterator i = modules.begin(); i != modules.end(); i++ )
	{
		eina_module_unload(*i);
		eina_module_delete(*i);
	}
	
	eina_module_shutdown();
}

int Card_Game::check_rule_conflicts( const vector <Conflict>& _conflicts )
{
	for( vector <Rule*>::iterator i = rules.begin(); i != rules.end(); i++ )
		for( vector <Conflict>::const_iterator j = _conflicts.begin(); j != _conflicts.end(); j++ )
			if( (*i)->get_name() == (*j).name && (*i)->get_type() == (*j).type )
				return 0;
	return 1;
}

int
Card_Game::check_rule_dependencies( vector <Rule*>& _rules_deps,
										const string& _type,
										const vector <string>& _dependencies )
{
	int depends = 0;
	vector <string>::const_iterator i;
	vector <Rule*>::iterator j;
	
	for( i = _dependencies.begin(); i != _dependencies.end(); i++ )
		for( j = rules.begin(); j != rules.end(); j++ )
			if( *i == (*j)->get_name() && _type == (*j)->get_type() )
				_rules_deps.push_back( *j );
	
	for( i = _dependencies.begin(); i != _dependencies.end(); i++ )
	{
		for( j = _rules_deps.begin(); j != _rules_deps.end(); j++ )
			if( *i == (*j)->get_name() && _type == (*j)->get_type() )
				depends = 1;
		if( !depends )
			return 0;
		depends = 0;
	}
	return 1;
}

int Card_Game::apply_rule( const string& _name, const vector <void*>& _params )
{
	Rule* rule = NULL;
	vector<Rule*>::iterator i;
	for( i = rules.begin(); i != rules.end(); i++)
		if( (*i)->get_name() == _name )
		{
			rule = *i;
			break;
		}
		
	if( rule == NULL )
		return 0;
	else
		return rule->execute(this, _params);
}

multimap <int, string>
Card_Game::load_rules( const string& _attribute_name,
							const string& _attribute_value )
{
	return load_rules_file( xml_file_name, _attribute_name, _attribute_value );
}

multimap <int, string>
Card_Game::load_rules_file( const string& _xml_file_name,
							const string& _attribute_name,
							const string& _attribute_value )
{
	multimap <int, string> rule_errors;
	bool have_module;
	Conflict conflict;
	Module_Symbol module_symbol; // Eh a regra instanciada na biblioteca
	vector <Node*> nodes = xml_parser.get_children_nodes("rule", _xml_file_name, _attribute_name, _attribute_value);
	
	if( nodes.size() == 0 )
	{
		rule_errors.insert( pair <int,string>( 0, "empty" ) );
		return rule_errors;
	}
	
	for( vector <Node*>::iterator i = nodes.begin(); i != nodes.end(); i++ )
	{
		vector <Conflict> conflicts;
		vector <string> dependencies;
		for( vector <Node*>::iterator j = (*i)->children.begin(); j != (*i)->children.end(); j++ )
			if( (*j)->name == "conflict" )
			{
				conflict.name = (*j)->attributes["name"];
				conflict.type = (*j)->attributes["type"];
				conflicts.push_back( conflict );
			}
			else if( (*j)->name == "dependence" )
				dependencies.push_back( (*j)->attributes["name"] );
			
		module_symbol.name = (*i)->attributes["name"];
		module_symbol.module_file_name = (*i)->attributes["module_file_name"];
		vector <Rule*> rules_deps;
		if( check_rule_conflicts(conflicts) )
			if( check_rule_dependencies( rules_deps, (*i)->attributes["type"], dependencies ) )
			{
				// Verifica se o modulo ja esta carregado e pega a regra
				have_module = false;
				for( vector<Eina_Module*>::iterator j = modules.begin(); j != modules.end(); j++ )
				{
					module_symbol.symbol = eina_module_symbol_get( *j, module_symbol.name.c_str() );
					if( module_symbol.symbol != NULL )
					{
						have_module = true;
						break;
					}
				}
				
				// Carrega o modulo e pega a regra
				if( !have_module )
				{
					modules.push_back( eina_module_new( module_symbol.module_file_name.c_str() ) );
					if( modules.back() == NULL )
					{
						rule_errors.insert( pair <int,string>( -3, (*i)->attributes["name"] ) );
						modules.pop_back();
						continue;
					}
					eina_module_load( modules.back() );
					module_symbol.symbol = eina_module_symbol_get( modules.back(), module_symbol.name.c_str() );
				}
				
				if( module_symbol.symbol == NULL )
				{
					rule_errors.insert( pair <int,string>( -4, (*i)->attributes["name"] ) );
					continue;
				}
				
				Rule* new_rule = (Rule*) module_symbol.symbol;
				new_rule->dependencies = rules_deps;
				rules.push_back( new_rule );		
			}
			else
				rule_errors.insert( pair <int,string>( -1, (*i)->attributes["name"] ) );
		else
			rule_errors.insert( pair <int,string>( -2, (*i)->attributes["name"] ) );
	}
	
	xml_parser.free_nodes(nodes);
		
	return rule_errors;
}

Team* Card_Game::get_player_team( const Player* _player )
{
	vector <Player*> team_players;
	vector<Player*>::iterator result;
	
	for( vector<Team*>::iterator j = teams.begin(); j != teams.end(); j++ )
	{
		team_players = (*j)->get_players();
		result = find( team_players.begin(), team_players.end(), _player);
		if( result != team_players.end() )
			return *j;
	}
	
	return NULL;
}
