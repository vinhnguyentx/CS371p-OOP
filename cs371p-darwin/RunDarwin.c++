/** @file RunDarwin.c++
 *  @brief Run Darwin's World instances
 */

// --------
// includes
// --------

#include <cassert>   // assert
#include <cstdlib>   // rand, srand
#include <iostream>  // cout, endl
#include <stdexcept> // invalid_argument, out_of_range
#include "Darwin.h"

// ----
// main
// ----

std::pair<int, int> pickLocation(int r, int c, int num){
    num = num % (r * c);
    int row = num / c;
    int col = num % c;
    return std::make_pair(row, col);
}

std::string pickDirection(int n){
    n = n % 4;
    if (n == 0){
        return "west";
    } else if ( n == 1){
        return "north";
    } else if (n == 2){
        return "east";
    } else {
        return "south";
    }
}

int main () {
    using namespace std;

    // ----
    // food
    // ----

    /*
     0: left
     1: go 0
    */
    Species food("food");
	food.addInstruction("left");
	food.addInstruction("go", 0);

    // ------
    // hopper
    // ------

    /*
     0: hop
     1: go 0
    */
	Species hopper("hopper");
	hopper.addInstruction("hop");
	hopper.addInstruction("go", 0);

    // -----
    // rover
    // -----

    /*
     0: if_enemy 9
     1: if_empty 7
     2: if_random 5
     3: left
     4: go 0
     5: right
     6: go 0
     7: hop
     8: go 0
     9: infect
    10: go 0
    */
	Species rover("rover");
	rover.addInstruction("if_enemy", 9);
	rover.addInstruction("if_empty", 7);
	rover.addInstruction("if_random", 5);
	rover.addInstruction("left");
	rover.addInstruction("go", 0);
	rover.addInstruction("right");
	rover.addInstruction("go", 0);
	rover.addInstruction("hop");
	rover.addInstruction("go", 0);
	rover.addInstruction("infect");
	rover.addInstruction("go", 0);

    // ----
    // trap
    // ----

    /*
     0: if_enemy 3
     1: left
     2: go 0
     3: infect
     4: go 0
    */
    Species trap("trap");
	trap.addInstruction("if_enemy", 3);
	trap.addInstruction("left");
	trap.addInstruction("go", 0);
	trap.addInstruction("infect");
	trap.addInstruction("go", 0);

    //----
    // best
    // ---
    // @brief "best" species acts like a rover, excepts it takes turn determinedly, not randomly.
    /*
     // 0: if_empty 6
     // 1: if_enemy 4
     // 2: left
     // 3: go 0
     // 4: infect
     // 5: go 0
     // 6: hop
     // 7: go 0

    */
    Species best("best");

    best.addInstruction("if_empty", 6);
    best.addInstruction("if_enemy", 4);
    best.addInstruction("left");
    best.addInstruction("go", 0);
    best.addInstruction("infect");
    best.addInstruction("go", 0);
    best.addInstruction("hop");
    best.addInstruction("go", 0);    
    
    // ----------
    // darwin 8x8
    // ----------

    cout << "*** Darwin 8x8 ***" << endl;
    /*
    8x8 Darwin
    Food,   facing east,  at (0, 0)
    Hopper, facing north, at (3, 3)
    Hopper, facing east,  at (3, 4)
    Hopper, facing south, at (4, 4)
    Hopper, facing west,  at (4, 3)
    Food,   facing north, at (7, 7)
    Simulate 5 moves.
    Print every grid.
    */
    try {
		srand(0);
        Darwin map(8, 8);
        
        Creature f1(&food, "east");
        map.addCreature(&f1, {0,0});

        Creature h1(&hopper, "north");
        map.addCreature(&h1, {3,3});

        Creature h2(&hopper, "east");
        map.addCreature(&h2, {3,4});

        Creature h3(&hopper, "south");
        map.addCreature(&h3, {4,4});

        Creature h4(&hopper, "west");
        map.addCreature(&h4, {4,3});

        Creature f2(&food, "north");
        map.addCreature(&f2, {7,7});

		cout << "Turn = 0." << endl;
        cout << map << endl;
        for (int i = 1; i <= 5; i++){
            map.run();
            cout << "Turn = " << i << "." << endl;
            cout << map << endl;
        } 
	} 
	catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);}

    // ----------
    // darwin 7x9
    // ----------

    cout << "*** Darwin 7x9 ***" << endl;
    /*
    7x9 Darwin
    Trap,   facing south, at (0, 0)
    Hopper, facing east,  at (3, 2)
    Rover,  facing north, at (5, 4)
    Trap,   facing west,  at (6, 8)
    Simulate 5 moves.
    Print every grid.
    */
    try {
		srand(0);
        Darwin map(7, 9);

        Creature t1(&trap, "south");
        map.addCreature(&t1, {0,0});

        Creature h1(&hopper, "east");
        map.addCreature(&h1, {3,2});

        Creature r1(&rover, "north");
        map.addCreature(&r1, {5,4});

        Creature t2(&trap, "west");
        map.addCreature(&t2, {6,8});

		cout << "Turn = 0." << endl;
        cout << map << endl;
        for (int i = 1; i <= 5; i++){
            map.run();
            cout << "Turn = " << i << "." << endl;
            cout << map << endl;
        }   
	} 
	catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }


    // ------------
    // darwin 72x72
    // without best
    // ------------

    cout << "*** Darwin 72x72 without Best ***" << endl;
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: west, north, east, south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    Simulate 1000 moves.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */
    try {
        srand(0);
        Darwin map(72, 72);
        string d;
        pair<int, int> loc;

        // food1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f1(&food, d);
        map.addCreature(&f1, loc);
        // food2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f2(&food, d);
        map.addCreature(&f2, loc);
        // food3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f3(&food, d);
        map.addCreature(&f3, loc);
        // food4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f4(&food, d);
        map.addCreature(&f4, loc);
        // food5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f5(&food, d);
        map.addCreature(&f5, loc);
        // food6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f6(&food, d);
        map.addCreature(&f6, loc);
        // food7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f7(&food, d);
        map.addCreature(&f7, loc);
        // food8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f8(&food, d);
        map.addCreature(&f8, loc);
        // food9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f9(&food, d);
        map.addCreature(&f9, loc);
        // food10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f10(&food, d);
        map.addCreature(&f10, loc);

        // hopper1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h1(&hopper, d);
        map.addCreature(&h1, loc);
        // hopper2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h2(&hopper, d);
        map.addCreature(&h2, loc);
        // hopper3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h3(&hopper, d);
        map.addCreature(&h3, loc);
        // hopper4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h4(&hopper, d);
        map.addCreature(&h4, loc);
        // hopper5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h5(&hopper, d);
        map.addCreature(&h5, loc);
        // hopper6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h6(&hopper, d);
        map.addCreature(&h6, loc);
        // hopper7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h7(&hopper, d);
        map.addCreature(&h7, loc);
        // hopper8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h8(&hopper, d);
        map.addCreature(&h8, loc);
        // hopper9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h9(&hopper, d);
        map.addCreature(&h9, loc);
        // hopper10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h10(&hopper, d);
        map.addCreature(&h10, loc);

        // rover1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r1(&rover, d);
        map.addCreature(&r1, loc);
        // rover2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r2(&rover, d);
        map.addCreature(&r2, loc);
        // rover3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r3(&rover, d);
        map.addCreature(&r3, loc);
        // rover4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r4(&rover, d);
        map.addCreature(&r4, loc);
        // rover5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r5(&rover, d);
        map.addCreature(&r5, loc);
        // rover6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r6(&rover, d);
        map.addCreature(&r6, loc);
        // rover7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r7(&rover, d);
        map.addCreature(&r7, loc);
        // rover8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r8(&rover, d);
        map.addCreature(&r8, loc);
        // rover9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r9(&rover, d);
        map.addCreature(&r9, loc);
        // rover10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r10(&rover, d);
        map.addCreature(&r10, loc);

        // trap1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t1(&trap, d);
        map.addCreature(&t1, loc);
        // trap2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t2(&trap, d);
        map.addCreature(&t2, loc);
        // trap3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t3(&trap, d);
        map.addCreature(&t3, loc);
        // trap4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t4(&trap, d);
        map.addCreature(&t4, loc);
        // trap5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t5(&trap, d);
        map.addCreature(&t5, loc);
        // trap6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t6(&trap, d);
        map.addCreature(&t6, loc);
        // trap7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t7(&trap, d);
        map.addCreature(&t7, loc);
        // trap8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t8(&trap, d);
        map.addCreature(&t8, loc);
        // trap9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t9(&trap, d);
        map.addCreature(&t9, loc);
        // trap10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t10(&trap, d);
        map.addCreature(&t10, loc);

        cout << "Turn = 0." << endl;
        cout << map << endl;
        for (int i = 1; i <= 1000; i++){
            map.run();
            if (i < 10 || (i % 100 == 0)){
                cout << "Turn = " << i << "." << endl;
                cout << map << endl;
            }
        }   
    } 
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }

    // ------------
    // darwin 72x72
    // with best
    // ------------

    cout << "*** Darwin 72x72 with Best ***" << endl;
    /*
    Randomly place the following creatures facing randomly.
    Call rand(), mod it with 5184 (72x72), and use that for the position
    in a row-major order grid.
    Call rand() again, mod it with 4 and use that for it's direction with
    the ordering: 0:west, 1:north, 2:east, 3:south.
    Do that for each kind of creature.
    10 Food
    10 Hopper
    10 Rover
    10 Trap
    10 Best
    Simulate 1000 moves.
    Best MUST outnumber ALL other species for the bonus pts.
    Print the first 10 grids          (i.e. 0, 1, 2...9).
    Print every 100th grid after that (i.e. 100, 200, 300...1000).
    */
    try {
        srand(0);
        Darwin map(72, 72);
        string d;
        pair<int, int> loc;

        // food1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f1(&food, d);
        map.addCreature(&f1, loc);
        // food2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f2(&food, d);
        map.addCreature(&f2, loc);
        // food3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f3(&food, d);
        map.addCreature(&f3, loc);
        // food4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f4(&food, d);
        map.addCreature(&f4, loc);
        // food5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f5(&food, d);
        map.addCreature(&f5, loc);
        // food6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f6(&food, d);
        map.addCreature(&f6, loc);
        // food7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f7(&food, d);
        map.addCreature(&f7, loc);
        // food8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f8(&food, d);
        map.addCreature(&f8, loc);
        // food9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f9(&food, d);
        map.addCreature(&f9, loc);
        // food10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature f10(&food, d);
        map.addCreature(&f10, loc);

        // hopper1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h1(&hopper, d);
        map.addCreature(&h1, loc);
        // hopper2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h2(&hopper, d);
        map.addCreature(&h2, loc);
        // hopper3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h3(&hopper, d);
        map.addCreature(&h3, loc);
        // hopper4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h4(&hopper, d);
        map.addCreature(&h4, loc);
        // hopper5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h5(&hopper, d);
        map.addCreature(&h5, loc);
        // hopper6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h6(&hopper, d);
        map.addCreature(&h6, loc);
        // hopper7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h7(&hopper, d);
        map.addCreature(&h7, loc);
        // hopper8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h8(&hopper, d);
        map.addCreature(&h8, loc);
        // hopper9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h9(&hopper, d);
        map.addCreature(&h9, loc);
        // hopper10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature h10(&hopper, d);
        map.addCreature(&h10, loc);

        // rover1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r1(&rover, d);
        map.addCreature(&r1, loc);
        // rover2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r2(&rover, d);
        map.addCreature(&r2, loc);
        // rover3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r3(&rover, d);
        map.addCreature(&r3, loc);
        // rover4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r4(&rover, d);
        map.addCreature(&r4, loc);
        // rover5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r5(&rover, d);
        map.addCreature(&r5, loc);
        // rover6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r6(&rover, d);
        map.addCreature(&r6, loc);
        // rover7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r7(&rover, d);
        map.addCreature(&r7, loc);
        // rover8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r8(&rover, d);
        map.addCreature(&r8, loc);
        // rover9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r9(&rover, d);
        map.addCreature(&r9, loc);
        // rover10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature r10(&rover, d);
        map.addCreature(&r10, loc);

        // trap1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t1(&trap, d);
        map.addCreature(&t1, loc);
        // trap2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t2(&trap, d);
        map.addCreature(&t2, loc);
        // trap3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t3(&trap, d);
        map.addCreature(&t3, loc);
        // trap4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t4(&trap, d);
        map.addCreature(&t4, loc);
        // trap5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t5(&trap, d);
        map.addCreature(&t5, loc);
        // trap6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t6(&trap, d);
        map.addCreature(&t6, loc);
        // trap7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t7(&trap, d);
        map.addCreature(&t7, loc);
        // trap8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t8(&trap, d);
        map.addCreature(&t8, loc);
        // trap9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t9(&trap, d);
        map.addCreature(&t9, loc);
        // trap10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature t10(&trap, d);
        map.addCreature(&t10, loc);

        // best1
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b1(&best, d);
        map.addCreature(&b1, loc);
        // best2
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b2(&best, d);
        map.addCreature(&b2, loc);
        // best3
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b3(&best, d);
        map.addCreature(&b3, loc);
        // best4
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b4(&best, d);
        map.addCreature(&b4, loc);
        // best5
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b5(&best, d);
        map.addCreature(&b5, loc);
        // best6
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b6(&best, d);
        map.addCreature(&b6, loc);
        // best7
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b7(&best, d);
        map.addCreature(&b7, loc);
        // best8
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b8(&best, d);
        map.addCreature(&b8, loc);
        // best9
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b9(&best, d);
        map.addCreature(&b9, loc);
        // best10
        loc = pickLocation(72, 72, rand());
        d = pickDirection(rand());
        Creature b10(&best, d);
        map.addCreature(&b10, loc);

        cout << "Turn = 0." << endl;
        cout << map << endl;
        for (int i = 1; i <= 1000; i++){
            map.run();
            if (i < 10 || (i % 100 == 0)){
                cout << "Turn = " << i << "." << endl;
                cout << map << endl;
            }
        }   
    } 
    catch (const invalid_argument&) {
        assert(false);
    }
    catch (const out_of_range&) {
        assert(false);
    }

    return 0;
}