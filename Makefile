
CXX=g++
CXXFLAGS=-std=c++11 -Werror -Wall -Wsign-conversion

SOURCES=Graph.cpp Algorithms.cpp
OBJECTS=$(SOURCES:.cpp=.o)

#run the main by ./main
EXEC=main
#run the tests by ./tests
TEST_EXEC=tests

#make all
all: $(EXEC) $(TEST_EXEC)

#make main
$(EXEC): main.o $(filter-out tests.o, $(OBJECTS))
	$(CXX) $(CXXFLAGS) $^ -o $@

# make tests
$(TEST_EXEC): tests.o $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


test: $(TEST_EXEC)
	./$(TEST_EXEC)

# make clean
clean:
	rm -f *.o $(EXEC) $(TEST_EXEC)

# check if the memory is ok
valgrind: $(EXEC)
	valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all --error-exitcode=99 ./$(EXEC)


.PHONY: all clean test valgrind
