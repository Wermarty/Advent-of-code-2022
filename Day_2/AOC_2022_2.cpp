#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int whoWin(char c, char b) {
	//Draw
	if (c == b) {
		return 3;
	}
	//Rock against ...
	else if (c == 'A') {
		return (b == 'C' ? 0 : 6);
	}
	//Paper against ...
	else if (c == 'B') {
		return (b == 'A' ? 0 : 6);
	}
	//Scissors against ...
	else {
		return (b == 'B' ? 0 : 6);
	}
}

char swap(char c) {
	switch (c) {
	case 'X': return 'A';
	case 'Y': return 'B';
	case 'Z': return 'C';
	default:
		std::cout << "ERROR";
		exit(EXIT_SUCCESS);
	}
}

int value(char c) {
	switch (c) {
	case 'A': return 1;
	case 'B': return 2;
	case 'C': return 3;
	default:
		return 0;
	}
}

char lose(char b) {
	switch (b) {
	case 'A': return 'C';
	case 'B': return 'A';
	case 'C': return 'B';
	default:
		return 0;
	}
}
char win(char b) {
	switch (b) {
	case 'A': return 'B';
	case 'B': return 'C';
	case 'C': return 'A';
	default:
		return 0;
	}
}
char manage(char b, char c) {
	switch (c) {
	case 'X': return lose(b);
	case 'Y':return b;
	case 'Z': return win(b);
	default:
		return 0;
	}
}


int main()
{
	std::ifstream f{};
	f.open("input_2.txt", std::ios::in);



	if (!f.is_open()) {
		exit(EXIT_SUCCESS);
	}


	std::vector<char> my_play{};
	std::vector<char> new_play{};
	std::vector<char> elf_play{};
	std::string string{};

	int num_game{ 0 };

	while (getline(f, string)) {

		if (!string.empty()) {
			elf_play.push_back(string.at(0));
			my_play.push_back(swap(string.at(2)));
			new_play.push_back(manage(string.at(0), string.at(2)));

			num_game++;
		}
	}

	f.close();


	int score{ 0 };
	int new_score{ 0 };

	for (int i{ 0 }; i < num_game; i++) {
		score += whoWin(elf_play.at(i), my_play.at(i)) + value(my_play.at(i));
		new_score += whoWin(elf_play.at(i), new_play.at(i)) + value(new_play.at(i));
	}

	std::cout << "level 1 : " << score << std::endl;
	std::cout << "level 2 : " << new_score << std::endl;
}
