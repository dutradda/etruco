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
			aux.push_back( players[(i+(num_team_players*j)] );
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
}
