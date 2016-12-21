CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
GPROF      := gprof
GPROFFLAGS := -pg
VALGRIND   := valgrind

all: $(sort $(patsubst %-RunVoting.in,%-RunVoting.tmp,$(wildcard *-RunVoting.in)))

RunVoting: ../RunVoting
	make -C .. voting-tests/RunVoting

%-RunVoting.tmp: RunVoting %-RunVoting.in %-RunVoting.out
	./RunVoting < $(*F)-RunVoting.in > $(*F)-RunVoting.tmp
	diff $(*F)-RunVoting.tmp $(*F)-RunVoting.out

%-TestVoting: Voting.h Voting.c++ %-TestVoting.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Voting.c++ $@.c++ -o $@ $(LDFLAGS)

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunVoting
	rm -f *-RunVoting.tmp
	rm -f *-TestVoting
	rm -f *-TestVoting.tmp