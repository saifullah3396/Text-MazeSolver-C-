#include "MazeSolver.h"

void MazeSolver::start() 
{
	cout << "Enter the input file path or write 'def' for default input> " << flush;
	while (true)
	{
		string mazeInputStr;
		getline(cin, mazeInputStr);
		if(mazeInputStr == "def")
			mazeInput.open("Input/InputMaze.txt");
		else
			mazeInput.open(mazeInputStr.c_str());
		if (mazeInput) break;
		cout << "Invalid file. Please enter a valid input file name> " << flush;
	}
	State* state = new State(0,0);
	vector<State*> path;
	findPath(state, path);
	string lineStr;
	stringstream strStream;
	int line;
	int prevLine;
	mazeOutput.open("Output/OutputMaze.txt", std::ios::out | std::ios::trunc);
	mazeOutput << largestPath.size() - 1;
	for(int i = 1; i < largestPath.size(); ++i) {
		line = largestPath[i]->getLine();
		if(line != prevLine) {
			mazeOutput << lineStr << endl;
			getFileLine(line, lineStr);
		}
		strStream << (i-1);
		string tempStr = strStream.str();
		char const *pchar = tempStr.c_str();
		lineStr.replace(largestPath[i]->getPos(), 1, pchar);
		strStream.str("");
		prevLine = line;
	}
	mazeOutput << lineStr << endl;
	line = largestPath[largestPath.size()-1]->getLine();
	while(!mazeInput.eof()) {
		getline(mazeInput, lineStr);
		mazeOutput << lineStr << endl;
	}
	mazeInput.close();
	mazeOutput.close();
}

void MazeSolver::findPath(State* state, vector<State*> path)
{
	path.push_back(state);
	vector<State*> children = getChildren(state, path);
	if (children.size() > 0) {
		for (int i = 0; i < children.size(); ++i) {
			findPath(children[i], path);
		}
	}
	else {
		if (largestPath.size() < path.size())
			largestPath = path;
	}
}

vector<State*> MazeSolver::getChildren(State* state, vector<State*> path) 
{
	int pos = state->getPos();
	int line = state->getLine();
	string lineStr;
	vector<State*> children;
	if(mazeInput.is_open())
	{
		if (line == 0) {
			line++;
			getline(mazeInput,lineStr);
			while(true) {
				pos = lineStr.find(dot, pos+1);
				if(pos > 0) {
					State* child = new State(pos, line, state);
					children.push_back(child);
				}
				else
					break;
			}
		} else {
			getFileLine(line, lineStr);
			if(!lineStr.empty()) {
				if(lineStr.at(pos + 1) == dot) {
					State* child = new State(pos + 1, line, state);
					if(!(*child == *state->getParent()))
						children.push_back(child);
				}
			}
			if(!lineStr.empty()) {
				if(lineStr.at(pos - 1) == dot) {
					State* child = new State(pos - 1, line, state);
					if(!(*child == *state->getParent()))
						children.push_back(child);
				}
			}
			line++;
			getFileLine(line, lineStr);
			if(!lineStr.empty()) {
				if(lineStr.at(pos) == dot) {
					State* child = new State(pos, line, state);
					if(!(*child == *state->getParent()))
						children.push_back(child);
				}
			}
		}
		return children;
	}
}

void MazeSolver::getFileLine(int num, string& lineStr)
{	
	string line;
	mazeInput.seekg (0, ios::beg);
	for (int i=0; i<=num - 1; i++) {
		getline(mazeInput, lineStr);
		if (mazeInput.eof())
			mazeInput.clear();
	}
}
