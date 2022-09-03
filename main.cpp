//
// Created by WildBoarGonnaGo on 03.09.2022.
//

#include "computor.h"

int main(int argc, char *argv[]) {
	if (argc != 2)
		std::cerr << "computor: wrong number of arguments." << std::endl;
	std::string src(argv[1]);
	computor comp(src);
	std::cout << comp.to_string() << std::endl;
	return 0;
}