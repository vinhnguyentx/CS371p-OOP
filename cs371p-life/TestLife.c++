#include <algorithm> // sort
#include <iostream>  // cout, endl
#include <iterator>  // equal
#include <sstream>   // istringtstream, ostringstream
#include <string>    // compare, string
#include <utility>   // pair
#include "gtest/gtest.h"

#include "Life.h"

// ----------
// TestLife
// ----------

// ----------
// Test ConwayCell
// ----------

TEST(ConwayCellFixture, Conway_constructor_1) {
	ConwayCell c('.');
	ASSERT_EQ(c.get_state(), '.');
}

TEST(ConwayCellFixture, Conway_constructor_2) {
	ConwayCell c('*');
	ASSERT_EQ(c.get_state(), '*');

}

TEST(ConwayCellFixture, Conway_constructor_3) {
	ConwayCell c('.');
	ASSERT_EQ(c.alive(), false);
}

TEST(ConwayCellFixture, Conway_constructor_4) {
	ConwayCell c('*');
	ASSERT_EQ(c.alive(), true);
}

TEST(ConwayCellFixture, Conway_change_state_1) {
	ConwayCell c('.');
	c.change_state();
	ASSERT_EQ(c.get_state(), '*');
}

TEST(ConwayCellFixture, Conway_change_state_2) {
	ConwayCell c('*');
	c.change_state();
	ASSERT_EQ(c.get_state(), '.');
}

TEST(ConwayCellFixture, Conway_change_state_3) {
	ConwayCell c('.');
	c.change_state();
	ASSERT_EQ(c.alive(), true);
}

TEST(ConwayCellFixture, Conway_change_state_4) {
	ConwayCell c('*');
	c.change_state();
	ASSERT_EQ(c.alive(), false);
}

// dead stay dead (neighbors < 3)
TEST(ConwayCellFixture, Conway_evolve_1) {
	ConwayCell c('.');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_FALSE(c.evolve(neighbors));
}

// dead stay dead (neighbors > 3)
TEST(ConwayCellFixture, Conway_evolve_2) {
	ConwayCell c('.');
	AbstractCell* neighbors[8] = {new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'), new ConwayCell('*'), new ConwayCell('*'), new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*')};
	ASSERT_FALSE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive to dead (neighbors < 3)
TEST(ConwayCellFixture, Conway_evolve_3) {
	ConwayCell c('*');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_TRUE(c.evolve(neighbors));
}

// alive to dead (neighbors > 3)
TEST(ConwayCellFixture, Conway_evolve_4) {
	ConwayCell c('*');
	AbstractCell* neighbors[8] = {new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*'), new ConwayCell('*'), new ConwayCell('*'), new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*')};
	ASSERT_TRUE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive stay alive (neighbors = 3)
