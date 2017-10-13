INC_DIR = include
SRC     = src
TARGET  = hw3
objects = main.o atom.o number.o variable.o term.o struct.o

all: $(TARGET)

$(TARGET): $(objects)
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) $(objects) -lgtest
else
	g++ -o $(TARGET) $(objects) -lgtest -lpthread
endif

$(objects): %.o: $(SRC)/%.cpp
	g++ -std=gnu++0x -c $<

# main.o: $(SRC)/main.cpp utTerm.h utStruct.h utVariable.h
# 	g++ -std=gnu++0x -c $(SRC)/main.cpp

# atom.o: $(INC_DIR)/atom.h $(SRC)/atom.cpp
# 	g++ -std=gnu++0x -c $(SRC)/atom.cpp


clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif
	
