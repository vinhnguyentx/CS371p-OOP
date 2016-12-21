// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair

#define CACHE_SIZE 1000000
using namespace std;

// ------------
// collatz_read
// ------------

pair<int, int> collatz_read (const string& s) {
	istringstream sin(s);
	int i;
	int j;
	sin >> i >> j;
	return make_pair(i, j);}

//-----------------------
// calculate cycle length
//-----------------------

int cycle_length (int n) {
    assert(n > 0);
    int c = 1;
    while (n > 1) {
        if ((n % 2) == 0) {
            n >>= 1;
            ++c;
          } else {
            n = n + (n >> 1) + 1;
            ++++c;
          }
      }
    assert(c > 0);
    return c;}

// ------------
// lazy_cache
// -----------

int lazy_cache(unsigned int i){
		#ifdef CACHE_SIZE
    assert (i > 0);
    static int Cache[CACHE_SIZE] = {};
    assert (i < CACHE_SIZE);
    if (Cache[i] == 0){
        Cache[i] = cycle_length(i);
    }
    return Cache[i];

		#endif

		#ifndef CACHE_SIZE

		return cycle_length(i);

		#endif
}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    assert(i > 0);
    assert(j > 0);

    if (i > j){
        int temp = j;
        j = i;
        i = temp;
    }

    int max = 1;
    while (i <= j) {
        int tempLength = lazy_cache(i);
        if (max < tempLength) {
            max = tempLength;
        }
        ++i;
    }
		// int cli = 0;
		// int clj = 0;
		// int max = 1;
    //
		// cli = lazy_cache(i);
		// clj = lazy_cache(j);
		// if (cli > clj) {
		// 		max = cli;
		// } else {
		// 		max = clj;
		// }
		assert (max > 0);
    return max;}

// -------------
// collatz_print
// -------------

void collatz_print (ostream& w, int i, int j, int v) {
	w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
	string s;
	while (getline(r, s)) {
		const pair<int, int> p = collatz_read(s);
		const int            i = p.first;
		const int            j = p.second;
		const int            v = collatz_eval(i, j);
		collatz_print(w, i, j, v);}}


    // ----
    // main
    // ----

    int main () {
        using namespace std;
        collatz_solve(cin, cout);
        return 0;}
