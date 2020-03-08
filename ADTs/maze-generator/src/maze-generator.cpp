/**
 * File: maze-generator.cpp
 * ------------------------
 * Presents an adaptation of Kruskal's algorithm to generate mazes.
 */

#include <iostream>

#include "console.h"
#include "simpio.h"
#include "maze-graphics.h"
#include "vector.h"
#include "shuffle.h"
#include "set.h"
#include "simpio.h"

void generateMaze(int dimension);
void generateWallsAndChambers(Vector<wall> & walls, Vector<Set <cell> > & chambers, int dimension);
void removeValidWalls(MazeGeneratorView & maze, Vector<wall> & walls, Vector<Set <cell> > & chambers);

static int getMazeDimension(std::string prompt,
                            int minDimension = 7, int maxDimension = 50) {
	while (true) {
		int response = getInteger(prompt);
		if (response == 0) return response;
        if (response >= minDimension && response <= maxDimension) return response;
        std::cout << "Please enter a number between "
			 << minDimension << " and " 
		     << maxDimension << ", inclusive." << std::endl;
	}
}

int main() {
	while (true) {
		int dimension = getMazeDimension("What should the dimension of your maze be [0 to exit]? ");
		if (dimension == 0) break;
        std::cout << "This is where I'd animate the construction of a maze of dimension " << dimension << "." << std::endl;
        generateMaze(dimension);
    }

	return 0;
}

void generateMaze(int dimension)
{
    Vector<wall> walls;
    Vector< Set<cell> > chambers;
    MazeGeneratorView maze;
    maze.setDimension(dimension);
    maze.drawBorder();
    generateWallsAndChambers(walls, chambers, dimension);
    for (int i = 0; i < walls.size(); i++)
    {
        maze.drawWall(walls[i]);
    }
    removeValidWalls(maze, walls, chambers);
}

void generateWallsAndChambers(Vector<wall> & walls, Vector< Set<cell> > & chambers, int dimension)
{
    for (int row = 0; row < dimension; row++)
    {
        for (int col = 0; col < dimension; col++)
        {
            struct cell current;
            current.row = row;
            current.col = col;
            Set<cell> chamber;
            chamber.add(current);
            chambers += chamber;
            
            struct cell toRight;
            toRight.row = row;
            toRight.col = col + 1;

            struct cell below;
            below.row = row + 1;
            below.col = col;

            struct wall right;
            right.one = current;
            right.two = toRight;

            struct wall bottom;
            bottom.one = current;
            bottom.two = below;
            
            if (toRight.col < dimension)
            {
                walls += right;
            }
            if (below.row < dimension)
            {
                walls += bottom;
            }
        }
    }
}

void removeValidWalls(MazeGeneratorView & maze, Vector<wall> & walls, Vector<Set <cell> > & chambers)
{
    shuffle(walls);
    int chamberIndex1 = 0;
    int chamberIndex2 = 0;
    int wallIndex = 0;
    while (chambers.size() > 1)
    {
        for (int j = 0; j < chambers.size(); j++)
        {
            if (chambers[j].contains(walls[wallIndex].one))
            {
                chamberIndex1 = j;
            }
            if (chambers[j].contains(walls[wallIndex].two))
            {
                chamberIndex2 = j;
            }
        }
        if (chamberIndex1 != chamberIndex2)
        {
            chambers[chamberIndex1] += chambers[chamberIndex2];
            chambers.remove(chamberIndex2);
            maze.removeWall(walls[wallIndex]);
            walls.remove(wallIndex);
            shuffle(walls);
            wallIndex = 0;
            chamberIndex1 = 0;
            chamberIndex2 = 0;
        }
        else
        {
            wallIndex++;
        }
    }
}
