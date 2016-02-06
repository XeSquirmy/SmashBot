CC=g++
CFLAGS=-g -c -Wall -std=gnu++11
LDFLAGS=-g -Wall -std=gnu++11
EXECUTABLE = cpu

#DIRS = Goals Strategies Tactics Chains

allFiles := $(foreach path,$(wildcard */*.cpp *.cpp), $(patsubst %, bin/%, $(path:%.cpp=%.o)))
mains := bin/myStuff.o bin/cpu.o

all: myShit

myShit: $(allFiles)
	@echo "all files not filtered = $(allFiles)"
	@echo "all files filtered= $(filter-out bin/cpu.o,$(allFiles))"
	$(CC) $(LDFLAGS) $(filter-out $(mains),$(allFiles)) bin/myStuff.o -o myStuff

cpu: $(allFiles)
	$(CC) $(LDFLAGS) $(filter-out $(mains), $(allFiles)) bin/cpu.o -o $(EXECUTABLE)


# main:
# 	$(CC) $(LDFLAGS) $(allFiles) -o $(EXECUTABLE)

# bin/Goals/%.o: Goals/%.cpp
# 	echo "inside the bin goals"
# 	$(CC) $(CFLAGS) $< -o $@

# bin/Strategies/%.o: Strategies/%.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/Tactics/%.o: Tactics/%.cpp
# 	$(CC) $(CFLAGS) $< -o $@

# bin/Chains/%.o: Chains/%.cpp
# 	$(CC) $(CFLAGS) $< -o $@

bin/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm bin/*/*.o bin/*.o $(mains) cpu myStuff


