#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Range {
private:
	int m_beginning{};
	int m_end{};
public:
	Range() = default;
	Range(int beginning, int end) :
		m_beginning{ beginning },
		m_end{ end }
	{
	}

	int begin() const {	return m_beginning;	}
	int end()	const { return m_end; }
};


class Pair {
private:
	Range m_first_range{};
	Range m_second_range{};
public:
	Pair(const std::string_view& input) {
		std::string temp_first{};
		std::string temp_second{};
		int i{ 0 };
		int begin{ 0 };

		while (input.at(i) != '-') {
			i++;
		}
		temp_first = input.substr(begin, i);
		i++; begin = i;
		while (input.at(i) != ',') {
			i++;
		}
		temp_second = input.substr(begin, i);
		m_first_range = { stoi(temp_first), stoi(temp_second) };
		
		i++; begin = i;
		while (input.at(i) != '-') {
			i++;
		}
		temp_first = input.substr(begin, i);
		i++;
		temp_second = input.substr(i, input.size() - i);
		m_second_range = { stoi(temp_first), stoi(temp_second) };
	}
	
	int one_contain_other() const{
		return m_first_range.begin() >= m_second_range.begin() && m_first_range.end() <= m_second_range.end()
			|| m_first_range.begin() <= m_second_range.begin() && m_first_range.end() >= m_second_range.end();
	}
	int overlap() const{
		return m_first_range.end() >= m_second_range.begin() && m_first_range.begin() <= m_second_range.end();
	}
};


int main()
{
	std::ifstream f{};
	f.open("input_4.txt", std::ios::in);

	if (!f.is_open()) {
		exit(EXIT_SUCCESS);
	}

	std::vector<Pair> pairs{};

	std::string string{};
	while (getline(f, string)) {
		pairs.push_back({ string });
	}

	f.close();

	int contained{ 0 };
	int overlaped{ 0 };
	for (Pair pair : pairs) {
		contained += pair.one_contain_other();
		overlaped += pair.overlap();
	}

	std::cout << "Level 1 : " << contained << std::endl;
	std::cout << "Level 2 : " << overlaped << std::endl;
	
	return 0;
}
