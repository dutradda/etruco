#include <Card_Game.h>
#include <iostream>
using namespace std;

int
main(int argc, char** argv)
{
	Card_Game* truco = new Card_Game(1, 4, argv[1]);
	multimap <int, string> rule_errors;

	vector <Team*> teams = truco->get_teams();
	vector <Player*> player = truco->get_players();
	Team* team = truco->get_player_team( (*(player.begin()+1)) );

	cout << "Team memory address: " << team << endl;

	for( vector<Team*>::iterator i = teams.begin(); i != teams.end(); i++ )
	{
		team = *i;
		cout << "Team vector memory address: " << team << endl;
	}

	if( argv[2] && argv[3] )	
		rule_errors = truco->load_rules(argv[2], argv[3]);
	else if( argv[2] )
		rule_errors = truco->load_rules(argv[2]);
	else
		rule_errors = truco->load_rules();

	 for( multimap<int, string>::iterator iter = rule_errors.begin(); iter != rule_errors.end(); ++iter )
		cout << "Type error: " << iter->first << ". From rule:" << iter->second << endl;

	 vector <Rule*> rules = truco->get_rules();

	 for( int i = 0; i < rules.size(); ++i  )
	 {
		 cout << "Rule: " << rules[i]->get_name() << ". Card_Game type: " << rules[i]->get_type() << endl;
//		 for( int j = 0; j < rules[i]->get_conflicts().size(); ++j )
//			 cout << "Conflict name: " << rules[i]->get_conflicts()[j].name << ". Type: " << rules[i]->get_conflicts()[j].truco_type << endl;
	 }
	
	 vector <void*> vetor;
	 truco->apply_rule("rule10", vetor);

	delete truco;
	return 0;
}
