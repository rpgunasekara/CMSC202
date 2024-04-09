CXX = g++
CXXFLAGS = -Wall

proj2: Pokemon.o Game.o proj2.cpp
        $(CXX) $(CXXFLAGS) Pokemon.o Game.o proj2.cpp -o proj2

Game.o: Game.h Game.cpp Pokemon.o
        $(CXX) $(CXXFLAGS) -c Game.cpp

Pokemon.o: Pokemon.cpp Pokemon.h
        $(CXX) $(CXXFLAGS) -c Pokemon.cpp

clean:
        rm *.o*
        rm *~

run:
        ./proj2 proj2_pokeDex.txt
