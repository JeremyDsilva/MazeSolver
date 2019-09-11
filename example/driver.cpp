#include "../src/MazeSolver.h"
#include "MazeStringReader.h"
#include "MazePrint.h"

void setOuter(MazeStringReader & msb) {
	char buffer = '\0';
	cout << "Do you want to use the default start and end positions[y/n]: ";
	cin >> buffer;
	while (cin.get() != '\n');  // clean line*/
	if (buffer == 'y' || buffer == 'Y') {
		cout << "Using default start and end positions\n";
		msb.setUsingDefault(true);
		return;
	}
	cout << "Maze size [y x]: [" << msb.getRow() << ' ' << msb.getColumn() << "]\n";
	msb.setUsingDefault(false);

	buffer = '\0';

	int y, x;

	// Set Start
	do {
		if (buffer != '\0') cout << "Start position exceeded maze bounds!\n";
		cout << "Enter Position of start [y x]: ";
		cin >> buffer >> y >> x >> buffer;
		while (cin.get() != '\n');  // clean line*/
	} while (!msb.addGoal(y,x));


	buffer = '\0';
	// Set Goal
	do {
		if (buffer != '\0') cout << "End position exceeded maze bounds!\n";
		cout << "Enter Position of goal [y x]: ";
		cin >> buffer >> y >> x >> buffer;
		while (cin.get() != '\n');  // clean line*/
	} while (!msb.addGoal(y, x));
}

template<typename path>
void findPath(Maze & maze, Vertex * start, Vertex * end, MazePrint & mp) {
	maze.reset();
	path p;
	p.findPath(start, end);
	if (p.getPath().empty()) {
		cout << "Path does not exist!\n";
	}
	else {
		mp.printPath(p.getPath());
	}

	char option;
	cout << "Number of iterations: " << p.getCount() << '\n';

	cout << "Cordinates of path: ";
	list<Coordinates> cord = p.getCordinatePath();
	for (auto & x : cord) {
		cout << '(' << x.row << ' ' << x.col << ") ";
	}

}

int main()
{
	bool rerun = true;

	Maze maze;
	MazeStringReader msb;
	MazePrint mp;
	string in;

	while (rerun) {
		cout << "\n1.Load Maze" <<
			"\n2.Find Path" <<
			"\n3.Exit\n";

		char option = '\0';
		do {	 // read option
			if (option != '\0') cout << "Invalid option!\n";
			cout << "Enter option: ";
			cin >> option;
			while (cin.get() != '\n');  // clean line*/
		} while (!('0' < option && option <= '3'));

		switch (option) {

		case '1': // Load Maze
			cout << "Enter file name: ";  cin >> in;
			while (cin.get() != '\n');  // clean line
			if(!msb.getFile(in)) break;

			setOuter(msb);			
			maze.setMaze(msb);

			cout << "Built Maze.\nMaze Size: " << maze.getRow() * maze.getColumn() << "\nBuilt using " << maze.listSize() << '\n';
			mp.setMaze(maze, msb.getText());
			mp.printNodes();
			mp.printAt(maze.maze_begin(), 'S');
			mp.printAt(maze.maze_end(), 'E');
			mp.printMaze();

			break;
		case '2': // Find Path
			if (maze.empty()) {
				cout << "Maze not set!\n";
				break;
			}
			cout << "\n1)dfs\n2)bfs\n3)dijkstra\n4)A *\n";
			do {
				// read option
				option = '\0';
				if (option != '\0') cout << "Invalid option!\n";
				cout << "Enter option: ";
				cin >> option;
				while (cin.get() != '\n');  // clean line*/
			} while (!('0' < option && option <= '4'));

			maze.reset();
			mp.setMaze(maze, msb.getText());
			switch (option) {
			case '1':
				findPath<DepthFirstSearch>(maze, maze.maze_begin(), maze.maze_end(), mp);
				break;
			case '2':
				findPath<BreadthFirstSearch>(maze, maze.maze_begin(), maze.maze_end(), mp);
				break;
			case '3':
				findPath<Dijkstra>(maze, maze.maze_begin(), maze.maze_end(), mp);
				break;
			case '4':
				findPath<Astar>(maze, maze.maze_begin(), maze.maze_end(), mp);
				break;
			}
			cout << '\n';
			break;

		case '3': // exit
			cout << "\nGoodBye!\n";
			rerun = false;
			break;
		}

	}

}