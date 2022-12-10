#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


void add2vec(int clk, int X,  std::vector<int>& vec) {
	switch (clk) {
	case 20: vec.push_back(20 * X); break;
	case 60: vec.push_back(60 * X); break;
	case 100: vec.push_back(100 * X); break;
	case 140: vec.push_back(140 * X); break;
	case 180: vec.push_back(180 * X); break;
	case 220: vec.push_back(220 * X); break;
	default :
		break;
	}
}

void print2screen(int clk, int X) {
	if (! (clk%40) ) std::cout << std::endl;

	if (((clk % 40) - X > -1.5) && ((clk % 40) - X < 1.5)) {
		std::cout << '#';
	}
	else {
		std::cout << '.';
	}
}

int main()
{
	std::ifstream f{ "input_10.txt", std::ios::in };

	if (!f.good()) {
		throw std::runtime_error("Couldn't open file\n");
	}

	int clk{ 0 };
	int X{ 1 };
	std::vector<int> vec{};

	std::string string{};
	while (getline(f, string)) {
		std::stringstream ss{ string };

		std::string instruction{};
		int value{ 0 } ;

		ss >> instruction >> value;
		if (instruction.at(0) == 'n') {
			print2screen(clk, X);
			clk++;
			add2vec(clk, X, vec);
		}
		else {
			print2screen(clk, X);
			clk++;
			add2vec(clk, X, vec);
			print2screen(clk, X);
			clk++;
			add2vec(clk, X, vec);
			X += value;
		}
	}


	int level_1{ 0 };
	for (int element : vec) {
		level_1 += element;
	}

	std::cout << std::endl << std::endl << "Level 1 : " << level_1 << std::endl;

	return 0;
}
