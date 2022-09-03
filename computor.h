//
// Created by WildBoarGonnaGo on 20.08.2022.
//

#ifndef WILD_COMPUTORV1_COMPUTOR_H
#define WILD_COMPUTORV1_COMPUTOR_H

#include <string>
#include <vector>
#include <iostream>

class computor {
	int degree;
	std::vector<double> *polys;
	int mirror;
	computor();
	void del_trailer();
	std::string::const_iterator it;
	int get_int_number();
	double get_number();
	std::string to_pass;
	std::string res;
	void fract();
	void parse();
	void pass();
	void syntax_err();
	void solution1d();
	void posdis(double dis);
	void negdis(double dis);
	void cheq();
	void solution2d();
	std::string&& complex_dis();
public:
	computor(const std::string &src);
	const std::string& to_string();
	~computor();
};


#endif //WILD_COMPUTORV1_COMPUTOR_H
