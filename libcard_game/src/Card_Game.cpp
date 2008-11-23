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

#include <config.h>

#include "Card_Game.h"

using namespace std;

Card_Game::Card_Game( int _num_players, int _num_teams, const string& _xml_file_name )
{
	int num_team_players = _num_players / _num_teams;
	
	for( int i = 0; i < _num_players; i++ )
		players.push_back( new Player( ) );
	
	vector<Player*>::iterator i = players.begin();
	// Cria as equipes e adiciona os jogadores a elas
	for( int cont = 0; cont < _num_teams; i++, cont++ )
	{
		vector <Player*> aux;
		// Insere todos os jogadores da mesma equipe de uma vez
		for( int j = 0; j < num_team_players; j++ )
			aux.push_back( *(i+(num_team_players*j)) );
		teams.push_back( new Team(aux) );
	}
	
	eina_module_init();
	xml_parser = new XML_Parser( _xml_file_name );
	
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
	
	delete xml_parser;
}

int Card_Game::check_rule_conflicts( vector <Conflict> _conflicts )
{
	for( vector <Rule*>::iterator i = rules.begin(); i != rules.end(); i++ )
		for( vector <Conflict>::iterator j = _conflicts.begin(); j != _conflicts.end(); j++ )
			if( (*i)->get_name() == (*j).name && (*i)->get_type() == (*j).type )
				return 0;
	return 1;
}

int
Card_Game::check_rule_dependencies( string _type,
										vector <string> _dependencies,
										vector <Rule*>& _rules_deps )
{
	int depends = 0;
	vector <string>::iterator i;
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

int Card_Game::apply_rule( const string& _name, vector <void*> _params )
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
	
	int ( *callback )( Rule*, Card_Game*, vector<void*> ) =
		( int (*)( Rule*, Card_Game*, vector<void*> ) ) rule->get_callback().func;
		
	if( !callback(rule, this, _params) )
		return 0;
	else
		return 1;
}

int
Card_Game::load_rules( multimap <int, string>& _rule_errors,
						const string& _attribute_name,
						const string& _attribute_value )
{
	bool has_module = false;
	int ret = 1;
	Conflict conflict;
	Callback callback;
	vector <Node*> nodes = xml_parser->get_children_nodes("rule", _attribute_name, _attribute_value);
	
	if( nodes.size() == 0 )
		ret = 0;
	
	vector <Node*>::iterator i, j;
	for( i = nodes.begin(); i != nodes.end(); i++ )
	{
		vector <Conflict> conflicts;
		vector <string> dependencies;
		for( j = (*i)->children.begin(); j != (*i)->children.end(); j++ )
			if( (*j)->name == "conflict" )
			{
				conflict.name = (*j)->attributes["name"];
				conflict.type = (*j)->attributes["type"];
				conflicts.push_back( conflict );
			}
			else if( (*j)->name == "dependence" )
				dependencies.push_back( (*j)->attributes["name"] );
			else if( (*j)->name == "callback" )
			{
				callback.name = (*j)->attributes["name"];
				callback.module_file_name = (*j)->attributes["module_file_name"];
			}
		
		vector <Rule*> rules_deps;
		if( check_rule_conflicts(conflicts) )
			if( check_rule_dependencies( (*i)->attributes["type"], dependencies, rules_deps) )
			{
				// Verifica se o modulo ja esta carregado
				for( vector<Eina_Module*>::iterator j = modules.begin(); j != modules.end(); j++ )
				{
					callback.func = eina_module_symbol_get( *j, callback.name.c_str() );
					if( callback.func != NULL )
					{
						has_module = true;
						break;
					}
				}
				
				if( !has_module )
				{
					modules.push_back( eina_module_new( callback.module_file_name.c_str() ) );
					if( modules.back() == NULL )
					{
						_rule_errors.insert( pair <int,string>( -3, (*i)->attributes["name"] ) );
						modules.pop_back();
						continue;
					}
					eina_module_load( modules.back() );
					callback.func = eina_module_symbol_get( modules.back(), callback.name.c_str() );
				}
				
				if( callback.func == NULL )
				{
					_rule_errors.insert( pair <int,string>( -4, (*i)->attributes["name"] ) );
					continue;
				}
				
				rules.push_back( new Rule( (*i)->attributes["name"],
													(*i)->attributes["type"],
													(*i)->attributes["description"],
													conflicts,
													rules_deps,
													callback ) );		
			}
			else
				_rule_errors.insert( pair <int,string>( -1, (*i)->attributes["name"] ) );
		else
			_rule_errors.insert( pair <int,string>( -2, (*i)->attributes["name"] ) );
			
	}
	
	xml_parser->free_nodes(nodes);
	
	if( _rule_errors.count(-1) != 0 || _rule_errors.count(-2) != 0 ||
		_rule_errors.count(-3) != 0 || _rule_errors.count(-4) != 0 )
		ret = 0;
	
	return ret;
}

Team* Card_Game::get_player_team( Player* _player )
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
