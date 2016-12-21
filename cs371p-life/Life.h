#include <string>   //string
#include <vector>   //vector
#include <iostream> //istream, ostream
#include <sstream>  //istringstream

using namespace std;

class AbstractCell {
protected:
	bool state;

public:

	// --------
	// AbstractCell Constructor
	// --------

	/**
	* @brief The AbstractCell constructor takes in a char which will be used to determine state of the cell
	* @param char s: char to be used to instantiate the Abstract cell and its state
	*/
	AbstractCell(char s);

	// --------
	// alive
	// --------

	/**
	* @brief This method returns whether the cell is dead or alive
	* @return bool: bool value where true is alive and false is dead
	*/
	bool alive();

	// --------
	// virtual get_state
	// --------

	/**
	* @brief This pure virtual method is implemented by the 2 concrete cell classes, Conway and Fredkin cells
	*/
	virtual char get_state() = 0;

	// --------
	// virtual evolve
	// --------

	/**
	* @brief This pure virutal method is implemented by the 2 concrete cell classes, Conway and Fredkin cells
	*/
	virtual bool evolve(AbstractCell** const neighbors) = 0;

	// --------
	// virtual destructor
	// --------

	/**
	* @brief This virutal method allows the abstract cell class to be destructed when either Conway or Fredkin cells call their own destructors
	*/
	virtual ~AbstractCell() {}

	// --------
	// change_state
	// --------

	/**
	* @brief This method changes the cell to either dead or alive depending on its first alive state. Fredkin cells will retain their age and will resume incrementing once alive again
	*/
	void change_state();

};

class ConwayCell: public AbstractCell {
public:
	// --------
	// ConwayCell Constructor
	// --------

	/**
	* @brief The ConwayCell constructor takes in a char which will be used to determine state of the cell. '*' will mean the cell is alive and '.' will mean it is dead
	* @param char s: char to be used to instantiate the Conway cell and its state
	*/
	ConwayCell(char s);

	// --------
	// get_state
	// --------

	/**
	* @brief This method returns the current state of the cell in the form of a char
	* @return char: char representation of the current state of the cell
	*/
	char get_state();

	// --------
	// evolve
	// --------

	/**
	* @brief This is the evolve method for the Fredkin cell. This follows 2 rules: a dead cell becomes a live cell, if exactly 3 neighbors are alive; and a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive
	* @param AbstractCell** neighbors: takes in a pointer to a grid of pointers to abstract cells
	* @return bool: true means the state of the cell will change and false will mean it stays the same
	*/
	bool evolve(AbstractCell** const neighbors);

};

class FredkinCell: public AbstractCell {
private:
	int age = 0;

public:
	// --------
	// FredkinCell Constructor
	// --------

	/**
	* @brief The FredkinCell constructor takes in a char which will be used to determine state of the cell. '-' will mean it is dead, while single digit numeric values and + will mean its current age and it is alive
	* @param char s: char to be used to instantiate the Fredkin cell and its state
	*/
	FredkinCell(char s);

	// --------
	// get_state
	// --------

	/**
	* @brief This method returns the current state of the cell in the form of a char
	* @return char: char representation of the current state of the cell
	*/
	char get_state();

	// --------
	// evolve
	// --------

	/**
	* @brief This is the evolve method for the Fredkin cell. This follows 2 rules: a dead cell becomes a live cell, if 1 or 3 neighbors are alive; and a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
	* @param AbstractCell** neighbors: takes in a pointer to a grid of pointers to abstract cells
	* @return bool: true means the state of the cell will change and false will mean it stays the same
	*/
	bool evolve(AbstractCell** const neighbors);
};

class Cell {
private:
	AbstractCell* _ptr;

public:
	// --------
	// Cell Constructor
	// --------

	/**
	* @brief The cell constructor takes in a char which will be used to determine which of the 2 types of cells it will be. Conway will be . and *, Fredkin will be +,-, and single digit numeric values
	* @param char s: char to be used to instantiate the cell and its state
	*/
	Cell(char s);

	// --------
	// destructor
	// --------

	/**
	* @brief This is the destructor for cell
	*/
	~Cell();

