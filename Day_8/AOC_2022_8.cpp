#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Tree {
	Tree(int size, bool b) : size{ size }, ever_count{ b }{}

	int size{};
	bool ever_count{};
};

void check_left_to_middle(std::vector < std::vector<Tree>>& map) {
	int nb_row{ static_cast<int>(map.size()) };
	int nb_col{ static_cast<int>(map.at(0).size()) };

	for (int i{ 0 }; i < nb_row; i++) {
		int max{ -1 };
		for (int j{ 0 }; j < nb_col; j++) {
			if (!j) {
				map.at(i).at(j).ever_count = true;
				max = map.at(i).at(j).size;
			}
			else {
				if (max < map.at(i).at(j).size) {
					map.at(i).at(j).ever_count = true;
					max = map.at(i).at(j).size;
				}
			}
			if (max == 9) break;
		}
	}
}
void check_right_to_middle(std::vector < std::vector<Tree>>& map) {
	int nb_row{ static_cast<int>(map.size()) };
	int nb_col{ static_cast<int>(map.at(0).size()) - 1 };
	
	for (int i{ 0 }; i < nb_row; i++) {
		int max{ -1 };
		for (int j{ nb_col }; j >= 0; j--) {
			if (j == nb_col) {
				map.at(i).at(j).ever_count = true;
				max = map.at(i).at(j).size;
			}
			else {
				if (max < map.at(i).at(j).size) {
					map.at(i).at(j).ever_count = true;
					max = map.at(i).at(j).size;
				}
			}
			if (max == 9) break;
		}
	}
}
void check_top_to_middle(std::vector < std::vector<Tree>>& map) {
	int nb_row{ static_cast<int>(map.size()) };
	int nb_col{ static_cast<int>(map.at(0).size()) };

	for (int j{ 0 }; j < nb_col; j++) {
		int max{ -1 };
		for (int i{ 0 }; i < nb_row; i++) {
			if (!i) {
				map.at(i).at(j).ever_count = true;
				max = map.at(i).at(j).size;
			}
			else {
				if (max < map.at(i).at(j).size) {
					map.at(i).at(j).ever_count = true;
					max = map.at(i).at(j).size;
				}
			}
			if (max == 9) break;
		}
	}
}
void check_bottom_to_middle(std::vector < std::vector<Tree>>& map) {
	int nb_row{ static_cast<int>(map.size()) - 1 };
	int nb_col{ static_cast<int>(map.at(0).size()) };

	for (int j{ 0 }; j < nb_col; j++) {
		int max{ -1 };
		for (int i{ nb_row }; i >= 0; i--) {
			if (i == nb_row) {
				map.at(i).at(j).ever_count = true;
				max = map.at(i).at(j).size;
			}
			else {
				if (max < map.at(i).at(j).size) {
					map.at(i).at(j).ever_count = true;
					max = map.at(i).at(j).size;
				}
			}
			if (max == 9) break;
		}
	}
}

int get_scenic(std::vector < std::vector<Tree>>& map, int x, int y) {
	int s1{ 1 }, s2{ 1 }, s3{ 1 }, s4{ 1 };

	while (map.at(x).at(y).size > map.at(x + s1).at(y).size) {
		if ((x + s1 + 1) > (static_cast<int>(map.size()) - 1)) break;
		s1++;
	}
	while (map.at(x).at(y).size > map.at(x).at(y+s2).size) {
		if ((y + s2 + 1) > (static_cast<int>(map.at(0).size()) - 1)) break;
		s2++;
	}
	while (map.at(x).at(y).size > map.at(x - s3).at(y).size) {
		if (x - (s3 + 1) < 0) break; 
		s3++;
	}
	while (map.at(x).at(y).size > map.at(x).at(y - s4).size) {
		if (y - (s4 + 1) < 0) break;
		s4++;
	}

	return s1*s2*s3*s4;
}

int main()
{
	std::ifstream f{ "input_8.txt", std::ios::in };

	if (!f.good()) {
		throw std::runtime_error("Couldn't open file\n");
	}

	std::vector < std::vector<Tree>> map{};

	int count{ 0 };
	std::string string{};
	while (getline(f, string)) {
		int n{ static_cast<int>(string.size()) };
		std::vector<Tree> temp{};
		for (int i{ 0 }; i < n; i++) {
			temp.emplace_back(static_cast<int>(string.at(i)) - 48, false);
		}
		map.push_back(temp);
		count++;
	}

	check_bottom_to_middle(map);
	check_left_to_middle(map);
	check_right_to_middle(map);
	check_top_to_middle(map);

	int sum{ 0 };
	int len{ static_cast<int>(map.at(0).size()) };
	for (int i{ 0 }; i < count; i++) {
		for (int j{ 0 }; j < len; j++) {
			if (map.at(i).at(j).ever_count) {
				sum += 1;
			}
		}
	}
	std::cout << "Level 1 : " << sum << std::endl;

	int scenic{ 0 };
	for (int i{ 1 }; i < count-1; i++) {
		for (int j{ 1 }; j < len-1; j++) {
			int candidate{ get_scenic(map, i, j) };
			scenic = (candidate > scenic ? candidate : scenic);
		}
	}
	std::cout << "Level 2 : " << scenic << std::endl;
	
	return 0;
}
