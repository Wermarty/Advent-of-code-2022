#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

#include <windows.h>

enum class Direction {
	up,
	down,
	left,
	right
};

struct Coord {
	Coord() = default;
	Coord(int i, int j) : x{ i }, y{ j }{}

	friend bool operator== (const Coord& c1, const Coord& c2);
	friend std::ostream& operator<< (std::ostream& out, const Coord& coord);

	int x{ 0 };
	int y{ 0 };
};
std::ostream& operator<< (std::ostream& out, const Coord& coord) {
	out << '(' << coord.x << ", " << coord.y << ')';
	return out;
}
bool operator== (const Coord& c1, const Coord& c2) {
	return (c1.x == c2.x && c1.y == c2.y);
}

struct Movement {
	Movement(char c, int lengh) : lengh{lengh}{
		switch (c) {
		case 'U' : direction = Direction::up;		break;
		case 'L' : direction = Direction::left;		break;
		case 'R' : direction =  Direction::right;	break;
		case 'D' : direction =  Direction::down;	break;
		default :
			std::cout << "Error parsing direction" << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	Direction direction{};
	int lengh{};
};



class Body {
public :
	Body() = default;
	Body(int i, int j) : coord{ i, j } {}

	friend std::ostream& operator<< (std::ostream& out, const Body& Body);

	Coord coord{};
};
std::ostream& operator<< (std::ostream& out, const Body& body) {
	out << body.coord;
	return out;
}


class Head : public Body {
public:
	void move(int i, int j) {
		coord.x += i;
		coord.y += j;
	}
};

class Knot : public Body {
public:
	void follow(const Coord& c) {

		int delta_row{ coord.x - c.x };
		int delta_col{ coord.y - c.y };

		//Si la queue est trop loin de la tete
		if (delta_row > 1.5 || delta_row < -1.5 || delta_col > 1.5 || delta_col < -1.5) {
			//Si la queue et la tete sont sur la meme ligne
			if (coord.x == c.x) {
				coord.y += (coord.y > c.y ? -1 : 1);
			}
			//Si la queue et la tete sont sur la meme colonne
			else if (coord.y == c.y) {
				coord.x += (coord.x > c.x ? -1 : 1);
			}
			//Sinon elles sont en diagonales
			else{
				if ((delta_row > 1.5 || delta_row < -1.5) && (delta_col < 1.5 && delta_col > -1.5)) {
					coord.x += (coord.x > c.x ? -1 : 1);
					coord.y = c.y;
				}
				else if ((delta_row < 1.5 && delta_row > -1.5) && (delta_col > 1.5 || delta_col < -1.5)) {
					coord.x = c.x;
					coord.y += (coord.y > c.y ? -1 : 1);
				}
				else {
					coord.x = (c.x + coord.x) / 2;
					coord.y = (c.y + coord.y) / 2;
				}
			}
		}
	}

};

struct Case {
	Case(int i, int j) : coord({ i, j }) {}
	Case(Coord coord) : coord{coord} {}

	friend std::ostream& operator<< (std::ostream& out, const Case& case_);

	Coord coord{};
};
std::ostream& operator<< (std::ostream& out, const Case& case_) {
	out << case_.coord;
	return out;
}

class Roop {
public:
	Roop(int roop_size) : roop_size{ roop_size }{
		for (int i{ 0 }; i < roop_size; i++) {
			knots.emplace_back();
		}
	}
	
	void move(Movement& movement, std::vector<Case>& cases) {
		int i{ 0 };
		while (i < movement.lengh) {
			switch (movement.direction) {
			case Direction::up:		head.move(-1, 0); break;
			case Direction::down:	head.move(1, 0); break;
			case Direction::left:	head.move(0, -1); break;
			case Direction::right:	head.move(0, 1); break;
			}

			knots.at(0).follow(head.coord);
			for (int j{ 1 }; j < roop_size; j++) {
				knots.at(j).follow(knots.at(j-1).coord);
			}
			
			bool is_in{ false };
			for (Case& case_ : cases) {
				if (case_.coord == knots.back().coord) is_in = true;
			}
			if (!is_in) cases.emplace_back(knots.back().coord);
			
			i++;
		}
	}

	Head head{};
	std::vector<Knot> knots{};
	int roop_size{};
};



int main()
{
	std::ifstream f{ "input_9.txt", std::ios::in };

	if (!f.good()) {
		throw std::runtime_error("Couldn't open file\n");
	}

	//Initialisation cases
	std::vector<Case> cases1{}, cases2;
	cases1.emplace_back(0, 0);
	cases2.emplace_back(0, 0);

	Roop roop1{ 1 }, roop2{ 9 };

	std::string string{};
	while (getline(f, string)) {
		
		
		
		std::stringstream ss{ string };
		char direction{};
		int lengh{};

		ss >> direction >> lengh;

		Movement mov{ direction, lengh };
		roop1.move(mov, cases1); 
		roop2.move(mov, cases2);
	}

	int level_1{ static_cast<int>(cases1.size())};
	int level_2{ static_cast<int>(cases2.size())};
	
	std::cout << "Level 1 : " << level_1 << std::endl;
	std::cout << "Level 2 : " << level_2 << std::endl;

	return 0;
}
