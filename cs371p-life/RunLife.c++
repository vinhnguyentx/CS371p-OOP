#include <iostream> //istream, ostream
#include "Life.h"

using namespace std;

int main() {

    while(!cin.eof()) {
        string type = "";
        int row = 0;
        int col = 0;
        int rounds = 0;
        int intervals = 0;

        cin >> type;
        if (type == "") {
            return 0;
        }
        cin >> row;
        cin >> col;
        cin >> rounds;
        cin >> intervals;

        if (type == "ConwayCell") {
            Life<ConwayCell> con1(cin, row, col);
            cout << "*** Life<ConwayCell> " << row << "x" << col << " ***\n" << endl;
            for (int i = 0; i <= rounds; i++) {
                con1.do_turn(i);
                if (i % intervals == 0)
                con1.print(i,cout);
            }
            cout << "...\n" << endl;
        } else if (type == "FredkinCell") {
            Life<FredkinCell> con2(cin, row, col);
            cout << "*** Life<FredkinCell> " << row << "x" << col << " ***\n" << endl;

            for (int i = 0; i <= rounds; i++) {
                con2.do_turn(i);
                if (i % intervals == 0)
                con2.print(i,cout);
            }
            cout << "...\n" << endl;
        } else {
            Life<Cell> con3(cin, row, col);
            cout << "*** Life<Cell> " << row << "x" << col << " ***\n" << endl;
            for (int i = 0; i <= rounds; i++) {
                con3.do_turn(i);
                if (i % intervals == 0)
                con3.print(i,cout);
            }
            cout << "...\n" << endl;
        }
    }
    return 0;
}