TEST(ConwayCellFixture, Conway_evolve_5) {
	ConwayCell c('*');
	AbstractCell* neighbors[8] = {new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*')};
	ASSERT_FALSE(c.evolve(neighbors));

	for(AbstractCell* p : neighbors)
		delete p;
}

// alive stay alive (neighbors = 2)
TEST(ConwayCellFixture, Conway_evolve_6) {
	ConwayCell c('*');
	AbstractCell* neighbors[8] = {new ConwayCell('*'),new ConwayCell('*')};
	ASSERT_FALSE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead to alive (neighbors = 3)
TEST(ConwayCellFixture, Conway_evolve_7) {
	ConwayCell c('.');
	AbstractCell* neighbors[8] = { new ConwayCell('*'),new ConwayCell('*'),new ConwayCell('*')};
	ASSERT_TRUE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// ----------
// Test FredkinCell
// ----------

TEST(FredkinCellFixture, Fredkin_constructor_1) {
	FredkinCell f('+');
	ASSERT_EQ(f.get_state(), '+');
}

TEST(FredkinCellFixture, Fredkin_constructor_2) {
	FredkinCell f('5');
	ASSERT_EQ(f.get_state(), '5');
}

TEST(FredkinCellFixture, Fredkin_constructor_3) {
	FredkinCell f('-');
	ASSERT_EQ(f.get_state(), '-');
}

TEST(FredkinCellFixture, Fredkin_constructor_4) {
	FredkinCell f('9');
	ASSERT_EQ(f.get_state(), '9');
}

TEST(FredkinCellFixture, Fredkin_alive_1) {
	FredkinCell f('+');
	ASSERT_EQ(f.alive(), true);
}

TEST(FredkinCellFixture, Fredkin_alive_2) {
	FredkinCell f('5');
	ASSERT_EQ(f.alive(), true);
}

TEST(FredkinCellFixture, Fredkin_alive_3) {
	FredkinCell f('-');
	ASSERT_EQ(f.alive(), false);
}

// dead stay dead (neighbors = 0)
TEST(FredkinCellFixture, Fredkin_evolve_1) {
	FredkinCell f('-');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_FALSE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead stay dead (neighbors = 2)
TEST(FredkinCellFixture, Fredkin_evolve_2) {
	FredkinCell f('-');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1'),nullptr,new FredkinCell('1')};
	ASSERT_FALSE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead stay dead (neighbors = 4)
TEST(FredkinCellFixture, Fredkin_evolve_3) {
	FredkinCell f('-');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1'),nullptr,new FredkinCell('1'),new FredkinCell('1'),nullptr,new FredkinCell('1'),nullptr};
	ASSERT_FALSE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead to alive (neighbors = 1)
TEST(FredkinCellFixture, Fredkin_evolve_4) {
	FredkinCell f('-');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1')};
	ASSERT_TRUE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead to alive (neighbors = 3)
TEST(FredkinCellFixture, Fredkin_evolve_5) {
	FredkinCell f('-');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1'),nullptr,new FredkinCell('1'), new FredkinCell('1')};
	ASSERT_TRUE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive to dead (neighbors = 0)
TEST(FredkinCellFixture, Fredkin_evolve_6) {
	FredkinCell f('0');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_TRUE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive to dead (neighbors = 2)
TEST(FredkinCellFixture, Fredkin_evolve_7) {
	FredkinCell f('0');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1'),nullptr,new FredkinCell('1')};
	ASSERT_TRUE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive to dead (neighbors = 4)
TEST(FredkinCellFixture, Fredkin_evolve_8) {
	FredkinCell f('0');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1'),nullptr,new FredkinCell('1'),new FredkinCell('1'),nullptr,new FredkinCell('1'),nullptr};
	ASSERT_TRUE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive stay alive (neighbors = 1)
TEST(FredkinCellFixture, Fredkin_evolve_9) {
	FredkinCell f('0');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1')};
	ASSERT_FALSE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive stay alive (neighbors = 3)
TEST(FredkinCellFixture, Fredkin_evolve_10) {
	FredkinCell f('0');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('1'),nullptr,new FredkinCell('1'), new FredkinCell('1')};
	ASSERT_FALSE(f.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// ----------
// Test Cell
// ----------

TEST(CellFixture, Cell_constructor_1){
	Cell c('*');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c));
}

TEST(CellFixture, Cell_constructor_2){
	Cell c('1');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c));
}

TEST(CellFixture, Cell_constructor_3){
	Cell c('+');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c));
}

TEST(CellFixture, Cell_constructor_4){
	Cell c('-');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c));
}

TEST(CellFixture, Cell_constructor_5){
	Cell c('.');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c));
}

TEST(CellFixture, Cell_copy_1) {
	Cell c1('*');
	Cell c2(c1);
	ASSERT_EQ(c1.get_state(), '*');
	ASSERT_EQ(c2.get_state(), '*');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c1));
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c2));
	ASSERT_NE(&c2, &c1);
}

TEST(CellFixture, Cell_copy_2) {
	Cell c1('.');
	Cell c2(c1);
	ASSERT_EQ(c1.get_state(), '.');
	ASSERT_EQ(c2.get_state(), '.');
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c1));
	ASSERT_TRUE(dynamic_cast<ConwayCell*>(&c2));
	ASSERT_NE(&c2, &c1);
}

TEST(CellFixture, Cell_copy_3) {
	Cell c1('1');
	Cell c2(c1);
	ASSERT_EQ(c1.get_state(), '1');
	ASSERT_EQ(c2.get_state(), '1');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c1));
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c2));
	ASSERT_NE(&c2, &c1);
}

TEST(CellFixture, Cell_copy_4) {
	Cell c1('-');
	Cell c2(c1);
	ASSERT_EQ(c1.get_state(), '-');
	ASSERT_EQ(c2.get_state(), '-');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c1));
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c2));
	ASSERT_NE(&c2, &c1);
}

TEST(CellFixture, Cell_copy_5) {
	Cell c1('+');
	Cell c2(c1);
	ASSERT_EQ(c1.get_state(), '+');
	ASSERT_EQ(c2.get_state(), '+');
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c1));
	ASSERT_TRUE(dynamic_cast<FredkinCell*>(&c2));
	ASSERT_NE(&c2, &c1);
}

TEST(CellFixture, Cell_reference_operator_1) {
	Cell c('.');
	ASSERT_EQ((&c)->get_state(), '.');
	ASSERT_EQ(c.get_state(), '.');
}

