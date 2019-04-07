# Maze Solver

A C++ implementation of a Maze data structure using graphs with four pathfinding algorithms. The implementation of the data structure aims to be memory efficient. The code is designed to be easily adaptable to read and solve mazes of any format (for example from a file or through an image). Four pathfinding algorithms are implemented: Depth First Search, Breadth First Search, Dijkstra and A*.  

## How is the maze built?

The Maze class aims to minimize the number of Vertexes needed to store the maze. Vertexes are built only at cells where path decisions need to take place to reduces the number of iterations using any pathfinding algorithm. Between Vertexes exist Edges. Each Vertex has a maximum of four Edges. Edges store the Vertex they lead to and the distance to the Vertex. In the case where a Vertex has fewer than four Edges, Edges lead to a nullptr. Each Vertex will have at least one edge that points to another Vertex. Shown below in Blue are Vertexes built for the this maze. Additionally, to aid in displaying the path such as by coloring in pixels or printing path to file, the Edge class, shown below in Orange, stores coordinates (has integers) that exist along straight lines in a list.

 ![](https://github.com/JeremyDsilva/MazeSolver/blob/master/maze%20image.JPG)
 
## Usage 

Download the src folder and include MazeSolver.h into your project. 

<pre><code>#include "MazeSolver.h"</code></pre>

### Building the Maze based on your format

You will need to build a class that inherits the MazeBuilder class to read the maze based on the format of your maze. The MazeBuilder class has two virtual functions as follows:

<pre><code>virtual void isVertex(int row, int column, bool & top, bool & down, bool & left, bool & right, bool & isGoal) = 0;</code></pre>

The function isVertex takes in a row and column positions of a cell in your maze as arguments along with four Booleans that represent the direction of movement that can occur at the cell and the Boolean isGoal representing the start or end points. 

Using the maze above as example, at row zero column zero, (numbering starts from zero) you can move only downward and hence down would be set to true and other directions set to false, while at position row four column two, you can move upward, to the left and to the right but not downward, hence all the directions would be set to true except down. If the position at row zero column zero is your starting or ending point, isGoal additionally would be set to true as well. By default, all Boolean passed are set to false. 

<pre><code>virtual void setSize(size_t & row, size_t & col) = 0;</code></pre>

The function should set row and column size of given your maze.

In the example folder, you can find MazeStringBuilder Class that inherits the MazeBuilder Class that reads a maze with the same format as the image above from a file as a string and implements the above functionality.

To build your maze, simply pass your MazeBuilder as a parameter to Maze::setMaze as shown below. Taking MazeStringBuilder as an example

<pre><code>Maze maze;
MazeStringBuilder msb;`
maze.setMaze(msb);</code></pre>

### Path Finding

Four pathfinding algorithms are implemented. Depth First Search, Breadth First Search, Dijkstra and A*. To find a path, run any of the pathfinding algorithms as follows.

<pre><code>DepthFirstSearch dfs;
dfs.findPath(maze.maze_begin(), maze.maze_end());</code></pre>

The calculated path is stored in a list and can be accessed by calling the following function.

<pre><code>list<Vertex*> path = dfs.getPath();</code></pre>

Additionally to get the coordinate path: 

<pre><code>list<Coordinates> cord = p.getCordinatePath();</code></pre>

A* is implemented using Manhattan distance. To add your own pathfinding algorithm, inherit the Path class. 

### Example folder and Animations

The example folder has examples of how the code could be used to solve a maze read from a text file. Download the example folder along with the src folder and run driver.cpp.

Alternatively running animate.cpp will let you see the pathfinding algorithms in action (animation built for Windows) to be used for educational purposes. Pathfinding algorithms included have been modified to store the sequence of Vertexes visited. Do manipulate the define statements in animate.cpp to control for speed and window size. 

## Additional Notes

### Start and end position

If the function MazeBuilder::isVertex does not set start and end goals (by setting isGoal to true at a given position), they are set automatically based on the first and last Vertexes in stored in Maze. If the function MazeBuilder::isVertex set isGoal to true for more that two position true, then start position is the first Vertex to be set as a goal and end position is the last Vertex to be set as goal. Vertexes are built at positions where isGoal is set to true, regardless if a different end position is later added and Vertex was otherwise redundant.

### Further Improvement

When building the maze, Maze::setMaze minimize building Vertexes along straight paths and in positions where a Vertex would only connect two different Vertexes. However, the number of Vertexes could be further brought down. Such is the case where a Vertex having three Edges connects to Vertex having a single Edge. In the maze above, such a Vertex would be at position row zero column two. Vertexes are also not minimized in cases where large empty space are present.

Other improvements include adding more implementation of pathfinding algorithms. 
