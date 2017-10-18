CXX = g++
CPPFLAGS = -std=gnu++0x
INC_DIR = include
SRC     = src
TARGET  = hw3
OBJECTS = atom.o number.o variable.o term.o struct.o
UTEST = $(utest *.h)
UTEST_IN_ROOT = $(./ *.h)

all: $(TARGET)

$(TARGET): $(OBJECTS) main.o
ifeq (${OS}, Windows_NT) 
	$(CXX) -o $(TARGET) $(OBJECTS) main.o -lgtest
else
	$(CXX) -o $(TARGET) $(OBJECTS) main.o -lgtest -lpthread
endif

$(OBJECTS): %.o: $(SRC)/%.cpp
	$(CXX) $(CPPFLAGS) -c $<

	
main.o: $(SRC)/main.cpp $(UTEST) $(UTEST_IN_ROOT)
	$(CXX) $(CPPFLAGS) -c $(SRC)/main.cpp


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
	make clean