	// --------
	// copy constructor
	// --------

	/**
	* @brief This is the copy constructor for cell
	* @param Cell& rhs: cell reference to be copied
	*/
	Cell(const Cell& rhs);

	// --------
	// & operator
	// --------

	/**
	* @brief This is the reference operator for AbstractCell
	*/
	AbstractCell* operator & ();

	// --------
	// alive
	// --------

	/**
	* @brief This method returns whether the cell is dead or alive
	* @return bool: bool value where true is alive and false is dead
	*/
	bool alive();

	// --------
	// get_state
	// --------

	/**
	* @brief This method returns the current state of the cell in the form of a char
	* @return char: char representation of the current state of the cell
	*/
	char get_state();

	// --------
	// change_state
	// --------

	/**
	* @brief This method changes the cell to either dead or alive depending on its first alive state. Fredkin cells will retain their age and will resume incrementing once alive again
	*/
	void change_state();

	// --------
	// evolve
	// --------

	/**
	* @brief This method determines whether the cell will change its state or not depending on the surrounding neighbors' states.
	* @param AbstractCell** neighbors: takes in a pointer to a grid of pointers to abstract cells
	* @return bool: true means the state of the cell will change and false will mean it stays the same
	*/
	bool evolve(AbstractCell** const neighbors);

};

template <typename T>
class Life{
private:
	int popu = 0;
	int gen = 0;
	string type;
	// int row;
	// int col;
	vector<vector<T>> grid;

public:
	int row;
	int col;
	int rounds = 0;
	int intervals = 0;

	// --------
	// do_turn
	// --------

	/**
	* @brief This method will take the current generation to determine the states of every cell in the grid
	* @param int current_generation: the given current generation to be used to determine states of the cells
	*/
	void do_turn(int current_generation){
		int r = grid.size(), c = grid[0].size();
		for(; gen<current_generation; ++gen){
			vector<AbstractCell*> buffer;
			for(int i = 0; i < r; ++i){
				for(int j = 0; j < c; ++j){
					AbstractCell* neighbors[8] = {NULL};
					if(j-1>=0){
						if(i-1>=0){
							neighbors[0] = &grid[i-1][j-1];
						}
						neighbors[3] = &grid[i][j-1];
						if(i+1<r){
							neighbors[5] = &grid[i+1][j-1];
						}
					}
					if(i-1>=0)
						neighbors[1] = &grid[i-1][j];
					if(i+1<r)
						neighbors[6] = &grid[i+1][j];
					if(j+1<c){
						if(i-1>=0)
							neighbors[2] = &grid[i-1][j+1];
						neighbors[4] = &grid[i][j+1];
						if(i+1<r)
							neighbors[7] = &grid[i+1][j+1];
					}

					if(grid[i][j].evolve(neighbors))
						buffer.push_back(&grid[i][j]);
				}
			}
			for(AbstractCell* to_change : buffer){
				to_change->change_state();
				if(to_change->alive())
					++popu;
				else
					--popu;
			}
		}
	}

	// --------
	// Life constructor
	// --------

	/**
	* @brief The constructor for life takes in an input stream and parses through to create the grid of cells
	* @param istream& in: input stream containing the grid layout given to the function
	* @param int row: number of row
	* @param int col: number of columns
	*/
	Life(istream& in, int row, int col){
		for(int i = 0; i < row; ++i){
			grid.push_back(vector<T>());
			for(int j = 0; j<col; ++j){
				char tmp;
				in >> tmp;

				T cell(tmp);
				grid[i].push_back(cell);
				if(cell.alive())
					++popu;
			}
		}
	}

	// --------
	// print
	// --------

	/**
	* @brief This method prints out the current generation and popuulation followed by the grid of cells
	* @param int gen: the current generation of life
	* @param ostream& out: output stream to be used
	*/
	void print(int gen, ostream& out){
		out << "Generation = " << gen << ", Population = " << popu << "." << endl;
		for(int i = 0; i < grid.size(); i++){
			for(int j = 0; j < grid[i].size(); j++){
				out << grid[i][j].get_state();
			}
			out << endl;
		}
		out << endl;
	}
};
