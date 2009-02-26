#include <discarga.hpp>

namespace discarga
{
	class Welcome : public Rule
	{
		public:
			int execute( vector<void*>& _data );
			int send_my_message( vector<void*>& _data );
	};
	
	class Player_Connected : public Rule
	{
		public:
			int execute( vector<void*>& _data );
			int send_my_message( vector<void*>& _data );
	};
}
