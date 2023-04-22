CC                 =   g++ -std=c++17
FLAGS              =   -c 
SOURCE             =   $(foreach dir, $(ALGORITHMSDIR) $(GRAPHDIR), $(wildcard $(dir)/*.cc))
SOURCEINTERFACE    =   $(foreach dir, $(SOURCEDIR), $(wildcard $(dir)/*.cc))
SOURCEALGORITHMS   =   $(wildcard $(ALGORITHMSDIR)/*.cc)
SOURCEGRAPH        =   $(wildcard $(GRAPHDIR)/*.cc)
GRAPHDIR           =   ./graph
ALGORITHMSDIR      =   ./algorithms
OBJECTS            =   $(addprefix $(BUILDDIR)/, $(notdir $(SOURCE:.cc=.o)))
OBJECTSGRAPH       =   $(addprefix $(BUILDDIR)/, $(notdir $(SOURCEGRAPH:.cc=.o)))
OBJECTSALGORITHMS  =   $(addprefix $(BUILDDIR)/, $(notdir $(SOURCEALGORITHMS:.cc=.o)))
BUILDDIR           =   ./build
LIBSDIR            =   ./libs
LIBNAME            =   graphlib
GRAPHLIB           =   graph
ALGORITHMSLIB      =   graph_algorithms
SOURCEDIR          =   ./graph ./algorithms ./interface
CONTAINERS         =   $(wildcard containers/*)
TESTDIR            =   ./tests
MAIN               =   ./main.cc
GCOV               =   --coverage

.PHONY: all clean interface

all: interface

libs: clean cbuild $(GRAPHLIB).a $(ALGORITHMSLIB).a

clean:
	@rm -rf *.gcno *.gcda *.gcov *.info report main
	@rm -rf $(BUILDDIR) $(LIBSDIR)
	@rm -rf *.o

cbuild:
	mkdir ./build ./libs

$(BUILDDIR)/$(GRAPHLIB).o: $(SOURCEGRAPH)
	$(CC) $(FLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(ALGORITHMSDIR)/%.cc
	$(CC) $(FLAGS) $< -o $@

$(ALGORITHMSLIB).a: $(OBJECTSGRAPH) $(OBJECTSALGORITHMS)
	ar rcs $(LIBSDIR)/$@ $^

$(GRAPHLIB).a: $(OBJECTSGRAPH)
	ar rcs $(LIBSDIR)/$@ $^

main: clean
	$(CC) $(SOURCE) -o main
	./main

test: clean cbuild $(ALGORITHMSLIB).a
	$(CC) $(TESTDIR)/*.cc $(LIBSDIR)/$(ALGORITHMSLIB).a $(GCOV) -lgtest -o $(BUILDDIR)/test
	$(BUILDDIR)/test

gcov_report: test
	lcov -t "test" --no-external -o test.info -c -d ./
	genhtml -o report test.info
	open report/index.html

interface:
	$(CC) $(MAIN) $(SOURCEINTERFACE) $(LIBSFLAGS) -o main
	./main

lint:
	@cp ../materials/linters/.clang-format .
	@clang-format -i --verbose $(SOURCEINTERFACE) $(CONTAINERS) $(TESTDIR)/*.cc $(GRAPHDIR)/*
	@rm -f .clang-format