#include <vector>
#include <discarga.hpp>

namespace truco_paulista
{
	/*
	* REGRA PARA DISTRIBUIR AS CARTAS AOS JOGADORES
	*/
	class Give_Cards : public discarga::Rule
	{
		friend class Pick_Vira;	

		public:
			Give_Cards( int _deck_size );
			~Give_Cards();
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );

		private:
			int round;
			int mao_value;
			int asks;
			bool truco_accepted;
			bool truco_rejected;
			
			discarga::Deck* deck;
			std::vector<discarga::Card*> cards;
	};

	/*
	 * REGRA PARA DEFINIR MANILHA
	 */
	class Pick_Vira : public discarga::Rule
	{
		friend class Play_Card;

		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );
		
		private:
			int manilhas;

			discarga::Card* card;
	};

	/*
	 * REGRA PARA JOGAR UMA CARTA
	 */
	class Play_Card : public discarga::Rule
	{
		struct Registry
		{
			char player_id;
			char card_value;
			char card_suit;
		};

		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );

		private:
			Registry registred_plays[4];
			char turn_params[3];	
	};

	/*
	 * REGRA PARA DEFINIR GANHADOR DA RODADA
	 */
	class Round_Winner : public discarga::Rule
	{
		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );

		private:
			char team1;
			char team2;
			char team_winner;
		//	int team1_points = 0;
		//	int team2_points = 0;
		//	bool draw = false;
	};

	/*
	 * REGRA PARA INFORMAR ESTADO DE MAO DE ONZE
	 */
	class Mao_Onze : public discarga::Rule
	{
		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );
	};

	/*
	 * REGRA PARA INFORMAR ESTADO DE MAO DE FERRO
	 */
	class Mao_Ferro : public discarga::Rule
	{
		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );
	};

	/*
	 * REGRA PARA IMPLEMENTAR O PEDIDO DE TRUCO ACEITO
	 */
	class Truco_Accepted : public discarga::Rule
	{
		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );
	};

	/*
	 * REGRA PARA IMPLEMENTAR O PEDIDO DE TRUCO REJEITADO
	 */
	class Truco_Rejected : public discarga::Rule
	{
		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );
	};

	/*
	 * REGRA PARA DEFINIR GANHADOR DA MAO
	 */
	class Mao_Winner : public discarga::Rule
	{
		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );
	};

	/*
	 * REGRA PARA DETERMINAR O GANHADOR DO JOGO
	 */
	class Game_Winner : public discarga::Rule
	{		
		public:
			int execute( std::vector<void*>& _data );
			int send_my_message( std::vector<void*>& _data );
	};
}
