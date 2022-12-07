#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


constexpr std::uint64_t MAX_SPACE { 70000000 };
constexpr std::uint64_t NEEDED_SPACE { 30000000 };

void print_tab(int i) {
	for (int j{ 0 }; j < i; j++) {
		std::cout << '\t';
	}
}

struct File {
	File(std::string file_name, std::uint64_t file_size = 0) : name{file_name}, size(file_size){}

	std::string name{};
	std::uint64_t size{};
};


struct Directory {
	Directory() = default;
	Directory(std::string dir_name) : name{ dir_name }{}
	
	void calcul_size() {
		std::uint64_t sum{ 0 };
		for (Directory& dir : directories) {
			if (dir.size == 0) dir.calcul_size();
			sum += size;
		}
		for (File file : files) sum += file.size;
		size = sum;
	}

	Directory *go_to(std::string wanted_dir) {
		Directory *new_dir{};
		if (wanted_dir == "..")	new_dir = last_directory;
		
		else {
			for (Directory& dir : directories) {
				if (dir.name == wanted_dir) {
					new_dir = &dir;
					break;
				}
			}
		}
		return new_dir;

	}
	Directory *go_home(Directory *dir) {
		while ((*dir).last_directory != nullptr) dir = (*dir).last_directory;
		
		return dir;
	}

	void get_size() {
		std::uint64_t sum{ 0 };
		for (Directory& dir : directories) {
			if (!size) dir.get_size();
			sum += dir.size;
		}
		for (File file : files) sum += file.size;

		size = sum;
	}

	std::uint64_t level_1() {
		std::uint64_t total{ 0 };
		
		if (size < 100000) total += size;
		for (Directory dir : directories) total += dir.level_1();

		return total;
	}

	std::uint64_t level_2(std::uint64_t need_to_free, std::uint64_t min) {
		for (Directory dir : directories) {
			std::uint64_t candidate{ dir.size - need_to_free };
			min = (candidate < min && candidate > 0) ? dir.size : min;
		}
		for (Directory dir : directories) {
			min = dir.level_2(need_to_free, min);
		}
		return min;
	}

	void print(int i) const {
		print_tab(i); 
		std::cout << name << " : " "size = " << size << std::endl;
		for (File file : files) {
			print_tab(i);
			std::cout << name << " : " << file.name << ' ' << file.size << std::endl;
		}
		for (Directory dir : directories) {
			print_tab(i); 
			std::cout << name << " : " << dir.name << std::endl;
			dir.print(i + 1);
		}
	}

	std::string name{};
	std::uint64_t size{ 0 };
	std::vector<Directory> directories{};
	std::vector<File> files{};
	Directory *last_directory{nullptr};

};




int main()
{
	std::ifstream f{ "input_7.txt", std::ios::in };

	if (!f.good()) {
		throw std::runtime_error("Couldn't open file\n");
	}

	//Receive a command after $ check
	std::string command{};
	//Receive the following of 'cd' command
	std::string going_where{};
	//Receive the file's size
	std::uint64_t file_size{};
	//Receive the directory's name
	std::string dir_name{};
	//Receive the file's name 
	std::string filename{};

	Directory home{"/"};
	Directory *current_dir{ &home };
	
	std::string string{};
	while (getline(f, string)) {
		//Line
		std::stringstream ss{ string };

		if (string.at(0) == '$') {
			ss >> command >> command >> going_where;
			if (command == "cd") {
				(going_where == "/") ? current_dir = (*current_dir).go_home(current_dir) : current_dir = (*current_dir).go_to(going_where);
			}
		}
		else {
			std::stringstream ss_temp{ string };

			ss >> file_size;
			if (file_size == 0) {
				ss_temp >> dir_name >> dir_name;
				(*current_dir).directories.emplace_back(dir_name);
				(*current_dir).directories.back().last_directory = current_dir;
			}
			else {
				ss >> filename;
				(*current_dir).files.emplace_back(filename, file_size);
			}
		}
	}

	home.get_size();
	home.print(0);

	std::uint64_t need_to_free{ NEEDED_SPACE - (MAX_SPACE - home.size) };
	std::uint64_t min{ home.size - need_to_free };

	std::cout << "Level 1 : " << home.level_1() << std::endl;
	std::cout << "Level 2 : " << home.level_2(need_to_free, min) << std::endl;

	return 0;
}
