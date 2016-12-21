#include <iostream> // cin, cout
#include <vector>
#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <algorithm>

//#include "Voting.h"

using namespace std;

// -------
// Classes
// -------

class Result
{
public:
    void set(int index, int value);
    int get(int index);
    int get_max();
    int get_min();
    int size();
    Result(vector<int>);
private:
    vector<int> results;
};

Result::Result(vector<int> current_results) {
    results = current_results;
}

void Result::set(int index, int value) {
    results[index] = value;
}

int Result::get(int index) {
    return results[index];
}

int Result::get_max() {
    int max = 0;
    for (int i : results) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}

int Result::get_min() {
    int min = results[0];
    for (int i : results) {
        if ((min == 0) || (i != 0 && i < min)) {
            min = i;
        }
    }
    return min;
}

int Result::size() {
    return results.size();
}

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
private:
    vector<vector<int>> ballots;
    vector<int> current_choice_index;
    vector<int> current_results;
};

Ballot::Ballot()
{
}

void Ballot::add_ballot(vector<int> votes) {
    ballots.push_back(votes);
    current_choice_index.push_back(0);
}

int Ballot::increment_choice_index(int index) {

    vector<int> ballot = ballots[index];
    int ballot_size = ballot.size();
    if (ballot_size == 0) { return - 1;}

    if (current_choice_index[index] >= ballot_size) {
        return ballot_size - 1;
    }
    int res = ++ current_choice_index[index];
    return res;
}

vector<int> Ballot::get(int index) {
    return ballots[index];
}

void Ballot::set(int index, vector<int>& new_ballot) {
    ballots[index] = new_ballot;
}

int Ballot::size() {
    return ballots.size();
}

int Ballot::get_current_result(int index) {
    return get(index)[current_choice_index[index]];
}

// ------------
// voting_read
// ------------
Ballot voting_read_ballots(istream& r, string& line, int& num_ballots) {
    Ballot ballots;

    while (getline(r, line)) {
        vector<int> votes;
        istringstream issstream(line);
        while (! issstream.eof()) {
            int vote = - 1;
            issstream >> vote;
            votes.push_back(vote - 1);
        }

        ballots.add_ballot(votes);
        num_ballots ++;
        if (r.peek() == '\n') {
            r.get();
            break; }
    }
    return ballots;
}

bool voting_check_tie(vector<int>& winners_if_tie, Result& current_results) {

    bool tie = true;

    for (int current_result_index = 0; current_result_index < current_results.size(); ++ current_result_index) {
        int current_result = current_results.get(current_result_index);
        if (current_result != current_results.get_max() && current_result != 0) {
            tie = false;
        } else if (current_result > 0) {
            winners_if_tie.push_back(current_result_index);
        }
    }

    return tie;
}

// todo: delete this
void print_current_results(Result& current_results) {
    for (int i = 0; i < current_results.size(); i ++) {
        cout << "current_result[" << i  + 1<< "]: " << current_results.get(i) << "\n";
    }
}

void voting_increment_losing_ballots(vector<int>& losing_ballots, Ballot& ballots, Result& current_results, vector<int>& losers) {
    for (int i = losing_ballots.size() - 1; i >= 0; i --) {
        int ballot = losing_ballots[i];
        int loser = ballots.get_current_result(ballot);
        if (!(find(losers.begin(), losers.end(), loser) != losers.end())) {
            losers.push_back(loser);
        }
    }

    for (int i = losing_ballots.size() - 1; i >= 0; i --) {
        int ballot = losing_ballots[i];
        int loser = ballots.get_current_result(ballot);
        int place = ballots.increment_choice_index(ballot);
        current_results.set(loser, 0);
        int beneficiary = ballots.get_current_result(ballot);
        while (find(losers.begin(), losers.end(), beneficiary) != losers.end() && place != (ballots.get(ballot).size() - 1)) {
            place = ballots.increment_choice_index(ballot);
            beneficiary = ballots.get_current_result(ballot);
        }
        if (!(find(losers.begin(), losers.end(), beneficiary) != losers.end())) {
            current_results.set(beneficiary, current_results.get(beneficiary) + 1);
        }
        losing_ballots.erase(losing_ballots.begin() + i);
    }

}

// todo: delete this
void print_current_results_cand(vector<string>& candidates, Result& current_results) {
    for (int i = 0; i < current_results.size(); i ++) {
        cout << "current_result[" << candidates[i] << "](" << i+ 1 << "): " << current_results.get(i) << "\n";
    }
}

