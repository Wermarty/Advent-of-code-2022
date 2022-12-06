#include <iostream>
#include <fstream>
#include <string>

std::uint64_t constexpr SIZE_BUFFER{ 14 };

int is_in_string(std::string_view string, int n) {
	int len{ static_cast<int>(string.size()) };
	int is_in{ 0 };
	
	for (int i{ n+1 }; i < len; i++) {
		if (string.at(i) == string.at(n)) {
			is_in = 1;
		}
	}
	return is_in;
}

int condition(std::string_view buffer, int n_max) {
	
	int condition{ 0 };
	int i{ 0 };
	while (!condition && i<n_max-1) {
		for (i; i < n_max-1; i++) {
			if (is_in_string(buffer, i)) {
				condition = 1;
			}
		}
	}
	return condition;
}

void rewrite(std::string& s, char last_car, int n) {
	for (int i{ 0 }; i < n; i++) {
		s.at(i) = s.at(i + 1);
	}
	s.at(n) = last_car;
}

int main()
{
	std::ifstream f{ "input_6.txt", std::ios::in };
	if (!f.good()) {
		throw std::runtime_error("Couldn't open file\n");
	}

	std::string string{};
	getline(f, string);

	std::uint64_t marker{ SIZE_BUFFER };
	std::string buffer{ string.substr(0, SIZE_BUFFER) };

	while (condition(buffer, SIZE_BUFFER)){
		rewrite(buffer, string.at(marker), SIZE_BUFFER-1);
		marker++;
	}

	int level{ SIZE_BUFFER == 4 ? 1 : 2 };
	std::cout << "Level " << level << " : " << marker << std::endl;

	return 0;
}
