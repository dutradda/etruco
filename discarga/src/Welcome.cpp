#include "Dealer_Rules.h"

using namespace discarga;
using namespace std;

int Welcome::execute( vector<void*>& _data )
{
	
}

// manda as regras que o player deve carregar.
int Welcome::send_my_message( vector<void*>& _data )
{
	Dealer* dealer = (Dealer*) _data.back();
	map<string, Rule*> rules = dealer.get_rules();
	
	char msg;
	int msg_size = rules.size();
	
	
	for( map<string, Rule*>::itarator i = rules.begin(); i != rules.end(); ++i )
	{
		msg_size += i->second->get_module_symbol().module_file_name.size();
	}
}
