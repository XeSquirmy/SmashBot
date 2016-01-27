CC=g++
CFLAGS=-g -c -Wall -std=gnu++11
LDFLAGS=-g -Wall -std=gnu++11

SOURCES=cpu.cpp Controller.cpp GameState.cpp MemoryWatcher.cpp
GOALS=Goals/*.cpp
STRATS=Strategies/*.cpp
TACTICS=Tactics/*.cpp
CHAINS=Chains/*.cpp

EXECUTABLE=cpu

all: goals2 strats2 tactics2 chains2 main
	$(CC) $(LDFLAGS) *.o -o $(EXECUTABLE)

main:
	$(CC) $(CFLAGS) $(SOURCES)

goals2:
	$(CC) $(CFLAGS) $(GOALS)

strats2: 
	$(CC) $(CFLAGS) $(STRATS)

tactics2:
	$(CC) $(CFLAGS) $(TACTICS)

chains2: 
	$(CC) $(CFLAGS) $(CHAINS)


clean:
	rm -f *.o */*.o *.d */*.d cpu


