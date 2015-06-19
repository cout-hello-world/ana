CXX = g++
CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Werror -O2

ana: ana.o enable.o
	$(CXX) $(CXXFLAGS) ana.o enable.o -o ana
ana.o: ana.cpp enable.hpp
	$(CXX) -c $(CXXFLAGS) ana.cpp
enable.o: enable.cpp enable.hpp
	$(CXX) -c $(CXXFLAGS) enable.cpp

clean:
	$(RM) *.o ana
