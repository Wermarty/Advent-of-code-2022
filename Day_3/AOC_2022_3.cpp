#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <vector>

int prioritize(char c) {
	int int_value{ static_cast<int>(c) };
	return (int_value > 96 ? int_value - 96 : int_value - 38);
}

class Rucksack {
private:
	std::string m_first_item{};
	std::string m_second_item{};
	
	int m_priority{};

public:
	Rucksack(std::string content) {
		int lengh_item = static_cast<int>(content.size()/2);
		m_first_item = content.substr(0, lengh_item);
		m_second_item = content.substr(lengh_item);

		char car{};
		for (char c : m_first_item) {
			for (char d : m_second_item) {
				if (c == d) {
					car = c;
				}
			}
		}
		m_priority = prioritize(car);
	}

	int getPriority() const {
		return m_priority;
	}
};


class Group {
private :
	char m_badge{};

public:
	Group(std::array<std::string, 3> content){
		
		for (char c : content.at(0)) {
			int first_bool{ 0 };
			int second_bool{ 0 }; 

			for (char d : content.at(1)) {
				if (c == d) {
					first_bool = 1;
				}
			}

			for (char d : content.at(2)) {
				if (c == d) {
					second_bool = 1;
				}
			}

			if (first_bool && second_bool) {
				m_badge = c;
			}
		}
	}

	int getBadge() const {
		return prioritize(m_badge);
	}

};
int main()
{
	std::ifstream f{};
	f.open("input_3.txt", std::ios::in);
	if (!f.is_open()) {
		exit(EXIT_SUCCESS);
	}

	std::vector<Rucksack> rucksacks{};
	std::vector<Group> groups{};

	int circular_count{ 0 };

	std::string string{};
	std::array<std::string, 3> group_bag{};

	while (getline(f, string)) {
		rucksacks.push_back({ string });
		
		group_bag.at(circular_count) = string;
		circular_count++;

		if (circular_count > 2) {
			groups.push_back({ group_bag });
			circular_count = 0;
			
			for (std::string sstring : group_bag) {
				sstring.erase();
			}
		}
	}

	f.close();


	int sum{ 0 };
	for (Rucksack sack : rucksacks) {
		sum += sack.getPriority();
	}

	int sum_badge{ 0 };
	for (Group group : groups) {
		sum_badge += group.getBadge();
	}

	std::cout << "Level 1 : " << sum << std::endl;
	std::cout << "Level 2 : " << sum_badge << std::endl;
	
	return 0;
}
