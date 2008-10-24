/*  
 * Deck.h
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
 
#ifndef DECK_H
#define DECK_H

#include "Card.h"

/**
 * The deck class.
 */
class Deck
{
	public:
		/**
		 * Default Constructor.
		 *
		 * @param _size
		 *  The number of cards per suit.
		 */
		Deck(int _size);
		
		/**
		 * Destructor.
		 */
		Deck();
		
		/**
		 * Shuffle the deck.
		 */
		void Shuffle();
		
		/**
		 * Gets three cards from deck.
		 */
		vector <Card*> get_3cards();
	
	protected:
		vector <Card*> cards; /**< The deck's cards */
		
	private:
		char get_cards_count = 0; /**< Counts the number of cards geted */
	
}
