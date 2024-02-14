OBJECTS = ADE.o StringUtil.o FileData.o PatchData.o Tests.o HelperFoo.o

FLAGS = -Wall
COMP = g++ -g -std=c++17

all: ADE

ADE: $(OBJECTS)
	$(COMP) -o ADE $(OBJECTS) $(FLAGS)

ADE.o: ADE.cpp
	$(COMP) -c ADE.cpp

StringUtil.o: StringUtil.cpp
	$(COMP) -c StringUtil.cpp

FileData.o: FileData.cpp
	$(COMP) -c FileData.cpp

PatchData.o: PatchData.cpp
	$(COMP) -c PatchData.cpp

Tests.o: Tests.cpp
	$(COMP) -c Tests.cpp

HelperFoo.o: HelperFoo.cpp
	$(COMP) -c HelperFoo.cpp

clean:
	rm ADE *.o