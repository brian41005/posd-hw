CXX      = g++
CPPFLAGS = -std=gnu++0x
INC_DIR  = include
SRC      = src
TARGET   = hw8
PROLOG_SHELL = shell

OBJECTS  = atom.o number.o  variable.o term.o struct.o \
		   list.o scanner.o parser.o prolog.o node.o \
		   parserInfo.o iterator.o
UTEST    = $(utest *.h) $(./ *.h)


all: $(TARGET) $(PROLOG_SHELL)

$(TARGET): $(OBJECTS) main.o
ifeq (${OS}, Windows_NT) 
	$(CXX) -o $(TARGET) $(OBJECTS) main.o -lgtest
else
	$(CXX) -o $(TARGET) $(OBJECTS) main.o -lgtest -lpthread
endif

$(PROLOG_SHELL): $(OBJECTS) shell.o
ifeq (${OS}, Windows_NT) 
	$(CXX) -o $(PROLOG_SHELL) $(OBJECTS) shell.o -lgtest
else
	$(CXX) -o $(PROLOG_SHELL) $(OBJECTS) shell.o -lgtest -lpthread
endif

$(OBJECTS): %.o: $(SRC)/%.cpp $(INC_DIR)/%.h
	$(CXX) $(CPPFLAGS) -c $<

shell.o: $(SRC)/shell.cpp
	$(CXX) $(CPPFLAGS) -c $(SRC)/shell.cpp

main.o: $(SRC)/main.cpp $(UTEST)
	$(CXX) $(CPPFLAGS) -c $(SRC)/main.cpp


clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET) $(PROLOG_SHELL)
endif


test:
	make clean
	make
	./$(TARGET)
	make clean