INC_DIR = include
TARGET = hw1
all: $(TARGET)
ifeq (${OS}, Windows_NT) 
	g++ -o $(NAME) main.o Shapes.o Media.o Sort.o -lgtest
else
$(TARGET): main.o Media.o Shapes.o Sort.o
	g++ -o $(TARGET) main.o Shapes.o Media.o Sort.o -lgtest -lpthread
endif

	
main.o: main.cpp utSort.h
	g++ -std=gnu++0x -c main.cpp

Shapes.o: $(INC_DIR)/Shapes.h Shapes.cpp
	g++ -std=gnu++0x -c Shapes.cpp

Media.o: $(INC_DIR)/Media.h Media.cpp
	g++ -std=gnu++0x -c Media.cpp

Sort.o: $(INC_DIR)/Sort.h Sort.cpp
	g++ -std=gnu++0x -c Sort.cpp

clean:	
ifeq (${OS}, Windows_NT) 
	del *.o $(TARGET).exe
else
	rm -f *.o $(TARGET)
endif
	
