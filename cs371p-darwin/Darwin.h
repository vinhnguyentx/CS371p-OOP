/** @file Darwin.h
 *  @brief A program that simulates Darwin's World.
 */

/** \mainpage Darwin
 *  Darwin's World contains a two-dimensional grid. Each square in the world can contain at most one creature.
 *  Each creature has a species, a direction, and a program counter.
 *  Each species has a program (a set of instructions).
 *  A creature executes the instruction indicated by the program counter. Each creature is given a turn.\n
 *
 *  Class: CS371p - Fall 2015
 *  Student 1: Vinh Nguyen - vtn288
 *  Student 2 : Hieu Nguyen - hn3935
 */


#ifndef Darwin_h
#define Darwin_h

// --------
// include
// --------

#include <vector>
#include <queue>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <stdexcept>
#include <cstdlib>

// location: a pair of ints, which are row and column indexs of a position
typedef std::pair<int, int> location;

class Darwin;
class Creature;

/**
 *  @class Species
 *  @brief Each species has a program (a set of instructions).
 */
class Species {

    private:
        std::string sp_name;    // the name of the species
        std::vector<std::pair<std::string, int>> program;   // Th program: a set of instructions for the species

    public:

        /**
         * CONSTRUCTOR
         * @brief Constructor for a Species
         * @param aName the name of the species
         */
        Species(std::string aName){
            sp_name = aName;
        }

        /**
         * @brief Create an instruction with 2 parameters, then add it to the program
         * @param n the name of the instruction
         * @param i the next step in the control flow instruction
         * @return 0 if successfully added
         */
        int addInstruction(std::string n, int i = 0);

        /**
         * @brief Execute the program for a specific creature
         * @param cr the pointer to the creature
         * @param c the program counter of the creature
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         * @return the updated program counter
         */
        int execute(Creature* cr, int c, const location& loc, Darwin& map);

        /**
         * @brief Overload the << operator to print out the species symbol
         * @param os the ostream object
         * @param sp the species object
         * @return the ostream object
         */
        friend std::ostream& operator<<(std::ostream& os, const Species& sp);

};

/**
 *  @class Creature
 *  @brief Each creature has a species, a direction, and a program counter.
 */
class Creature {

    private:

        Species* _p;    //  the species of the creature
        std::string _d;   // the direction of the creature
        int _c;         // the program counter of the creature

    public:

        /**
         * CONSTRUCTOR
         * @brief Create a creature with 2 parameters
         * @param sc - the pointer to the species of the creature
         * @param d - the direction of the creature
         */
        Creature(Species* sp, std::string d){
            _p = sp;
            _d = d;
            _c = 0;
        }

        /**
         * @brief Take the turn
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        void take_turn(const location& loc, Darwin& map);

        /**
         * @brief hop ahead, if possible
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        void hop(const location& loc, Darwin& map);

        /**
         * @brief turn to the left
         */
        void turnLeft();

        /**
         * @brief turn to the right
         */
        void turnRight();

        /**
         * @brief infect the creature ahead, if possible
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        void infect(const location& loc, Darwin& map);

        /**
         * @brief Check if the space ahead is empty
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        bool ifEmpty(const location& loc, Darwin& map);

         /**
         * @brief Check if the space ahead is wall
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        bool ifWall(const location& loc, Darwin& map);

         /**
         * @brief Check if the space ahead is an enemy
         * @param loc the location of the creature
         * @param map the Darwin's World of the creature
         */
        bool ifEnemy(const location& loc, Darwin& map);

         /**
         * @brief Get the location ahead of this creature
         * @param loc the location of the creature
         */
        location ahead(const location& loc);

        /**
         * @brief Overload the << operator to print out the creature symbol
         * @param os the ostream object
         * @param sp the creature object
         * @return the ostream object
         */
        friend std::ostream& operator<<(std::ostream& os, const Creature& cr);

};

/**
 *  @class Darwin
 *  @brief Darwin's World contains a two-dimensional grid. Each square in the world can contain at most one creature.
 */
class Darwin {

    private:

        std::vector<Creature*> grid;   // the grid of the Darwin's World
        int row;    // the number of rows in the grid
        int col;    // the number of column in the grid

    public:

        ////////////////////////////////////////////////////
        /**
         *  @class iterator
         *  @brief Customized iterator class for Darwin
         */
        typedef Creature* T;
        class iterator : public std::iterator<std::random_access_iterator_tag, T> {

            public:
                 using iterator_category = std::input_iterator_tag;
                 using value_type        = T;
                 using pointer           = T*;
                 using reference         = T&;

            private:
                T* _v;  //

            public:

                iterator() : _v(nullptr) {
                }

                iterator (T* rhs) : _v(rhs) {}

                iterator(const iterator& rhs) : _v(rhs._v) {}

                bool operator == (const iterator& rhs) const {
                    return (_v == rhs._v);}

                bool operator != (const iterator& rhs) const {
                    return !(*this == rhs);}

                const T& operator * () const {
                    return *_v;}

                T& operator * () {
                    return *_v;
                }

                iterator& operator ++ () {
                    ++_v;
                    return *this;}

                iterator& operator -- () {
                    --_v;
                    return *this;}

                iterator operator ++ (int) {
                    iterator x = *this;
                    ++*this;
                    return x;
                }

                iterator operator -- (int) {
                    iterator x = *this;
                    --*this;
                    return x;
                }

                iterator operator + (const int& i) {
                    iterator x = *this;
                    x._v = x._v + i;
                    return x;
                }

                iterator operator - (const int& i) {
                    iterator x = *this;
                    x._v = x._v - i;
                    return x;
                }

                int operator - (const iterator& rhs) {
                    return this->_v - rhs._v;
                }


            };


        // begin() returns the begin iterator in Darwin
        iterator begin() {
            return iterator(&grid[0]);
        }

        // end() returns the end iterator in Darwin
        iterator end() {
            return iterator(&grid[row * col]);
        }

        ////////////////////////////////////////////////////



        /**
         * CONSTRUCTOR
         * Create a grid with 2 parameters
         * @param r the number of rows in the grid
         * @param c the number of columns in the grid
         */
        Darwin(int r, int c){
            row = r;
            col = c;
            grid.resize(r * c, 0);
        }


        /**
         * @brief Change an iterator in Darwin into a location on the grid
         * @param it an iterator
         * @return a location
         */
        location itToLocation(iterator it);

        /**
         * @brief Change a location on the grid into an iterator in Darwin
         * @param loc a location
         * @return an iterator
         */
        iterator locationToIt(location loc);

        /**
         * @brief Check if a location is wall
         * @param loc a location
         * @return boolean value
         */
        bool isWall(const location& loc);

        /**
         * @brief Check if a location is empty
         * @param loc a location
         * @return boolean value
         */
        bool isEmpty(const location& loc);

        /**
         * @brief Get the pointer to a creature at a location
         * @param loc a location
         * @return a pointer to a creature
         */
        T& at(const location& loc);

        /**
         * @brief Run the Darwin's world
         * Darwin gives each Creature a turn in a left-to-right and top-down ordering.
         * During a turn a Creature can execute only one action instruction.
         */
        void run();

        /**
         * @brief Add a creature to Darwin
         * @param cr a pointer to a creation
         * @param loc the location in which the creature is added
         * @return 0 if successfully added
         */
        int addCreature(Creature* cr, const location& loc);

        /**
         * @brief Overload the << operator to print out the Darwin's World
         * @param os the ostream object
         * @param map the Darwin object
         * @return the ostream object
         */
        friend std::ostream& operator<<(std::ostream& os, Darwin& map);
};

#endif
