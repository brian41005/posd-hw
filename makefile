CXX      = g++
CPPFLAGS = -std=gnu++0x
INC_DIR  = include
SRC      = src
TARGET   = hw4
OBJECTS  = atom.o number.o variable.o term.o struct.o list.o
UTEST    = $(utest *.h) $(./ *.h)


all: $(TARGET)

$(TARGET): $(OBJECTS) main.o
ifeq (${OS}, Windows_NT) 
	$(CXX) -o $(TARGET) $(OBJECTS) main.o -lgtest
else
	$(CXX) -o $(TARGET) $(OBJECTS) main.o -lgtest -lpthread
endif

$(OBJECTS): %.o: $(SRC)/%.cpp $(INC_DIR)/%.h
	$(CXX) $(CPPFLAGS) -c $<

	
main.o: $(SRC)/main.cpp $(UTEST)
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