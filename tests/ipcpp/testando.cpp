#include <iostream>
using namespace std;

extern "C"

int testando(void* data) {
	int* p = (int*) data;
	cout << "Message id in testando: " << *p << endl;
}

