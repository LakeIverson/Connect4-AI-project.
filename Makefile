CXXFLAGS := -std=c++11 -Wall -Wextra -Werror

TARGETS := connect4

FILES_O := environment.o random_agent.o agent.o main.o
FILES_H := environment.h random_agent.h agent.h

all: $(TARGETS)

connect4: $(FILES_O)
	g++ $(CXXFLAGS) -o $@ $^

environment.o: environment.cpp $(FILES_H)
	g++ $(CXXFLAGS) -c -o $@ $<

random_agent.o: random_agent.cpp $(FILES_H)
	g++ $(CXXFLAGS) -c -o $@ $<

agent.o: agent.cpp $(FILES_H)
	g++ $(CXXFLAGS) -c -o $@ $<

################################
clean:
	rm -f *.o
	rm $(TARGETS)
