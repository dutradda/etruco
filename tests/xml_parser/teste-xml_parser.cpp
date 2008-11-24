#include <XML_Parser.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv)
{
	XML_Parser xml_parser = XML_Parser();
	vector <Node*> nodes;
	if( argv[3] && argv[4] )
		nodes = xml_parser.get_children_nodes( argv[2], argv[1], argv[3], argv[4] );
	else if( argv[3] )
		nodes = xml_parser.get_children_nodes( argv[2], argv[1], argv[3] );
	else
		nodes = xml_parser.get_children_nodes( argv[2], argv[1] );

	int i, j, k;
	for( i = 0; i < nodes.size(); ++i ){
		cout << "Attributes:" << nodes[i]->attributes["name"] << ", " << nodes[i]->attributes["truco_type"] << endl;
		cout << "Children of: " << nodes[i]->name << endl;
		for( j = 0; j < nodes[i]->children.size(); ++j ){
			cout << "\t\t" << nodes[i]->children[j]->name << " Attributes: " << nodes[i]->children[j]->attributes["name"] << ", " << nodes[i]->children[j]->attributes["truco_type"] <<  endl;
			for( k = 0; k < nodes[i]->children[j]->children.size(); ++k )
				cout << "\t\t\t" << nodes[i]->children[j]->children[k]->name << endl;
		}
	}
	
	xml_parser.free_nodes( nodes );

	return 0;
}
