/** @file Darwin.c++                                                          
 *  @brief Implementation of a program that simulates Darwin's World.
 */

// --------
// include
// --------

#include "Darwin.h"

/**
 *  @class Species
 *  @brief Each species has a program (a set of instructions).
 */

        /**
         * @brief Create an instruction with 2 parameters, then add it to the program
         * @param n the name of the instruction
         * @param i the next step in the control flow instruction
         * @return 0 if successfully added
         */
        int Species::addInstruction(std::string n, int i){

        	//try to add an instruction to the program, return -1 if that fails
        	// an instruction is a pair of instruction name and a program counter after it
            std::string names[9] = {"hop", "left", "right", "infect", "if_empty", "if_wall", "if_random", "if_enemy", "go"};
            bool checkName = false;
            for (int i = 0; i < 9; i++){
                if (names[i] == n){
                    checkName = true;
                }
            }
            if (!checkName){
                return -1;
            }

            std::pair<std::string, int> instruction(n, i);
            program.push_back(instruction);

            return 0;
        }

        /**
         * @brief Execute the program for a specific creature
         * @param cr the pointer to the creature
         * @param c the program counter of the creature
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         * @return the updated program counter
         */
        int Species::execute(Creature* cr, int c, const location& loc, Darwin& map){
            
	        std::pair<std::string, int> instruction;
	        std::string act;
	        int step;
	        while (1) {

	        	// get the instruction with a program counter
	            instruction = program[c];
	            // get the name of the instruction
	            act = instruction.first;
	            // get the program counter going with the instruction
	            step = instruction.second;

	            // depends on the instruction name, take actions accordingly
	            if(act == "hop") {

	                cr->hop(loc, map);
	                return ++c;

	            } else if(act == "left") {

	                cr->turnLeft();
	                return ++c;

	            } else if(act == "right") {

	                cr->turnRight();
	                return ++c;
	                
	            } else if(act == "infect") {

	                cr->infect(loc, map);
	                return ++c;
	                
	            } else if(act == "if_empty") {
	                if (cr->ifEmpty(loc, map)){
	                    c = step;
	                } else {
	                    ++c;
	                }
	                
	            } else if(act == "if_wall") {

	                if (cr->ifWall(loc, map)){
	                    c = step;
	                } else {
	                    ++c;
	                }
	                
	            } else if(act == "if_random") {
	                if(rand() % 2){
	                    c = step;
	                } else {
	                    ++c;
	                }
	                
	            } else if(act == "if_enemy") {
	                
	                if (cr->ifEnemy(loc, map)){
	                    c = step;
	                } else {
	                    ++c;
	                }
	                
	            } else if(act == "go") {
	                c = step;
	            }
	        }
	            
            return c;
		}

        /**
         * @brief Overload the << operator to print out the species symbol
         * @param os the ostream object
         * @param sp the species object
         * @return the ostream object
         */
        std::ostream& operator<<(std::ostream& os, const Species& sp){
        	
        	//only print out the first character of the species name
        	os << sp.sp_name.at(0);
        	return os;
        }

/**
 *  @class Creature
 *  @brief Each creature has a species, a direction, and a program counter.
 */

        /**
         * @brief Take the turn
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        void Creature::take_turn(const location& loc, Darwin& map){
            
            // call the species to execute a turn with the given information
            _c = _p->execute(this, _c, loc, map);
        }

        /**
         * @brief hop ahead, if possible
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        void Creature::hop(const location& loc, Darwin& map){
            
            // get the location ahead
            location ahead = this->ahead(loc);

            // hop ahead if it's empty
            if(map.isEmpty(ahead)){
                map.at(ahead) = map.at(loc);
                map.at(loc) = 0;
            }
		}

        /**
         * @brief turn to the left
         */
        void Creature::turnLeft(){

        	// turn left change the direction of the creature
            if (_d == "north") {
                _d = "west";
            } else if (_d == "south") {
                _d = "east";
            } else if (_d == "east") {
                _d = "north";
            } else if (_d == "west") {
                _d = "south";
            }
        }

        /**
         * @brief turn to the right
         */
        void Creature::turnRight(){

        	// turn right change the direction of the creature
            if (_d == "north") {
                _d = "east";
            } else if (_d == "south") {
                _d = "west";
            } else if (_d == "east") {
                _d = "south";
            } else if (_d == "west") {
                _d = "north";
            }
        }

        /**
         * @brief infect the creature ahead, if possible
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        void Creature::infect(const location& loc, Darwin& map){
            
            // get the location ahead
            location ahead = this->ahead(loc);

            // if the creature ahead is enemy then infect it
            if(!map.isWall(ahead) && !map.isEmpty(ahead)){
                if (map.at(ahead)->_p != map.at(loc)->_p){
                    map.at(ahead)->_p = map.at(loc)->_p;
                    map.at(ahead)->_c = 0;
                }
            }
		}

        /**
         * @brief Check if the space ahead is empty
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        bool Creature::ifEmpty(const location& loc, Darwin& map){
            
            // get the location ahead and check if it's emmpty
            location ahead = this->ahead(loc);
            return map.isEmpty(ahead);
		}

         /**
         * @brief Check if the space ahead is wall
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        bool Creature::ifWall(const location& loc, Darwin& map){
            
            // get the location ahead and check if it's wall
            location ahead = this->ahead(loc);
            return map.isWall(ahead);
		}

         /**
         * @brief Check if the space ahead is an enemy
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        bool Creature::ifEnemy(const location& loc, Darwin& map){
            
            // get the location ahead and check if it's an enemy
            location ahead = this->ahead(loc);
            
            if(!map.isWall(ahead) && !map.isEmpty(ahead)){
                if (map.at(ahead)->_p != map.at(loc)->_p){
                    return true;
                }
            }

            return false;
		}

         /**
         * @brief Get the location ahead of this creature
         * @param loc the location of the creature
         */
        location Creature::ahead(const location& loc){

        	//depends on the direction of the creature, calculate the location ahead of it
            int r = loc.first;
            int c = loc.second;
            location ahead = std::make_pair(-1, -1);
            if (_d == "north") {
                ahead = std::make_pair(r - 1, c);
            } else if (_d == "south") {
                ahead = std::make_pair(r + 1, c);
            } else if (_d == "east") {
                ahead = std::make_pair(r, c + 1);
            } else if (_d == "west") {
                ahead = std::make_pair(r, c - 1);
            }
            return ahead;
        }

        /**
         * @brief Overload the << operator to print out the creature symbol
         * @param os the ostream object
         * @param sp the creature object
         * @return the ostream object
         */
        std::ostream& operator<<(std::ostream& os, const Creature& cr){
        	
        	//print the species of the creature
        	os << *(cr._p);
        	return os;
        }

