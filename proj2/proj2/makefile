CXX = g++
CXXFLAGS = -Wall -g -std=c++11

proj2.x: test_list.o
	$(CXX) $(CXXFLAGS) -o proj2.x test_list.o

test_list.o:
	$(CXX) $(CXXFLAGS) -c test_list.cpp

clean:
	rm proj2.x
