INC_DIR = include
SRC     = src
TARGET  = hw3
OBJECTS = atom.o number.o variable.o term.o struct.o
UTEST = *.h



all: $(TARGET)

$(TARGET): $(OBJECTS) main.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) $(OBJECTS) main.o -lgtest
else
	g++ -o $(TARGET) $(OBJECTS) main.o -lgtest -lpthread
endif

# $(OBJECTS): %.o: $(SRC)/%.cpp
# 	g++ -std=gnu++0x -c $<

	
main.o: $(SRC)/main.cpp $(UTEST)
	g++ -std=gnu++0x -c $(SRC)/main.cpp

atom.o: $(SRC)/atom.cpp $(INC_DIR)/atom.h
	g++ -std=gnu++0x -c $(SRC)/atom.cpp

number.o: $(SRC)/number.cpp $(INC_DIR)/number.h
	g++ -std=gnu++0x -c $(SRC)/number.cpp

variable.o: $(SRC)/variable.cpp $(INC_DIR)/variable.h
	g++ -std=gnu++0x -c $(SRC)/variable.cpp

term.o: $(SRC)/term.cpp $(INC_DIR)/term.h
	g++ -std=gnu++0x -c $(SRC)/term.cpp

struct.o: $(SRC)/atom.cpp $(INC_DIR)/struct.h
	g++ -std=gnu++0x -c $(SRC)/struct.cpp
	
clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif
	
test:
	make clean
	make
	./$(TARGET)