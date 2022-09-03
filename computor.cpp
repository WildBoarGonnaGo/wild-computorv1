//
// Created by WildBoarGonnaGo on 20.08.2022.
//

#include "computor.h"
#include <cctype>
#include <cstring>
#include <utility>
#include <cmath>

computor::computor() {}

computor::computor(const std::string &src) : degree(0), polys(new std::vector<double>(3)),
	mirror(1), to_pass(std::move(src)), res(std::string()) {
	if (to_pass.empty())
		return ;
	it = to_pass.begin();
	degree = 2;
	parse();
	res.append("Polynomial degree: ");
	res.append(std::to_string(degree));
	res.push_back('\n');
	if (!degree) cheq();
	if (degree == 1) solution1d();
	if (degree == 2) solution2d();
	if (degree > 2)
		res.append("The polynomial degree is strictly greater than 2, I can't solve");
}

void computor::pass() {
	while (it != to_pass.end() && isblank(*it)) ++it;
}

void del_trailer(std::string &src) {
	int end;

	end = src.size() - 1;
	while (src[end] == '0' || src[end] == '.') --end;
	src.resize(end + 1);
}

void computor::syntax_err() {
	unsigned long pos;

	pos = it - to_pass.begin();
	std::cerr << "computor: " << to_pass << std::endl;
	for (unsigned long i = 0; i < strlen("computor: ") + pos; ++i)
		std::cerr << ' ';
	std::cerr << '^' << std::endl;
	std::cerr << "syntax error" << std::endl;
	exit(-1);
}

double computor::get_number() {
	double rain;
	bool point;
	std::string number;

	point = false;
	number = std::string();
	rain = 0;
	while (it != to_pass.end() && ((std::isdigit(*it)
		|| (*it == '.' && point == false)))) {
			if (*it == '.' && !point) point = true;
			number.push_back(*it);
			++it;
	}
	if (!number.empty()) rain = std::stod(number);
	return rain;
}

int computor::get_int_number() {
	int rain;
	std::string number;

	number = std::string();
	rain = 0;
	while (it != to_pass.end() && std::isdigit(*it)) {
		if (*it == '.') syntax_err();
		number.push_back(*it);
		++it;
	}
	if (!number.empty()) rain = std::stoi(number);
	return rain;
}

void computor::del_trailer() {
	int size;

	size = res.size() - 1;
	while (res[size] == '0' || res[size] == '.')
		if (res[size--] == '.') break ;
	res.resize(size + 1);
}

void computor::fract() {
	unsigned long aux_degree;
	double arg;
	int multi;
	bool if_arg;

	pass();
	multi = 1;
	if_arg = true;
	if (it == to_pass.end()) return ;
	if (*it == '=') {
		mirror = -1;
		++it;
	}
	pass();
	if (*it == '-') {
		multi = -1;
		++it;
	}
	else if (*it == '+') ++it;
	pass();
	if (!std::isdigit(*it) && *it != '.') {
		arg = 1.0;
		if_arg = false;
	}
	else arg = get_number();
	pass();
	if (*it == '+' || *it == '-') {
		polys->operator[](0) += arg * mirror * multi;
		fract();
		return ;
	}
	if (*it == '=') {
		polys->operator[](0) += arg * mirror * multi;
		fract();
		return ;
	}
	if (*it && *(it++) != '*' && if_arg) syntax_err();
	if (!*it) return ;
	if (!if_arg) --it;
	pass();
	if (*it && *(it++) != 'X') syntax_err();
	if (!*it) return ;
	pass();
	aux_degree = (*(it++) == '^') ? get_int_number() : 1;
	if (aux_degree > polys->size() - 1) {
		polys->resize(aux_degree + 1);
		degree = aux_degree;
	}
	polys->operator[](aux_degree) += arg * mirror * multi;
	fract();
}

void computor::parse() {
	fract();
	int final_degree = degree;

	res.append("Reduced form: ");
	for (int i = degree; i > -1; --i) {
		if (polys->operator[](i)) {
			if (i != final_degree) {
				res.push_back((polys->operator[](i) < 0) ? '-' : '+');
				res.push_back(' ');
			}
			if (i == final_degree && polys->operator[](i) < 0)
				res.push_back('-');
			res.append((i == degree && polys->operator[](i) > 0)
				? std::to_string(polys->operator[](i))
				: std::to_string(abs(polys->operator[](i))));
			del_trailer();
			res.push_back(' ');
			if (i > 0) {
				res.append("* X^");
				res.append(std::to_string(i));
				del_trailer();
				res.push_back(' ');
			}
		}
		if (!polys->operator[](final_degree) && final_degree) --final_degree;
	}
	res.append("= 0\n");
	degree = final_degree;
}

void computor::solution1d() {
	double sol;

	sol = -1.0 * polys->operator[](0) / polys->operator[](1);
	res.append("The solution is:\n");
	res.append(std::to_string(sol));
	del_trailer();
}

void computor::solution2d() {
	double dis;

	dis = polys->operator[](1) * polys->operator[](1)
			- 4 * polys->operator[](2) * polys->operator[](0);
	if (dis >= 0) posdis(dis);
	else negdis(dis);
}

void computor::posdis(double dis) {
	double sol[2] = {0};

	sol[0] = (-1.0 * polys->operator[](1) + sqrt(dis)) /
			(2 * polys->operator[](2));
	sol[1] = (-1.0 * polys->operator[](1) - sqrt(dis)) /
			 (2 * polys->operator[](2));
	res.append("The solution is:\n");
	res.append(std::to_string(sol[1]));
	del_trailer();
	if (dis) {
		res.push_back('\n');
		res.append(std::to_string(sol[0]));
		del_trailer();
	}
}

void computor::negdis(double dis) {
	double sol[2] = {0};

	sol[0] = (-1.0 * polys->operator[](1)) / (2 * polys->operator[](2));
	sol[1] = sqrt(abs(dis)) / (2 * polys->operator[](2));
	res.append("The solution is:\n");
	res.append(std::to_string(sol[0]));
	del_trailer();
	res.append(" + ");
	res.append(std::to_string(sol[1]));
	del_trailer();
	res.append(" * i\n");
	res.append(std::to_string(sol[0]));
	del_trailer();
	res.append(" - ");
	res.append(std::to_string(sol[1]));
	del_trailer();
	res.append(" * i");
}

void computor::cheq() {
	if (polys->operator[](0)) {
		res.append(std::to_string(polys->operator[](0)));
		del_trailer();
		res.append(" is not equal to 0");
	} else
		res.append("0 is equal to 0, of course. Yep!");
}

const std::string& computor::to_string() {
	return res;
}

computor::~computor() {
	delete polys;
}