#ifndef __MAZESTRINGREADER__
#define __MAZESTRINGREADER__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::cin;
using std::ifstream;
using std::string;
using std::vector;

/*
	Maze String Reader

	Rules 
	Top and bottom characters are - if wall is present 
	Left and Right characters are | if wall is present

	If open spaces are found leading to outside the maze like at row 0 column 0
		If usingdefault is true -> in isVertex goal is set to true
		else treated as if wall closing path to outside the maze is present

+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
									|           |               |
+   +---+---+---+---+---+---+   +   +   +---+---+   +---+   +---+
|   |                           |                   |           |
+   +   +---+---+   +---+   +---+---+   +---+---+---+   +---+---+
|   |           |               |           |                   |
+   +---+---+---+   +---+---+   +---+---+---+---+---+   +---+---+
|                   |
+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+

*/

class MazeStringReader : public IMazeReader {

public:
	MazeStringReader() {};

	/*
		Parameters
		File: Name of file

		Reads file and store its in maze_txt 
		Updates y_max and x_max

		Returns false if ifstream fails
		Return true if file is read successfully
	*/
	bool getFile(string file) {
		maze_txt.clear();
		std::ifstream in(file);
		if (in.fail()) {
			std::cout << "File not found!\n";
			return false;
		}
		vector<string> maze;
		string buffer;
		while (!in.eof()) {
			getline(in, buffer, '\n');
			maze_txt.push_back(buffer);
		}
		y_max = ((maze_txt.size() - 1) / 2) - 1;
		x_max = ((maze_txt[0].size() - 1) / 4) - 1;
		return true;
	}

	/*
		Parameters
		Row
		Column

		Return true if cell is a part of start or end goal, returns false otherwise
	*/
	bool isOuter(size_t row, size_t col) {
		for (int i = 0; i < 2; ++i) {
			if (_goalPos[i][0] == row && _goalPos[i][1] == col)
				return true;
		}
		return false;
	}

	/*
		Implementation of virtual function
		
		Parameters
		y : Row
		x : Column
		top down left right : true if cell has path to the specified direction
		outer : true if cell is part of start or end goal

		Uses maze_txt to determine paths leading from cell
	*/
	void isVertex(int y, int x, bool & top, bool & down, bool & left, bool & right, bool & isGoal) {
		if (!usingDefault && isOuter(y, x))
			isGoal = true;

		if (maze_txt[(y * 2) + 0][(x * 4) + 1] == ' ') // top
			if (y != 0)
				top = true;
			else if (usingDefault) {
				isGoal = true;
			}

		if (maze_txt[(y * 2) + 1][x * 4] == ' ') // left
			if (x != 0)
				left = true;
			else if (usingDefault) {
				isGoal = true;
			}

		if (maze_txt[(y * 2) + 1][(x * 4) + 4] == ' ')
			if (x != x_max) // right
				right = true;
			else if (usingDefault) {
				isGoal = true;
			}

		if (maze_txt[(y * 2) + 2][(x * 4) + 1] == ' ') // down
			if (y != y_max)
				down = true;
			else if (usingDefault) {
				isGoal = true;
			}
	}

	/*
		Paramenters
		b

		Sets usingDefault to value of b
	*/
	void setUsingDefault(bool b) {
		usingDefault = b;
	}

	/*
		Parameter
		y row
		x column

		Add positon to _goalPosition
	*/
	bool addGoal(int y, int x) {
		static int counter = 0;
		if (0 > y || y > y_max || 0 > x || x > x_max) return false; // exceeds limits
		_goalPos[counter][0] = y;
		_goalPos[counter][1] = x;
		counter = ++counter % 2;
		return true;
	}

	/*
		Must implement

		Parameter
		y row
		x column

		Sets size of maze
	*/
	void setSize(size_t & row, size_t & col) {
		row = y_max + 1;
		col = x_max + 1;
	}

	/*
		Getter for row
	*/
	int getRow() {
		return y_max;
	}


	/*
		getter for column
	*/
	int getColumn() {
		return x_max;
	}


	/*
		getter for usingDefault
	*/
	bool isUsingDefault() {
		return usingDefault;
	}

	/*
		getter for Text
	*/
	vector<string>& getText() {
		return maze_txt;
	}

private:

	int x_max, y_max; // max size of maze

	int _goalPos[2][2]; // stores position of start and end goal

	bool usingDefault = true; // does file specify start and end goal 

	vector<string> maze_txt; // to store maze file


};

#endif // !__MAZESTRINGREADER__