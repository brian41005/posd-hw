INC_DIR = include
SRC     = src
TARGET  = hw2

all: $(TARGET)

$(TARGET): main.o atom.o number.o variable.o simpleObj.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) main.o atom.o number.o variable.o simpleObj.o -lgtest
else
	g++ -o $(TARGET) main.o atom.o number.o variable.o simpleObj.o -lgtest -lpthread
endif

	
main.o: main.cpp utTerm.h
	g++ -std=gnu++0x -c main.cpp

atom.o: $(INC_DIR)/atom.h $(SRC)/atom.cpp
	g++ -std=gnu++0x -c $(SRC)/atom.cpp

number.o: $(INC_DIR)/number.h $(SRC)/number.cpp
	g++ -std=gnu++0x -c $(SRC)/number.cpp

variable.o: $(INC_DIR)/variable.h $(SRC)/variable.cpp
	g++ -std=gnu++0x -c $(SRC)/variable.cpp

simpleObj.o: $(INC_DIR)/simpleObj.h $(SRC)/simpleObj.cpp
	g++ -std=gnu++0x -c $(SRC)/simpleObj.cpp


clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif
	
