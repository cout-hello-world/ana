CXXFLAGS = -std=c++11 -pedantic -Wall -Wextra -Werror -O2
OBJECTS = ana.o enable.o

ana: $(OBJECTS)
	$(CXX) -o $@ $(OBJECTS)
$(OBJECTS): enable.hpp

clean:
	$(RM) *.o ana
