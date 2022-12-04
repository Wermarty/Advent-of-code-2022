#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream f{};
	f.open("input_1.txt", std::ios::in);

	if (!f.is_open()) {
		exit(EXIT_SUCCESS);
	}

	std::string string{};

	int max{ 0 }, max_1{ 0 }, max_2{ 0 }, max_3{ 0 };
	int sum{ 0 };
	while (!f.eof()) {
		getline(f, string);
		if (!string.empty()) {
			sum += stoi(string);
		}
		else {
			(max < sum ? max = sum : max = max);
			if (sum > max_1) {
				max_1 = sum;
			}
			else if(sum>max_2) {
				max_2 = sum;
			}
			else if (sum > max_3) {
				max_3 = sum;
			}
			sum = 0;
		}
	}

	f.close();

	int global_sum{ max_1 + max_2 + max_3 };

	std::cout << "niveau 1 : " << max << std::endl;
	std::cout << "niveau 2 : " << global_sum << std::endl;
}

