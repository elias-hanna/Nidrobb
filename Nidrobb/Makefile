# options de compilation
CC =g++ -std=c++11
CCFLAGS = -Wall -g #-msse3 #-msse2
LDFLAGS = -lboost_unit_test_framework -lSDL2 -lSDL2_image #-lSDL_mixer 


# fichiers du projet
MAIN = main.cpp
SRC = Toolbox.cpp Command/InputMap.cpp gui/display.cpp gui/sprite.cpp Animation/Animation.cpp Animation/AnimationFrame.cpp Animation/AnimationBuilder.cpp GameEnv/Game.cpp GameEnv/WorldBuilder.cpp GameEnv/World.cpp GameEnv/Obstacle.cpp GameEnv/Player.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = Nidrobb

TESTSRC = Unitests/AnimationTest.cpp #Unitests/WorldTest.cpp #Unitests/ObstacleTest.cpp #Unitests/InputMapTest.cpp #Unitests/AnimationTest.cpp #Unitests/AnimationFrameTest.cpp #Unitests/ToolboxTest.cpp #Unitests/SpriteTest.cpp 
TESTOBJ = $(TESTSRC:.cpp=.o)

# règle initiale
all: $(EXEC) #clean

# dépendance des .hpp
%.o: %.hpp

# règles de compilation
%.o: %.cpp
	$(CC) $(CCFLAGS) -o $@ -c $<

# règles d'édition de liens
$(EXEC): $(MAIN:.cpp=.o) $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# règles supplémentaires
clean:
	rm -rf $(MAIN:.cpp=.o) $(OBJ) $(TESTOBJ) 
rmproper:
	rm -rf $(EXEC) Unitest

Unitest: $(OBJ) $(TESTOBJ)
	$(CC) -o $@ $^ $(LDFLAGS) && ./$@ --log_level=test_suite

