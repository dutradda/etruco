/*  
 * Deck_Baralho_Sujo.h
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
 
#ifndef DECK_BARALHO_SUJO_H
#define DECK_BARALHO_SUJO_H

/**
 * The deck with the rule 'Baralho Sujo'.
 */
class Deck_Baralho_Sujo : public Deck
{
	public:
		/**
		 * Constructor
		 */
		Deck_Baralho_Sujo();
		
		/**
		 * Choose the 'o vira' card
		 *
		 * @return
		 *  The 'o vira' card
		 */
		Card pick_o_vira();
		
		/**
		 * Get a copy of the 'manilhas' cards
		 */
		vector <Card> get_manilhas();
	
	private:
		Card* vira; /**< The card choosed to be 'o vira' */
		vector <Card*> manilhas; /**< The cards called 'manilhas' */
}
