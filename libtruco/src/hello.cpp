#include <config.h>
#include <iostream>
#include "hello.h"

void hello() {

	std::cout << "Hello" << PACKAGE_STRING << std::endl;
}
