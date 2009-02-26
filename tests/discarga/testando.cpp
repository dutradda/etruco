#include <discarga/Rule.h>
#include <vector>
#include <iostream>

extern "C"

class Rule_Test : public discarga::Rule
{
	public:
		int execute(std::vector<void*>& data)
		{
			std::cout << "UHUU!" << std::endl;
			return 1;
		}

		int send_my_message(std::vector<void*>& data)
		{
			return 1;
		}
};
Rule_Test rule;
Rule_Test rule2;
Rule_Test rule3;
Rule_Test rule4;
Rule_Test rule5;
Rule_Test rule6;
Rule_Test rule7;
Rule_Test rule8;
Rule_Test rule9;
Rule_Test rule10;

