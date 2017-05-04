#ifndef STATE_H
#define STATE_H

class State 
{
public:
	State(int pos, int line, State* parent) {
		this->pos = pos;
		this->line = line;
		this->parent = parent;
	}
	
	State(int pos, int line) {
		this->pos = pos;
		this->line = line;
		parent = this;
	}
	
	int getPos() {return pos;}
	int getLine() {return line;}
	State* getParent() {return parent;}
	
	bool operator == (const State &state) const 
	{
		return (this->pos == state.pos && this->line == state.line);
	}
private:
	int pos;
	int line;
	State* parent;
};
#endif //!STATE_H
