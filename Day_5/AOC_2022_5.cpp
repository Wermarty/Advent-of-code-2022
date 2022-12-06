#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include <string>
#include <array>
#include <vector>

constexpr int stack_number{ 9 };

struct Command {
	
	Command(int number, int from, int to) : number{ number },	from{ from }, to{ to }	{}
	
	int number{};
	int from{};
	int to{};
};

int main()
{
	std::ifstream f{ "input_5.txt", std::ios::in };

	if (!f.good()) {
		throw std::runtime_error("Couldn't open file\n");
	}

	std::string string{};
	getline(f, string); 
	
	//Stacks
	std::array < std::vector<char>, stack_number > stacks{};
	while (!string.empty()) {

		int i{ 0 };
		if (string.at(1) != '1'){
			while (i < stack_number) {
				char c{ string.at((1 + 4 * i)) };

				if (!(c == ' ')) stacks.at(i).push_back({ c }) ;

				i++;
			}
		}
		getline(f, string);
	}

	//Commands
	std::vector<Command> commands{};
	while (getline(f, string)) {

		std::stringstream ss{ string };

		std::string temp1{}, temp2{}, temp3{};

		int number{}, from{}, to{};

		ss >> temp1 >> number >> temp2 >> from >> temp3 >> to;
		assert(temp1 == "move"); assert(temp2 == "from"); assert(temp3 == "to");

		commands.emplace_back(number, from - 1, to - 1);
	}

	//Inverser les vecteurs des stacks

	for (std::vector<char>& v : stacks) {
		std::reverse(v.begin(), v.end());
	}

	auto stacks_copy1{ stacks };
	auto stacks_copy2{ stacks };

	for (Command command : commands) {
		std::vector<char>& from_stack1{ stacks_copy1.at(command.from) };
		std::vector<char>& from_stack2{ stacks_copy2.at(command.from) };

		//Level 1
		for (int i{ 0 }; i < command.number; i++) {
			stacks_copy1.at(command.to).push_back(from_stack1.back());
			from_stack1.pop_back();
		}

		//Level 2
		size_t len{ from_stack2.size() - 1 };
		for (int j{ command.number }; j > 0; j--) {
			stacks_copy2.at(command.to).push_back(from_stack2.at(len - j + 1));
		}
		for (int j{ 0 }; j < command.number; j++) {
			from_stack2.pop_back();
		}
	}

	std::cout << "Level 1 : ";
	for (std::vector<char> v : stacks_copy1) {
		std::cout << v.back();
	}
	std::cout << std::endl << "Level 2 : ";
	for (std::vector<char> v : stacks_copy2) {
		std::cout << v.back();
	}

	return 0;
}