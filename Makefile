CC=g++
CFLAGS=-g -c -Wall -std=gnu++11
LDFLAGS=-g -Wall -std=gnu++11

SOURCES=cpu.cpp Controller.cpp GameState.cpp MemoryWatcher.cpp
GOALS=Goals/*.cpp
STRATS=Strategies/*.cpp
TACTICS=Tactics/*.cpp
CHAINS=Chains/*.cpp
SOURCES=cpu.cpp Controller.cpp GameState.cpp MemoryWatcher.cpp

SOURCES=cpu.o bin/Controller.o bin/GameState.o bin/MemoryWatcher.o
STRATS=Strategies/Bait.o
TACTICS=Tactics/CloseDistance.o bin/Tactics/Edgeguard.o bin/Tactics/Laser.o bin/Tactics/Parry.o bin/Tactics/Punish.o bin/Tactics/Recover.o bin/Tactics/ShineCombo.o bin/Tactics/Wait.o
CHAINS=Chains/EdgeAction.o bin/Chains/EdgeStall.o bin/Chains/FireFox.o bin/Chains/FullJump.o bin/Chains/GrabEdge.o bin/Chains/Jab.o bin/Chains/JumpCanceledShine.o bin/Chains/MarthKiller.o bin/Chains/Multishine.o bin/Chains/Nothing.o bin/Chains/Powershield.o bin/Chains/Run.o bin/Chains/SHDL.o bin/Chains/ShineUpsmash.o bin/Chains/SmashAttack.o bin/Chains/SpotDodge.o bin/Chains/TransitionHelper.o bin/Chains/Walk.o bin/Chains/Wavedash.o bin/Chains/Waveshine.o
GOALS=Goals/KillOpponent.o bin/Goals/NavigateMenu.o
EXECUTABLE=cpu


DIRS = Goals Strategies Tactics Chains


all: $(GOALS) $(STRATS) $(TACTICS) $(CHAINS) $(SOURCES)
	$(CC) $(LDFLAGS) -o $(EXECUTABLE) bin/*.o bin/*/*.o

main:
	$(CC) $(CFLAGS) $(SOURCES)

bin/Goals/%.o: Goals/%.cpp
	$(CC) $(CFLAGS) $< -o bin/$@

bin/Strategies/%.o: Strategies/%.cpp
	$(CC) $(CFLAGS) $< -o bin/$@

bin/Tactics/%.o: Tactics/%.cpp
	$(CC) $(CFLAGS) $< -o bin/$@

bin/Chains/%.o: Chains/%.cpp
	$(CC) $(CFLAGS) $< -o bin/$@

bin/%.o: %.cpp
	$(CC) $(CFLAGS) $< -o bin/$@

clean:
	rm -f *.o */*.o *.d */*.d $(EXECUTABLE)
	rm -f ./*/*.o




# all: goals2 strats2 tactics2 chains2 main
# 	$(CC) $(LDFLAGS) *.o -o $(EXECUTABLE)

# main:
# 	$(CC) $(CFLAGS) $(SOURCES)

# # goals:
# # 	$(CC) $(CFLAGS) $(GOALS)

# strats2: 
# 	$(CC) $(CFLAGS) $(STRATS)

# tactics2:
# 	$(CC) $(CFLAGS) $(TACTICS)

# chains2: 
# 	$(CC) $(CFLAGS) $(CHAINS) 

