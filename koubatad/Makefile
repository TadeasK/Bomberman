# Compilator aliases
CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++17 -O2

# Doxygen comfiguration file
DOX=Doxyfile

# Remove alias
RM=rm -rf

# Final executable binary file
BIN=koubatad

# What to put into zip file
ZIP=zadani.txt $(wildcard src/*.hpp) doc/

# modules to make 
# ls *.cpp | sed 's/.cpp/.o/g' | tr '\n' ' '
MODULES=tmp/Bomb.o tmp/BuffBomb.o tmp/BuffDetonator.o tmp/BuffMove.o tmp/BuffRadius.o tmp/BuffThrow.o tmp/Crate.o tmp/Enemy.o tmp/Entity.o tmp/ExitDoor.o tmp/GameLoop.o tmp/main.o tmp/MainMenu.o tmp/Monster1.o tmp/Monster2.o tmp/Monster3.o tmp/Object.o tmp/Player.o tmp/Special.o tmp/Wall.o

# Makefile parameters

# Generate all outputs, documentation
all: $(MODULES) $(DOX)
	make compile
	make doc

# Create binary executable of the whole program
compile: $(BIN)

# Run the exectuable
run: compile
	./$(BIN)

# Removes all created files
clean:
	$(RM) tmp doc $(BIN) $(BIN).zip 2>/dev/null

# Generates documentation
doc: $(DOX)
	doxygen $(DOX) > /dev/null

# Crate .zip file to hand in (final/check point)
zip: ${BIN}.zip

${BIN}.zip: ${ZIP}
	rm -rf tmp/
	rm -f $@
	mkdir -p tmp/${BIN}/
	cp --parents -r $^ tmp/${BIN}/
	cd tmp/ && zip -r ../$@ ${BIN}/
	rm -rf tmp/

# Compile and Link
$(BIN): $(MODULES)
	@mkdir -p tmp/
	$(CXX) $(CXXFLAGS) $^ -o $@

tmp/%.o: src/%.cpp
	@mkdir -p tmp/
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Program dependencies //TODO


