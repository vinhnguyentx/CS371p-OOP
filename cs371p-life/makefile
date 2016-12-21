FILES :=                              \
    .travis.yml                       \
    life-tests/vtn288-TestLife.c++ 	\
    life-tests/vtn288-TestLife.out 	\
	life-tests/vtn288-RunLife.in	 \
	life-tests/vtn288-RunLife.out 		\
    Life.h                         \
	Life.log						\
	Life.pdf                       \
	Life.c++                       \
	RunLife.in						\
	RunLife.out						\
	RunLife.c++						\
    html                              \
    TestLife.c++                   \
    TestLife.out

CXX        := g++-4.8
CXXFLAGS   := -pedantic -std=c++11 -Wall
LDFLAGS    := -lgtest -lgtest_main -pthread
GCOV       := gcov-4.8
GCOVFLAGS  := -fprofile-arcs -ftest-coverage
VALGRIND   := valgrind

check:
	@not_found=0;                                 \
    for i in $(FILES);                            \
    do                                            \
        if [ -e $$i ];                            \
        then                                      \
            echo "$$i found";                     \
        else                                      \
            echo "$$i NOT FOUND";                 \
            not_found=`expr "$$not_found" + "1"`; \
        fi                                        \
    done;                                         \
    if [ $$not_found -ne 0 ];                     \
    then                                          \
        echo "$$not_found failures";              \
        exit 1;                                   \
    fi;                                           \
    echo "success";

clean:
		rm -f *.gcda
		rm -f *.gcno
		rm -f *.gcov
		rm -f RunLife
		rm -f RunLife.out
		rm -f TestLife
		rm -f TestLife.out


config:
	git config -l

scrub:
	make clean
	rm -f  life.log
	rm -rf life-tests
	rm -rf html
	rm -rf latex

status:
	make clean
	@echo
	git branch
	git remote -v
	git status

test: TestLife


life-tests:
	git clone https://github.com/cs371p-fall-2015/life-tests.git

html: Doxyfile Life.h Life.c++ RunLife.c++ TestLife.c++
		doxygen Doxyfile

Life.log:
	git log > Life.log

Doxyfile:
	doxygen -g

RunLife: Life.h Life.c++ RunLife.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Life.c++ RunLife.c++ -o RunLife

RunLife.out: RunLife
	./RunLife < RunLife.in > RunLife.out

TestLife: Life.h Life.c++ TestLife.c++
	$(CXX) $(CXXFLAGS) $(GCOVFLAGS) Life.c++ TestLife.c++ -o TestLife $(LDFLAGS)

TestLife.out: TestLife
	$(VALGRIND) ./TestLife                                       >  TestLife.out 2>&1
	$(GCOV) -b Life.c++     | grep -A 5 "File 'Life.c++'"     >> TestLife.out
	$(GCOV) -b TestLife.c++ | grep -A 5 "File 'TestLife.c++'" >> TestLife.out
	cat TestLife.out