TEST(CellFixture, Cell_reference_operator_2) {
	Cell c('+');
	ASSERT_EQ((&c)->get_state(), '+');
	ASSERT_EQ(c.get_state(), '+');
}

TEST(CellFixture, Cell_reference_operator_3) {
	Cell c1('*');
	Cell c2(c1);
	ASSERT_EQ((&c1)->get_state(), '*');
	ASSERT_EQ((&c2)->get_state(), '*');
	ASSERT_NE(&c2, &c1);
}

TEST(CellFixture, Cell_alive_1) {
	Cell c('*');
	ASSERT_TRUE(c.alive());
}

TEST(CellFixture, Cell_alive_2) {
	Cell c('.');
	ASSERT_FALSE(c.alive());
}

TEST(CellFixture, Cell_alive_3) {
	Cell c('+');
	ASSERT_TRUE(c.alive());
}

TEST(CellFixture, Cell_alive_4) {
	Cell c('-');
	ASSERT_FALSE(c.alive());
}

TEST(CellFixture, Cell_get_state_1) {
	Cell c('*');
	ASSERT_EQ(c.get_state(), '*');
}

TEST(CellFixture, Cell_get_state_2) {
	Cell c('.');
	ASSERT_EQ(c.get_state(), '.');
}

TEST(CellFixture, Cell_get_state_3) {
	Cell c('5');
	ASSERT_EQ(c.get_state(), '5');
}

TEST(CellFixture, Cell_get_state_4) {
	Cell c('-');
	ASSERT_EQ(c.get_state(), '-');
}

TEST(CellFixture, Cell_change_state_1) {
	Cell c('*');
	c.change_state();
	ASSERT_EQ(c.get_state(), '.');
}

TEST(CellFixture, Cell_change_state_2) {
	Cell c('.');
	c.change_state();
	ASSERT_EQ(c.get_state(), '*');
}

TEST(CellFixture, Cell_change_state_3) {
	Cell c('+');
	c.change_state();
	ASSERT_EQ(c.get_state(), '-');
}

TEST(CellFixture, Cell_change_state_4) {
	Cell c('-');
	c.change_state();
	ASSERT_EQ(c.get_state(), '0');
}


