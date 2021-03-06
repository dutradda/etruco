/*  
 * Card.h
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
 
#ifndef DISCARGA_CARD_H
#define DISCARGA_CARD_H

namespace discarga
{
	/**
	 * The card class.
	 */
	class Card
	{	
		public:
			/**
			 * Constructor
			 *
			 * @param _value
			 *  The card's value
			 *
			 * @param _suit
			 *  The card's suit
			 */
			Card( int _value, int _suit ) : value( _value ), suit( _suit ) { };
			
			/**
			 * Gets the card's value.
			 */
			inline int get_value() { return value; };
			
			/**
			 * Gets the card's suit.
			 */
			inline int get_suit() { return suit; };
			
			/**
			 * The = operator
			 */
			//inline Card operator=( Card& _card );
			
			/**
			 * The == operator
			 */
			friend inline bool operator==( const Card& _card, const Card& _card2 );
			
		private:
			int value; /**< The card's value */
			int suit; /**< The card's suit */		
	};
};

/*inline
discarga::Card discarga::Card::operator=( Card& _card )
{
this->value = _card.get_value();
this->suit = _card.get_suit();

return *this;
}*/

inline
bool discarga::operator==( const discarga::Card& _card, const discarga::Card& _card2 )
{
if( _card.value == _card2.value && _card.suit == _card2.suit )
	return true;
else
	return false;
}

#endif
