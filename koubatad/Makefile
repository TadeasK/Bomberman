# Compilator aliases
CXX=g++
CXXFLAGS=-Wall -pedantic -std=c++17 -O2
DEBUGFLAGS=-Wall -pedantic -g -std=c++17 -O2
VALGRINDFLAGS=-s --leak-check=full --show-leak-kinds=all
# Doxygen comfiguration file
DOX=Doxyfile

# Remove alias
RM=rm -rf

# Final executable binary file
BIN=koubatad

# What to put into zip file
ZIP=zadani.txt prohlaseni.txt src/ assets/ examples/ Doxyfile Makefile

# modules to make 
# ls src/*.cpp | sed 's/.cpp/.o/g' | sed 's/src/tmp/g' | tr '\n' ' '
MODULES=tmp/Bomb.o tmp/BuffBomb.o tmp/BuffDetonator.o tmp/BuffHeal.o tmp/BuffLevitate.o tmp/BuffRadius.o tmp/Crate.o \
tmp/Enemy.o tmp/Entity.o tmp/Explosion.o tmp/GameManager.o tmp/GameMenu.o tmp/LevelMenu.o tmp/main.o tmp/MainMenu.o \
tmp/Menu.o tmp/Object.o tmp/OptionsMenu.o tmp/Player.o tmp/ScoreMenu.o tmp/Special.o tmp/Wall.o

# tmp/Monster1.o tmp/Monster2.o tmp/Monster3.o tmp/BuffBomb.o tmp/BuffDetonator.o tmp/BuffMove.o tmp/BuffRadius.o tmp/BuffThrow.o tmp/ExitDoor.o

# Makefile parameters

# Generate all outputs, documentation
all: compile doc

# Create binary executable of the whole program
compile: deps $(BIN)

# Run the exectuable
run: compile
	./$(BIN)

# Removes all created files
clean:
	$(RM) tmp doc $(BIN) $(BIN).zip debug.txt 2>/dev/null

# Generates documentation
doc:
	doxygen $(DOX) > /dev/null

# Crate .zip file to hand in (final/check point)
zip: $(BIN).zip

$(BIN).zip: $(ZIP)
	rm -rf tmp/
	rm -f $@
	mkdir -p tmp/$(BIN)/
	cp --parents -r $^ tmp/$(BIN)/
	cd tmp/ && zip -r ../$@ $(BIN)/
	rm -rf tmp/

# Compile and run in debug mode
debug: compile
	valgrind $(VALGRINDFLAGS) ./$(BIN) 2> debug.txt

test: compile
	./$(BIN) -test

# Compile and Link
$(BIN): $(MODULES)
	@mkdir -p tmp/
	$(CXX) $(CXXFLAGS) -o $@ $^ -lncurses

# Generate dependencies
deps:
	@mkdir -p tmp/
	$(CXX) -MM src/*.cpp > tmp/Makefile.d

tmp/%.o: src/%.cpp
	@mkdir -p tmp/
	$(CXX) $(CXXFLAGS) -c $< -o $@

-include Makefile.d




