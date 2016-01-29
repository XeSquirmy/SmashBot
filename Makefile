CC=g++
CFLAGS=-g -c -Wall -std=gnu++11
LDFLAGS=-g -Wall -std=gnu++11

SOURCES=cpu.cpp Controller.cpp GameState.cpp MemoryWatcher.cpp
GOALS=Goals/*.cpp
STRATS=Strategies/*.cpp
TACTICS=Tactics/*.cpp
CHAINS=Chains/*.cpp
SOURCES=cpu.cpp Controller.cpp GameState.cpp MemoryWatcher.cpp



SOURCES=cpu.o Controller.o GameState.o MemoryWatcher.o
STRATS=Strategies/Bait.o
TACTICS=Tactics/CloseDistance.o Tactics/Edgeguard.o Tactics/Laser.o Tactics/Parry.o Tactics/Punish.o Tactics/Recover.o Tactics/ShineCombo.o Tactics/Wait.o
CHAINS=Chains/EdgeAction.o Chains/EdgeStall.o Chains/FireFox.o Chains/FullJump.o Chains/GrabEdge.o Chains/Jab.o Chains/JumpCanceledShine.o Chains/MarthKiller.o Chains/Multishine.o Chains/Nothing.o Chains/Powershield.o Chains/Run.o Chains/SHDL.o Chains/ShineUpsmash.o Chains/SmashAttack.o Chains/SpotDodge.o Chains/TransitionHelper.o Chains/Walk.o Chains/Wavedash.o Chains/Waveshine.o
GOALS=Goals/KillOpponent.o Goals/NavigateMenu.o
EXECUTABLE=cpu

# all: goals2 strats2 tactics2 chains2 main
# 	$(CC) $(LDFLAGS) *.o -o $(EXECUTABLE)




all: $(GOALS) $(STRATS) $(TACTICS) $(CHAINS) $(SOURCES)
	echo "done everything, just going to print compile the executable $(STRATS)"
	$(CC) $(LDFLAGS) -o cpu *.o */*.o

main:
	$(CC) $(CFLAGS) $(SOURCES)

Goals/%.o: Goals/%.cpp
	echo "going to compile $< into $@"
	$(CC) $(CFLAGS) $< -o $@

Strategies/%.o: Strategies/%.cpp
	echo "going to compile $< into $@"
	$(CC) $(CFLAGS) $< -o $@

Tactics/%.o: Tactics/%.cpp
	echo "going to compile $< into $@"
	$(CC) $(CFLAGS) $< -o $@

Chains/%.o: Chains/%.cpp
	echo "going to compile $< into $@"
	$(CC) $(CFLAGS) $< -o $@

%.o: %.cpp
	echo "inside the normal base folder"
	$(CC) $(CFLAGS) $< -o $@

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


clean:
	rm -f *.o */*.o *.d */*.d $(EXECUTABLE)
	rm -f ./*/*.o


