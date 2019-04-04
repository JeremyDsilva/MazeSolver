#ifndef __MAZEPRINT__
#define __MAZEPRINT__

#include <chrono>
#include <thread>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include "../src/Maze.h"

using std::vector;
using std::string;
using std::cin;
using std::cout;
using std::stringstream;
using std::flush;

#ifdef _WIN32
#include <windows.h>
void setCursor(int y, int x) {
	COORD destCoord;
	destCoord.Y = (y * 2) + 1;
	destCoord.X = (x * 4) + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), destCoord);
}

#else
#undef animation
#endif 

#ifdef animation 

#ifndef y_window_size
#define y_window_size 30 // for number of rows to display during animation
#endif // !y_window_size

#ifndef x_window_size
#define x_window_size 30 /// for number of columns to display during animation
#endif // !x_window_size 30

#ifndef speed
#define speed 0.0 // speed of animations
#endif // !speed

#endif



class MazePrint {

	Maze * maze; // maze
	vector<string> maze_txt; // used for animation

public:

	void setMaze(Maze &m, vector<string>& maze_text) {
		maze = &m;
		maze_txt = maze_text;
	}

	void printAt(Vertex * v, char c) {
		if (!v)	return;
		maze_txt[(v->getRow() * 2) + 1][(v->getColumn() * 4) + 2] = c;
	}

	void printMaze() {
		for (auto & x : maze_txt)
			cout << x << '\n';
		cout << '\n';
	}

	void printNodes() {
		for (auto it = maze->begin(); it != maze->end(); ++it)
			printAt(*it, '#');
	}

#ifdef animation
	void printPath(const list<Vertex*> &path) {
		for (auto & x : maze_txt)
			cout << x << '\n';
		cout << '\n';
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
		for (auto & x : path) {
			setCursor(x->getRow(), x->getColumn());
			cout << '#';
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
		setCursor((*(--maze->end()))->getRow() +1, 0);
	}
#else
	void printPath(const list<Vertex*> &path) {
		for (auto & x : path)
			printAt(x, '#');
		for (auto & x : maze_txt)
			cout << x << '\n';
		cout << '\n';
	}
#endif 

	void reset() {
		for(auto & x : *maze)
			maze_txt[(x->getRow() * 2) + 1][(x->getColumn() * 4) + 2] = ' ';
	}

	void printVisted() {
		for (auto & x : *maze)
			if (x->isVisted()) printAt(x, '*');
	}

#ifdef animation
		void animate(Vertex * start, Vertex * end, bool reset) {
			if (!start || !end)	return;

			int max_row = y_window_size > abs(start->getRow() - end->getRow()) ? y_window_size : abs(start->getRow() - end->getRow());
			int max_col = x_window_size > abs(start->getColumn() - end->getColumn()) ? x_window_size : abs(start->getColumn() - end->getColumn());

			int x_min = 0, y_min = 0, x_max = maze->getColumn(), y_max = maze->getRow();
			if (0 <= start->getRow() - max_row) {
				y_min = start->getRow() - max_row;
			}
			if (start->getRow() + max_row < maze->getRow()) {
				y_max = start->getRow() + max_row;
			}
			if (0 <= start->getColumn() - max_col) {
				x_min = start->getColumn() - max_col;
			}
			if (start->getColumn() + max_col < maze->getColumn()) {
				x_max = start->getColumn() + max_col;
			}

			printHelper(x_min, x_max, y_min, y_max);

			if (!reset) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x03);
			}
			
			Vertex::Edge & connecting_edge = start->connectingEdge(end);
			Vertex::Edge::iterator it = connecting_edge.begin();

			int row = start->getRow();
			int col = start->getColumn();
			while (it != connecting_edge.end()) {
				printAnimation(row, col, it->row, it->col, x_min, x_max, y_min, y_max, reset);
				row = it->row;
				col = it->col;
				++it;
			}
			printAnimation(row, col, end->getRow(), end->getColumn(), x_min, x_max, y_min, y_max, reset);

			if (reset) {
				printAt(start, '*');
			}
			else {
				printAt(start, '#');
				printAt(end, '#');
			}

			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0F);
			setCursor(y_max - y_min + 1, 0);

		}


	private:

		void printAnimation(int start_row, int start_col, int end_row, int end_col, int & x_min, int & x_max, int & y_min, int & y_max, bool reset) {
			using namespace std::chrono;
			using namespace std::this_thread;

			bool reprint = false;

			if (x_min > start_col) {
				x_min = start_col;
				reprint = true;
			}

			if (x_min > end_col) {
				x_min = end_col;
				reprint = true;
			}

			if (x_max < start_col) {
				x_max = start_col;
				reprint = true;
			}

			if (x_max < end_col) {
				x_max = end_col;
				reprint = true;
			}

			if (y_min > start_row) {
				y_min = start_row;
				reprint = true;
			}

			if (y_min > end_row) {
				y_min = end_col;
				reprint = true;
			}

			if (y_max < start_row) {
				y_max = start_row;
				reprint = true;
			}

			if (y_max < end_row) {
				y_max = end_row;
				reprint = true;
			}

			if (reprint) {
				printHelper(x_min, x_max, y_min, y_max);
			}

			int i, j;
			if (start_row != end_row) {
				i = start_row;
				j = end_row;
				if (i < j) {
					sleep_for(milliseconds(int(150 * speed)));
					for (; i <= j; ++i) {
						setCursor(i - y_min, start_col - x_min);
						cout << "v";
						sleep_for(milliseconds(int(150 * speed)));
						setCursor(i - y_min, start_col - x_min);
						cout << "H";
					}
				}
				else {
					for (; j <= i; --i) {
						sleep_for(milliseconds(int(150 * speed)));
						setCursor(i - y_min, start_col - x_min);
						cout << "^";
						sleep_for(milliseconds(int(150 * speed)));
						setCursor(i - y_min, start_col - x_min);
						cout << "H";
					}
				}
			}
			else {
				i = start_col;
				j = end_col;
				if (i < j) {
					for (; i <= j; ++i) {
						sleep_for(milliseconds(int(100 * speed)));
						setCursor(start_row - y_min, i - x_min);
						cout << ">";
						sleep_for(milliseconds(int(150 * speed)));
						setCursor(start_row - y_min, i - x_min);
						cout << "=";
					}
				}
				else {
					for (; j <= i; --i) {
						sleep_for(milliseconds(int(100 * speed)));
						setCursor(start_row - y_min, i - x_min);
						cout << "<";
						sleep_for(milliseconds(int(150 * speed)));
						setCursor(start_row - y_min, i - x_min);
						cout << "=";
					}
				}

			}

		}

		void printHelper(int x_min, int x_max, int y_min, int y_max)
		{
			y_min *= 2;
			x_min *= 4;
			x_max *= 4;
			y_max *= 2;

			stringstream print;
			while (y_min <= y_max) {
				for (int i = x_min; i <= x_max; ++i) {
					print << maze_txt[y_min][i];
				}
				print << '\n'; ++y_min;
			}
			system("cls");
			cout << print.str();
		}
#endif // animation

};

#endif // !__MAZEPRINT__
