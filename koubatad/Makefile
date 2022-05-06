# Compilator aliases
CXX=g++
CXXFLAGS= -Wall -pedantic -std=c++17

# Doxygen comfiguration file
DOX=Doxyfile

# Remove alias
RM=rm -rf

# Final executable binary file
BIN=./koubatad

# modules to make 
# ls *.cpp | sed 's/.cpp/.o/g' | tr '\n' ' '
MODULES=tmp/Bomb.o tmp/Bonus.o tmp/Crate.o tmp/Enemy.o tmp/Entity.o tmp/main.o tmp/Object.o tmp/Player.o tmp/Wall.o

# Makefile parameters

# Generate all outputs, documentation
all: $(MODULES) $(DOX)
	make compile
	make doc

# Create binary executable of the whole program
compile: $(BIN)

# Run the exectuable
run: $(BIN)

# Removes all created files
clean:
	$(RM) tmp doc $(BIN)

# Generates documentation
doc: $(DOX)
	doxygen $(DOX) > /dev/null


# Compile and Link
$(BIN): $(MODULES)
	$(CXX) $(CXXFLAGS) $(MODULES) -o $(BIN)

# Program dependencies //TODO
tmp/Bomb.o: src/Bomb.cpp src/Bomb.hpp src/Object.hpp
tmp/Bonus.o: src/Bonus.cpp src/Bonus.hpp src/Object.hpp
tmp/Crate.o: src/Crate.cpp src/Crate.hpp src/Object.hpp
tmp/Enemy.o: src/Enemy.cpp src/Enemy.hpp src/Entity.hpp src/Object.hpp
tmp/Entity.o: src/Entity.cpp src/Entity.hpp src/Object.hpp
tmp/main.o: src/main.cpp
tmp/Object.o: src/Object.cpp src/Object.hpp
tmp/Player.o: src/Player.cpp src/Player.hpp src/Entity.hpp src/Object.hpp
tmp/Wall.o: src/Wall.cpp src/Wall.hpp src/Object.hpp

