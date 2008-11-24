#include <iostream>
#include <Truco.h>
#include <vector>
using namespace std;

extern "C"

int testando(Rule* rule, Truco* truco, vector <void*> vetor) {
	        cout << "Rule name in testando: " << rule->get_name() << endl;
}

