INC_DIR = include
SRC     = src
TARGET  = hw3
objects = atom.o number.o variable.o term.o struct.o

all: $(TARGET)

$(TARGET): $(objects) main.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(TARGET) $(objects) main.o -lgtest
else
	g++ -o $(TARGET) $(objects) main.o -lgtest -lpthread
endif

$(objects): %.o: $(SRC)/%.cpp
	g++ -std=gnu++0x -c $<

main.o: $(SRC)/main.cpp utTerm.h utStruct.h utVariable.h
	g++ -std=gnu++0x -c $(SRC)/main.cpp

clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif
	
