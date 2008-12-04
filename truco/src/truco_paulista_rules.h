#include <vector>

class game_winner : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class give_cards : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class mao_ferro : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class mao_onze : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class mao_winner : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class pick_vira : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class play_card : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class round_winner : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class truco_accepted : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};

class truco_rejected : public Rule
{
	public:
		void execute( vector<void*>& v );
		int send_my_message( vector<void*>& v );
};