// alive conway to dead
TEST(CellFixture, Cell_evolve_1) {
	Cell c('*');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_TRUE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive conway stay alive
TEST(CellFixture, Cell_evolve_2) {
	Cell c('*');
	AbstractCell* neighbors[8] = {new ConwayCell('*'),new FredkinCell('0'),new ConwayCell('*')};
	ASSERT_FALSE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead conway to alive
TEST(CellFixture, Cell_evolve_3) {
	Cell c('.');
	AbstractCell* neighbors[8] = {new FredkinCell('0'),new ConwayCell('*'),new FredkinCell('0')};
	ASSERT_TRUE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead conway stay dead
TEST(CellFixture, Cell_evolve_4) {
	Cell c('.');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_FALSE(c.evolve(neighbors));
}

// alive Fredkin to dead
TEST(CellFixture, Cell_evolve_5) {
	Cell c('0');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_TRUE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// alive Fredkin stay alive
TEST(CellFixture, Cell_evolve_6) {
	Cell c('0');
	AbstractCell* neighbors[8] = {nullptr,new FredkinCell('0')};
	ASSERT_FALSE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead Fredkin to alive
TEST(CellFixture, Cell_evolve_7) {
	Cell c('-');
	AbstractCell* neighbors[8] = {nullptr,new ConwayCell('*')};
	ASSERT_TRUE(c.evolve(neighbors));
	for(AbstractCell* p : neighbors)
		delete p;
}

// dead Fredkin stay dead
TEST(CellFixture, Cell_evolve_8) {
	Cell c('-');
	AbstractCell* neighbors[8] = {NULL};
	ASSERT_FALSE(c.evolve(neighbors));
}

// ----------
// Test Life
// ----------

TEST(LifeFixture, Life_constructor_1) {
	stringstream in(".....\n.*...\n...*.\n..*..\n.....\n");
	Life<ConwayCell> life(in,5,5);
	stringstream out;
	life.print(0, out);
	ASSERT_EQ("Generation = 0, Population = 3.\n.....\n.*...\n...*.\n..*..\n.....\n\n", out.str());
}

TEST(LifeFixture, Life_constructor_2) {
	stringstream in("ConwayCell\n5\n5\n0\n1\n.....\n.*...\n...*.\n..*..\n.....\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<ConwayCell> life(in,row,col);
	stringstream out;
	life.print(0, out);
	ASSERT_EQ("Generation = 0, Population = 3.\n.....\n.*...\n...*.\n..*..\n.....\n\n", out.str());
}

TEST(LifeFixture, Life_constructor_3) {
	stringstream in("ConwayCell\n21\n13\n12\n1\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<ConwayCell> life(in,row,col);
	stringstream out;
	life.print(0, out);
	ASSERT_EQ("Generation = 0, Population = 13.\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n\n", out.str());
}

TEST(LifeFixture, Life_constructor_4) {
	stringstream in("FredkinCell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<ConwayCell> life(in,row,col);
	stringstream out;
	life.print(0, out);
	ASSERT_EQ("Generation = 0, Population = 4.\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n.........**.........\n.........**.........\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n\n", out.str());
}

TEST(LifeFixture, Life_constructor_5) {
	stringstream in("Cell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0000--------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<ConwayCell> life(in,row,col);
	stringstream out;
	life.print(0, out);
	ASSERT_EQ("Generation = 0, Population = 6.\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n.........**.........\n........****........\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n....................\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_1) {
	stringstream in("ConwayCell\n21\n13\n12\n1\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<ConwayCell> life(in,row,col);
	life.do_turn(1);
	stringstream out;
	life.print(1, out);
	ASSERT_EQ("Generation = 1, Population = 17.\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.....***.....\n.....****....\n........*....\n......*......\n....*........\n....****.....\n.....***.....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_2) {
	stringstream in("ConwayCell\n21\n13\n12\n1\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<ConwayCell> life(in,row,col);
	life.do_turn(2);
	stringstream out;
	life.print(2, out);
	ASSERT_EQ("Generation = 2, Population = 14.\n.............\n.............\n.............\n.............\n.............\n.............\n......*......\n.....*..*....\n.....*..*....\n.....*..*....\n.............\n....*..*.....\n....*..*.....\n....*..*.....\n......*......\n.............\n.............\n.............\n.............\n.............\n.............\n\n", out.str());

}

TEST(LifeFixture, Life_do_turn_3) {
	stringstream in("ConwayCell\n21\n13\n12\n1\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n....*****....\n.......*.....\n......*......\n.....*.......\n....*****....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<ConwayCell> life(in,row,col);
	life.do_turn(3);
	stringstream out;
	life.print(3, out);
	ASSERT_EQ("Generation = 3, Population = 18.\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n.....***.....\n....******...\n.............\n.............\n.............\n...******....\n.....***.....\n.............\n.............\n.............\n.............\n.............\n.............\n.............\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_4) {
	stringstream in("FredkinCell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<FredkinCell> life(in,row,col);
	life.do_turn(1);
	stringstream out;
	life.print(1, out);
	ASSERT_EQ("Generation = 1, Population = 8.\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_5) {
	stringstream in("FredkinCell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<FredkinCell> life(in,row,col);
	life.do_turn(2);
	stringstream out;
	life.print(2, out);
	ASSERT_EQ("Generation = 2, Population = 16.\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n---------11---------\n-------01--10-------\n-------01--10-------\n---------11---------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_6) {
	stringstream in("FredkinCell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<FredkinCell> life(in,row,col);
	life.do_turn(3);
	stringstream out;
	life.print(3, out);
	ASSERT_EQ("Generation = 3, Population = 16.\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0--0--------\n-------0----0-------\n------0------0------\n------0------0------\n-------0----0-------\n--------0--0--------\n---------00---------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_7) {
	stringstream in("Cell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0000--------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<Cell> life(in,row,col);
	life.do_turn(1);
	stringstream out;
	life.print(1, out);
	ASSERT_EQ("Generation = 1, Population = 12.\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------------------\n-------011110-------\n--------0000--------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_8) {
	stringstream in("Cell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0000--------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<Cell> life(in,row,col);
	life.do_turn(2);
	stringstream out;
	life.print(2, out);
	ASSERT_EQ("Generation = 2, Population = 24.\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0110--------\n-------00--00-------\n------01****10------\n---------11---------\n--------0000--------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n\n", out.str());
}

TEST(LifeFixture, Life_do_turn_9) {
	stringstream in("Cell\n20\n20\n5\n1\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------0000--------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n");
	string type = "";
	int row = 0;
	int col = 0;
	int rounds = 0;
	int intervals = 0;
	in >> type;
	in >> row;
	in >> col;
	in >> rounds;
	in >> intervals;
	Life<Cell> life(in,row,col);
	life.do_turn(3);
	stringstream out;
	life.print(3, out);
	ASSERT_EQ("Generation = 3, Population = 32.\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n---------00---------\n--------------------\n---------**---------\n--------1001--------\n-----01*....*10-----\n------000**000------\n-------011110-------\n--------0000--------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n--------------------\n\n", out.str());
}