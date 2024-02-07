OBJECTS = ADE.o StringUtil.o FileData.o

FLAGS = -Wall
COMP = g++

all: ADE

ADE: $(OBJECTS)
	$(COMP) -o ADE $(OBJECTS) $(FLAGS)

ADE.o: ADE.cpp
	$(COMP) -c ADE.cpp

StringUtil.o: StringUtil.cpp
	$(COMP) -c StringUtil.cpp

FileData.o: FileData.cpp
	$(COMP) -c FileData.cpp

clean:
	rm ADE *.o