// -----------------
// voting_get_winner
// -----------------

vector<int> voting_get_winner (vector<string>& candidates, Ballot& ballots, Result& current_results) {
    //for a first pass, increment the current results with the current index for each ballot

    for (int ballot_index = 0; ballot_index < ballots.size(); ballot_index ++) {
        current_results.set(ballots.get(ballot_index)[0], current_results.get(ballots.get(ballot_index)[0]) + 1);
    }

//    print_current_results(current_results);
//    cout << "!!! min: " << current_results.get_min() << "\n";

    vector<int> winners_if_tie;
    bool is_tie = voting_check_tie(winners_if_tie, current_results);
    if (is_tie) {
        return winners_if_tie;
    }

    vector<int> losing_ballots;
    vector<int> losers;
    vector<int> winners;


    for (int current_result_index = 0; current_result_index < current_results.size(); current_result_index ++) {
        int current_result = current_results.get(current_result_index);
        if (current_result > ballots.size() / 2) {
            winners.push_back(current_result_index);
            return winners;
        }
        if (current_results.get(current_result_index) == current_results.get_min()) {
            losers.push_back(current_result_index);
            // todo: find a way to optimize this later
            for (int ballot_index = 0; ballot_index < ballots.size(); ++ ballot_index) {
                if (ballots.get_current_result(ballot_index) == current_result_index) {
                    losing_ballots.push_back(ballot_index);
                }
            }
        } else if (current_results.get(current_result_index) == 0) {
            losers.push_back(current_result_index);
        }
    }

    while (losing_ballots.size() > 0) {
//        cout << "before increment:" << "\n";
//        print_current_results_cand(candidates, current_results);
        voting_increment_losing_ballots(losing_ballots, ballots, current_results, losers);
//        cout << "after increment:" << "\n";
//        print_current_results_cand(candidates, current_results);
        vector<int> winners_if_tie;
        bool is_tie = voting_check_tie(winners_if_tie, current_results);
        if (is_tie) {
            return winners_if_tie;
        }

        while (!losing_ballots.empty())
        {
            losing_ballots.pop_back();
        }

        for (int current_result_index = 0; current_result_index < current_results.size(); current_result_index ++) {
            int current_result = current_results.get(current_result_index);
            if (current_result > ballots.size() / 2) {
                winners.push_back(current_result_index);
                return winners;
            }
            if (current_results.get(current_result_index) == current_results.get_min()) {

                for (int ballot_index = 0; ballot_index < ballots.size(); ballot_index ++) {
                    if (ballots.get_current_result(ballot_index) == current_result_index) {
                        losing_ballots.push_back(ballot_index);
                    }
                }
            }
        }
    }
    for (int current_result_index = 0; current_result_index < current_results.size(); current_result_index ++) {
        int current_result = current_results.get(current_result_index);
        if (current_result == current_results.get_max()) {
            winners.push_back(current_result_index);
        }
    }
    return winners;
}

// -------------
// voting_solve
// -------------

void voting_solve (istream& r, ostream& w) {
    int num_cases;

    string line;
    getline(r, line);
    istringstream iss(line);
    iss >> num_cases;
    getline(r, line);

    for (int i = 0; i < num_cases; ++ i) {
        int num_candidates = 0;
        int num_ballots = 0;

        line = "";
        getline(r, line);
        istringstream iss2(line);
        iss2 >> num_candidates;
        vector <string> candidates;
        vector<int> current_results_vector;

        for (int j = 0; j < num_candidates; ++j) {
            line = "";
            getline(r, line);
            candidates.push_back(line);
            current_results_vector.push_back(0);
        }

        Result current_results(current_results_vector);

        Ballot ballots = voting_read_ballots(r, line, num_ballots);

        vector<int> winners = voting_get_winner(candidates, ballots, current_results);

        if (i != num_cases - 1) {
            for (int winner : winners) {
                w << candidates[winner] << "\n";
            }
            w << "\n";
        } else {
            for (int j = 0; j < winners.size(); j ++) {
                if (j != winners.size() - 1) {
                    w << candidates[winners[j]] << "\n";
                } else {
                    w << candidates[winners[j]];
                }

            }
        }
    }
    w << "\n";
}

// ----
// main
// ----

int main () {
    voting_solve(cin, cout);
    return 0;}
