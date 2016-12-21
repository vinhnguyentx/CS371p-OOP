#include <cassert>
#include "Life.h"

using namespace std;

// --------
// AbstractCell Constructor
// --------

/**
* @brief The AbstractCell constructor takes in a char which will be used to determine state of the cell
* @param char s: char to be used to instantiate the Abstract cell and its state
*/
AbstractCell::AbstractCell(char s) {
	if (s == '.' || s == '-') {
		state = false;
	} else {
		state = true;
	}
}

// --------
// alive
// --------

/**
* @brief This method returns whether the cell is dead or alive
* @return bool: bool value where true is alive and false is dead
*/
bool AbstractCell::alive() {
	return state;
}

// --------
// change_state
// --------

/**
* @brief This method changes the cell to either dead or alive depending on its first alive state. Fredkin cells will retain their age and will resume incrementing once alive again
*/
void AbstractCell::change_state() {
	state = !state;
}

// --------
// ConwayCell Constructor
// --------

/**
* @brief The ConwayCell constructor takes in a char which will be used to determine state of the cell. '*' will mean the cell is alive and '.' will mean it is dead
* @param char s: char to be used to instantiate the Conway cell and its state
*/
ConwayCell::ConwayCell(char s): AbstractCell(s) {}

// --------
// get_state
// --------

/**
* @brief This method returns the current state of the cell in the form of a char
* @return char: char representation of the current state of the cell
*/
char ConwayCell::get_state() {
	if (state) {
		return '*';
	} else {
		return '.';
	}
}

// --------
// evolve
// --------

/**
* @brief This is the evolve method for the Fredkin cell. This follows 2 rules: a dead cell becomes a live cell, if exactly 3 neighbors are alive; and a live cell becomes a dead cell, if less than 2 or more than 3 neighbors are alive
* @param AbstractCell** neighbors: takes in a pointer to a grid of pointers to abstract cells
* @return bool: true means the state of the cell will change and false will mean it stays the same
*/
bool ConwayCell::evolve(AbstractCell** const neighbors) {
	int count = 0;
	for (int i = 0; i <= 7; ++i) {
		if (neighbors[i] != NULL && neighbors[i]->alive()) {
			++ count;
		}
	}

	if (!state && (count == 3)) {
		return true;
	} else if (state && (count < 2 || count > 3)) {
		return true;
	}

	return false;
}

// --------
// FredkinCell Constructor
// --------

/**
* @brief The FredkinCell constructor takes in a char which will be used to determine state of the cell. '-' will mean it is dead, while single digit numeric values and + will mean its current age and it is alive
* @param char s: char to be used to instantiate the Fredkin cell and its state
*/
FredkinCell::FredkinCell(char s): AbstractCell(s) {
	if (s <= '9' && s >= '0') {
		age = s - '0';
	} else if (s == '+') {
		age = 10;
	}

	// if(s == '+')
	// 	age = 10;
	// else if(s <= '9' && s >= '0')
	// 	age = s - '0';
	// assert(age >= 0);
}

// --------
// get_state
// --------

/**
* @brief This method returns the current state of the cell in the form of a char
* @return char: char representation of the current state of the cell
*/
char FredkinCell::get_state() {
	if (state) {
		if (age >= 10) {
			return '+';
		} else {
			return (char) (age + '0');
		}
	} else {
		return '-';
	}
}

// --------
// evolve
// --------

/**
* @brief This is the evolve method for the Fredkin cell. This follows 2 rules: a dead cell becomes a live cell, if 1 or 3 neighbors are alive; and a live cell becomes a dead cell, if 0, 2, or 4 neighbors are alive
* @param AbstractCell** neighbors: takes in a pointer to a grid of pointers to abstract cells
* @return bool: true means the state of the cell will change and false will mean it stays the same
*/
bool FredkinCell::evolve(AbstractCell** const neighbors){
	int count = 0;
	if(neighbors[1] && neighbors[1]->alive())
		++count;
	if(neighbors[3] && neighbors[3]->alive())
		++count;
	if(neighbors[4] && neighbors[4]->alive())
		++count;
	if(neighbors[6] && neighbors[6]->alive())
		++count;

	if(state && (count == 0 || count == 2 || count == 4)){
		age = 0;
		return true;
	}
	else if(!state && (count == 1 || count == 3)){
		return true;
	}
	if(state){
		++ age;
	}
	return false;
}

// --------
// Cell Constructor
// --------

/**
* @brief The cell constructor takes in a char which will be used to determine which of the 2 types of cells it will be. Conway will be . and *, Fredkin will be +,-, and single digit numeric values
* @param char s: char to be used to instantiate the cell and its state
*/
Cell::Cell(char s) {
	if (s =='*' || s =='.') {
		_ptr = new ConwayCell(s);
	} else {
		_ptr = new FredkinCell(s);
	}
}

// --------
// destructor
// --------

/**
* @brief This is the destructor for cell
*/
Cell::~Cell() {
	delete _ptr;
}

// --------
// copy constructor
// --------

/**
* @brief This is the copy constructor for cell
* @param Cell& rhs: cell reference to be copied
*/
Cell::Cell(const Cell& rhs) {
	if (dynamic_cast<ConwayCell*> (rhs._ptr)) {
		_ptr = new ConwayCell(*(dynamic_cast<ConwayCell*> (rhs._ptr)));
	} else {
		_ptr = new FredkinCell(*(dynamic_cast<FredkinCell*> (rhs._ptr)));
	}
}

// --------
// alive
// --------

/**
* @brief This method returns whether the cell is dead or alive
* @return bool: bool value where true is alive and false is dead
*/
bool Cell::alive() {
	return _ptr->alive();
}

// --------
// get_state
// --------

/**
* @brief This method returns the current state of the cell in the form of a char
* @return char: char representation of the current state of the cell
*/
char Cell::get_state() {
	return _ptr->get_state();
}

// --------
// change_state
// --------

/**
* @brief This method changes the cell to either dead or alive depending on its first alive state. Fredkin cells will retain their age and will resume incrementing once alive again
*/
void Cell::change_state() {
	return _ptr->change_state();
}

// --------
// evolve
// --------

/**
* @brief This method determines whether the cell will change its state or not depending on the surrounding neighbors' states.
* @param AbstractCell** neighbors: takes in a pointer to a grid of pointers to abstract cells
* @return bool: true means the state of the cell will change and false will mean it stays the same
*/
bool Cell::evolve(AbstractCell** const neighbors) {
	char pre_state = _ptr->get_state();
	bool output = _ptr->evolve(neighbors);

	if (FredkinCell* cells = dynamic_cast<FredkinCell*> (_ptr)) {
		if (pre_state == '1' && (cells-> get_state() == '2')) {
			_ptr = new ConwayCell('*');
			delete cells;
		}
	}
	return output;
}

AbstractCell* Cell::operator& () {
	return _ptr;
}
