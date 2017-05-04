#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string.h>
#include <vector>

#include "State.h"

using namespace std;

const char dot = '.';

class MazeSolver 
{
public:
	MazeSolver() {}
	~MazeSolver() {}
	void start();
private:
	void findPath(State* state, vector<State*> path);
	vector<State*> getChildren(State* state, vector<State*> path);
	vector<State*> largestPath;
	void getFileLine(int num, string& lineStr);
	fstream mazeInput;
	fstream mazeOutput;
};
#endif //!MAZE_SOLVER_H
