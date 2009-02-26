/*  
 * Rule_Handler.cpp
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

#include "Rule_Handler.h"
#include <iostream>

using namespace std;
using namespace discarga;

Rule_Handler::Rule_Handler( const string& _xml_file_name )
{
	xml_file_name = _xml_file_name;
		
	eina_module_init();
}

Rule_Handler::~Rule_Handler()
{
	for( vector <Eina_Module*>::iterator i = modules.begin(); i != modules.end(); i++ )
	{
		eina_module_unload(*i);
		eina_module_delete(*i);
	}
	
	eina_module_shutdown();
}


int Rule_Handler::check_rule_conflicts( const vector <Conflict>& _conflicts, const string& _name )
{	
	map <string, Rule*>::iterator result;
	for( vector <Conflict>::const_iterator i = _conflicts.begin(); i != _conflicts.end(); i++ )
	{
		result = rules.find( i->name );
		if( result != rules.end() && result->second->type == i->type )
			return 0;
	}
	
	for(map <string, Rule*>::iterator i = rules.begin(); i != rules.end(); ++i )
		for( vector <Conflict>::const_iterator j = i->second->conflicts.begin(); j != i->second->conflicts.end(); ++j )
			if( j->name == _name )
				return 0;
		
	return 1;
}

int
Rule_Handler::check_rule_dependencies( map <string, Rule*>& _rules_deps,
										const string& _type,
										const vector <string>& _dependencies,
										const string& _xml_file_name )
{
	multimap <int, string> rule_errors;
	map <string, Rule*> rules_loaded_now;
	map <string, Rule*>::iterator result;
	for( vector <string>::const_iterator i = _dependencies.begin(); i != _dependencies.end(); i++ )
	{
		result = rules.find( *i );
		if( result != rules.end() && result->second->type == _type )
			_rules_deps[*i] = result->second;
		else
		{ // se uma dependencia nao estiver carregada, tenta carregar agora
			rule_errors = load_rules_file( _xml_file_name, _type, *i );
			if( rule_errors.empty() )
			{
				rules_loaded_now[*i] = rules.find( *i )->second;
				_rules_deps[*i] = rules.find( *i )->second;
			}
			else
			{ // se deu problema em carregar alguma dependencia, remove as carregadas automaticamente
				for( map <string, Rule*>::iterator i = rules_loaded_now.begin(); i != rules_loaded_now.end(); ++i )
					unload_rule( i->second->name );
				return 0;
			}
		}
	}
	
	return 1;
}

int Rule_Handler::apply_rule( const string& _name, vector <void*>& _data/*, const int& _who_sent*/ )
{
	map <string, Rule*>::iterator result = rules.find( _name );
	if( result != rules.end() )
	{
		//_data.push_back( (void*) _who_sent );
		//_data.push_back( this );
		return rules[_name]->execute( _data );
	}
	
	return 0;
}

int Rule_Handler::unload_rule( const string& _name )
{
	map <string, Rule*>::iterator result = rules.find( _name );
	if( result != rules.end() )
	{
		rules.erase( result );
		return 1;
	}
	
	return 0;
}

int Rule_Handler::unload_rule_type( const string& _type )
{
	int ret = 0;
	map <string, Rule*>::iterator i = rules.begin();
	while(  i != rules.end() )
		if( i->second->get_type() == _type )
		{
			ret = 1;
			delete i->second;
			rules.erase( i++ );
		}
	
	return ret;
}

multimap <int, string>
Rule_Handler::load_rules( const string& _type,
							const string& _name )
{
	return load_rules_file( xml_file_name, _type, _name );
}

multimap <int, string>
Rule_Handler::load_rules_file( const string& _xml_file_name,
							const string& _type,
							const string& _name )
{
	multimap <int, string> rule_errors;
	bool have_module;
	Conflict conflict;
	Module_Symbol module_symbol; // Eh a regra instanciada na biblioteca
	vector <Node*> nodes;
	map<string, string> mrules; // Um multimap com o tipo e/ou nome da regra
	
	if( _type == "" )
		nodes = XML_Parser::get_children_nodes( "rule", _xml_file_name, mrules );
	else if( _name == "" )
	{
		mrules["type"] = _type;
		nodes = XML_Parser::get_children_nodes( "rule", _xml_file_name, mrules );
	}
	else
	{
		mrules["type"] = _type;
		mrules["name"] = _name;
		nodes = XML_Parser::get_children_nodes( "rule", _xml_file_name, mrules );
		
		/*for( vector <Node*>::iterator i = tmp.begin(); i != tmp.end(); i++ )
			if( (*i)->attributes["type"] == _type )
			{
				nodes.push_back( *i );
				break;
			}*/
	}
	
	if( nodes.size() == 0 )
	{
		rule_errors.insert( pair <int,string>( 0, "empty" ) );
		return rule_errors;
	}
	
	map <string, Rule*>::iterator result;
	for( vector <Node*>::iterator i = nodes.begin(); i != nodes.end(); i++ )
	{
		// verifica se a regra jah estah carrregada
		result = rules.find( (*i)->attributes["name"] );
		if( result != rules.end() && result->second->type == (*i)->attributes["type"] )
		{
			rule_errors.insert( pair <int,string>( -5, (*i)->attributes["name"] ) );
			continue;
		}
		
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
			else if( (*j)->name == "instance" )
			{
				module_symbol.name = (*j)->attributes["name"];
				module_symbol.module_file_name = (*j)->attributes["module_file_name"];
			}
		
		map <string, Rule*> rules_deps;
		if( check_rule_conflicts(conflicts, (*i)->attributes["name"]) )
			if( check_rule_dependencies( rules_deps, (*i)->attributes["type"], dependencies, _xml_file_name ) )
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
					if( !eina_module_load( modules.back() ) )
					{
						rule_errors.insert( pair <int,string>( -3, module_symbol.module_file_name ) );
						modules.pop_back();
						continue;
					}
					module_symbol.symbol = eina_module_symbol_get( modules.back(), module_symbol.name.c_str() );
					
					if( module_symbol.symbol == NULL )
					{
						rule_errors.insert( pair <int,string>( -4, (*i)->attributes["name"] ) );
						continue;
					}
				}
				
				Rule* new_rule = (Rule*) module_symbol.symbol;
				new_rule->id = atoi( (*i)->attributes["id"].c_str() );
				new_rule->name = (*i)->attributes["name"];
				new_rule->type = (*i)->attributes["type"];
				new_rule->description = (*i)->attributes["description"];
				new_rule->dependencies = rules_deps;
				new_rule->conflicts = conflicts;
				module_symbol.symbol = NULL;
				new_rule->module_symbol = module_symbol;
				rules[new_rule->name] = new_rule;
			}
			else
				rule_errors.insert( pair <int,string>( -1, (*i)->attributes["name"] ) );
		else
			rule_errors.insert( pair <int,string>( -2, (*i)->attributes["name"] ) );
	}
	
	cout << rules.size() << endl;
	for(map <string, Rule*>::iterator j = rules.begin(); j != rules.end(); ++j )
					cout << j->second->name << " " << j->second->type << " " << j->first << endl;
	
	XML_Parser::free_nodes(nodes);
			
	return rule_errors;
}
