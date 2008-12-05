#include <vector>

/*
 * REGRA PARA DISTRIBUIR AS CARTAS AOS JOGADORES
 */

class Give_Cards : public Rule
{
	friend class Pick_Vira;	

	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );

	private:
		int round = 4;
		int mao_value = 1;
		int asks = 0;
		bool truco_accepted = false;
		bool truco_rejected = false;
		
		Deck* deck;
		vector<Card*> cards;
};

/*
 * REGRA PARA DEFINIR MANILHA
 */

class Pick_Vira : public Rule
{
	friend class Play_Card;

	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );
	
	private:
		int manilhas;

		Card* card;
};

/*
 * REGRA PARA JOGAR UMA CARTA
 */

class Play_Card : public Rule
{
	struct Registry
	{
		char player_id;
		char card_value;
		char card_suit;
	};

	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );

	private:
		Registry registred_plays[4];
		char[3] turn_params;	
};

/*
 * REGRA PARA DEFINIR GANHADOR DO ROUND
 */

class Round_Winner : public Rule
{
	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );

	private:
		char team1;
		char team2;
		char team_winner;
		int team1_points = 0;
		int team2_points = 0;
		bool draw = false;
};

/*
 * REGRA PARA INFORMAR ESTADO DE MAO DE ONZE
 */

class Mao_Onze : public Rule
{
	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );
};

/*
 * REGRA PARA INFORMAR ESTADO DE MAO DE FERRO
 */

class Mao_Ferro : public Rule
{
	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );
};

/*
 * REGRA PARA IMPLEMENTAR O PEDIDO DE TRUCO ACEITO
 */

class Truco_Accepted : public Rule
{
	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );
};

/*
 * REGRA PARA IMPLEMENTAR O PEDIDO DE TRUCO REJEITADO
 */

class Truco_Rejected : public Rule
{
	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );
};

/*
 * REGRA PARA DEFINIR GANHADOR DO ROUND
 */

class Mao_Winner : public Rule
{
	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );
};

/*
 * REGRA PARA DETERMINAR O GANHADOR DO JOGO
 */

class Game_Winner : public Rule
{		
	public:
		void execute( vector<void*>& _data );
		int send_my_message( vector<void*>& _data );
};