/**
 *  @class Darwin
 *  @brief Darwin's World contains a two-dimensional grid. Each square in the world can contain at most one creature.
 */
 		typedef Creature* T;
 		typedef Darwin::iterator iterator;
        
        /**
         * @brief Change an iterator in Darwin into a location on the grid
         * @param it an iterator
         * @return a location
         */
        location Darwin::itToLocation(iterator it){
            
            // get the difference between begin iterator and the given iterator 
            int d = it - this->begin();
            
            // calculate the location based on the offset of the given iterator
            int c = d % (col);
            int r = d / (col);

            return location(r, c);
        }

        /**
         * @brief Change a location on the grid into an iterator in Darwin 
         * @param loc a location
         * @return an iterator
         */
        iterator Darwin::locationToIt(location loc) {

        	// calculate the offset of the iterator to be returned based on the location
            iterator it = this->begin() + (loc.first * col + loc.second);

            return it;
        }

        /**
         * @brief Check if a location is wall
         * @param loc a location
         * @return boolean value
         */
        bool Darwin::isWall(const location& loc) {

            int r = loc.first;
            int c = loc.second;

            // check if row is between 0 and Max(row)
            bool withinR = (r >= 0 && r < row);
            // check if col is between 0 and Max(col)
            bool withinC = (c >= 0 && c < col);

            // return whether or not loc is inbound
            return !(withinR && withinC);
        }

        /**
         * @brief Check if a location is empty
         * @param loc a location
         * @return boolean value
         */
        bool Darwin::isEmpty(const location& loc){

        	// check if the location is wall
            bool wall = this->isWall(loc);
            if (wall){
                return false;
            }

            // check if the location is empty (pointing to nothing)
            return !(this->at(loc)); 
        }

        /**
         * @brief Get the pointer to a creature at a location
         * @param loc a location
         * @return a pointer to a creature
         */
        T& Darwin::at(const location& loc){
            
            // check for in-bound condition
            if(this->isWall(loc)){
                throw std::out_of_range("out of range");
            }

            // return a reference to the pointer of a creature
            return *(this->locationToIt(loc));
        }
        
        /**
         * @brief Run the Darwin's world
         * Darwin gives each Creature a turn in a left-to-right and top-down ordering. 
         * During a turn a Creature can execute only one action instruction.
         */
        void Darwin::run(){

            iterator it = this->begin();
            iterator e = this->end();

            // make a pair of a creature and its position
            std::pair<Creature*, location> runCreator;

            // this is a queue of pairs of a creature and its location
            std::queue<std::pair<Creature*, location>> runQueue;
            
        	// iterate through Darwin and get all existing creatures into a queue
            while (it != e){

            	//
                if(*it != 0){
                    location loc = this->itToLocation(it);
                    runCreator = std::make_pair(*it, loc);
                    runQueue.push(runCreator);
                }
                it++;
            }

            // pop one pair of a creature and its location out at a time,
            // each of them is given a turn in Darwin
            while(!runQueue.empty()){

                runCreator = runQueue.front();
                runQueue.pop();
                runCreator.first->take_turn(runCreator.second, *this);
            }
        }

        /**
         * @brief Add a creature to Darwin
         * @param cr a pointer to a creation
         * @param loc the location in which the creature is added
         * @return 0 if successfully added
         */
        int Darwin::addCreature(Creature* cr, const location& loc){
            
            // add a creature to Darwin, return -1 if that fails
            if (this->isEmpty(loc)){
                this->at(loc) = cr;
                return 0;
            }

            return -1;
        }

        /**
         * @brief Overload the << operator to print out the Darwin's World
         * @param os the ostream object
         * @param map the Darwin object
         * @return the ostream object
         */
       	std::ostream& operator<<(std::ostream& os, Darwin& map)
        {
        	// print a grid of Darwin and its creatures
            std::ostringstream output;
            output << "  ";

            // print the column numbers
            for (int i = 0; i < map.col; i++){
                output << i % 10;
            }
            
            output << std::endl;

            // print each row with row number and creatures in it
            for (int i = 0; i < map.row; i++){
                output << i % 10 << " ";
                for (int j = 0; j < map.col; j++){
                    location loc = std::make_pair(i, j);
                    if (map.at(loc) == 0){
                        output << ".";
                    }
                    else {
                        output << *(map.at(loc));
                    }
                }
                output << std::endl;

            }

          os << output.str();
          return os;
        }
///////////////////