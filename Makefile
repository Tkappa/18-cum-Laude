NCURSES_ARG := -lncurses
UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S), Darwin)
	NCURSES_ARG := -lcurses
endif

all: main

main: build/main.o build/Controller.o build/Character.o build/MajorCharacter.o build/Follower.o build/Mappa.o build/View.o build/Stanza.o build/ability.o build/Item.o build/inventory.o
	g++ -std=c++11 -o dist/18Lode build/main.o build/Controller.o build/Character.o build/MajorCharacter.o build/Follower.o build/Mappa.o build/View.o build/Stanza.o build/ability.o $(NCURSES_ARG)

npc: build/mainC.o build/MajorCharacter.o
	g++ -std=c++11 -o mainC build/mainC.o build/MajorCharacter.o

build/mainC.o: mainC.cpp build/MajorCharacter.o
	g++ -std=c++11 -c mainC.cpp -o build/mainC.o

build/main.o: main.cpp control/Controller.h
	g++ -std=c++11 -c main.cpp -o build/main.o

build/Controller.o: control/Controller.cpp model/pc/Character.hpp model/pc/MajorCharacter.hpp model/npc/Follower.hpp view/mappa/Mappa.h view/View.h model/pc/Item.hpp model/pc/inventory.hpp
	g++ -std=c++11 -c control/Controller.cpp -o build/Controller.o
	
build/MajorCharacter.o: model/pc/MajorCharacter.cpp model/pc/MajorCharacter.hpp
	g++ -std=c++11 -c model/pc/MajorCharacter.cpp -o build/MajorCharacter.o
	
build/Follower.o: model/npc/Follower.hpp
	g++ -std=c++11 -c model/npc/Follower.cpp -o build/Follower.o
	
build/ability.o: model/pc/ability.h
	g++ -std=c++11 -c model/pc/ability.cpp -o build/ability.o

build/Character.o: model/pc/Character.cpp model/pc/ability.h
	g++ -std=c++11 -c model/pc/Character.cpp -o build/Character.o

build/Mappa.o: view/mappa/Mappa.h build/Stanza.o
	g++ -std=c++11 -c view/mappa/Mappa.cpp -o build/Mappa.o

build/View.o: view/mappa/Mappa.h model/pc/Character.hpp view/View.h
	g++ -std=c++11 -c view/View.cpp -o build/View.o

build/Stanza.o: view/mappa/Stanza.h
	g++ -std=c++11 -c view/mappa/Stanza.cpp -o build/Stanza.o

build/Item.o: model/pc/Item.hpp model/pc/Item.cpp
	g++ -std=c++11 -c model/pc/Item.cpp -o build/Item.o

build/inventory.o: model/pc/inventory.hpp model/pc/inventory.cpp
	g++ -std=c++11 -c model/pc/inventory.cpp -o build/inventory.o

clean:
	rm -rf main build/*.o
