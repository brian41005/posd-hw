
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

$(OBJECTS): %.o: $(SRC)/%.cpp
	g++ -std=gnu++0x -c $<

	
main.o: $(SRC)/main.cpp $(UTEST)
	g++ -std=gnu++0x -c $(SRC)/main.cpp


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