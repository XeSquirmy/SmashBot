CC=g++
CFLAGS=-g -c -Wall -std=gnu++11
LDFLAGS=-g -Wall -std=gnu++11
EXECUTABLE = cpu

#DIRS = Goals Strategies Tactics Chains

allFiles := $(foreach path,$(wildcard */*.cpp *.cpp), $(patsubst %, bin/%, $(path:%.cpp=%.o)))
mains := bin/cpu.o

all: cpu

myShit: $(allFiles)
	$(CC) $(LDFLAGS) $(filter-out $(mains),$(allFiles)) bin/myStuff.o -o myStuff

cpu: $(allFiles)
	$(CC) $(LDFLAGS) $(filter-out $(mains), $(allFiles)) bin/cpu.o -o $(EXECUTABLE)


bin/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm bin/*/*.o bin/*.o $(mains) cpu


