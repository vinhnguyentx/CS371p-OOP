// --------------------------
// projects/Voting/Voting.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef Voting_h
#define Voting_h

// --------
// includes
// --------

#include <vector>
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <algorithm>

using namespace std;

class Result
{
public:
  void set(int index, int value);
    int get(int index);
    int get_max();
    int get_min();
    int size();
    Result(vector<int>);
};

class Ballot
{
public:
  void add_ballot(vector<int> votes);
    int increment_choice_index(int index);
    vector<int> get(int index);
    void set(int index, vector<int>& new_ballot);
    int get_current_result(int index);
    int size();
    Ballot();
  // {
    // void add_ballot(vector<int> votes);
    // int increment_choice_index(int index)
    // vector<int> get(int index);
    // void set(int index, vector<int>& new_ballot);
    //
    // int size();
    //
    // int get_current_result(int index);
    //
    // int begin() ;
    //
    // int end();
  // }
};

//// -------------------
//// voting_read_ballots
//// -------------------
Ballot voting_read_ballots(istream& r, string& line, int& num_ballots);

// -------------
// voting check tie
// -------------

bool voting_check_tie(vector<int>& winners_if_tie, Result& current_results);

//// -------------------------------
//// voting_increment_losing_ballots
//// -------------------------------
void voting_increment_losing_ballots(vector<int>& losing_ballots, Ballot& ballots, Result& current_results, vector<int>& losers);

//// -----------------
//// voting_get_winner
//// -----------------
vector<int> voting_get_winner (vector<string>& candidates, Ballot& ballots, Result& current_results);

// ------------
// voting_read
// ------------

/**
* read two ints
* @param s a string
* @return a pair of ints, representing the beginning and end of a range, [i, j]
*/
pair<int, int> voting_read (const string& s);

// ------------
// voting_eval
// ------------

/**
* @param i the beginning of the range, inclusive
* @param j the end       of the range, inclusive
* @return the max cycle length of the range [i, j]
*/
int voting_eval (int i, int j);

// -------------
// voting_print
// -------------

/**
* print three ints
* @param w an ostream
* @param i the beginning of the range, inclusive
* @param j the end       of the range, inclusive
* @param v the max cycle length
*/
void voting_print (ostream& w, int i, int j, int v);

// -------------
// voting_solve
// -------------

/**
* @param r an istream
* @param w an ostream
*/
void voting_solve (istream& r, ostream& w);

#endif // voting_h
