all: main

main: main.o character.o aiutante.o majorCharacter.o
	g++ -std=c++11 -o main main.o character.o aiutante.o majorCharacter.o

main.o: main.cpp character.cpp aiutante.cpp majorCharacter.cpp
	g++ -std=c++11 -c main.cpp

majorCharacter.o: majorCharacter.h character.cpp aiutante.cpp
	g++ -std=c++11 -c majorCharacter.cpp

aiutante.o: aiutante.h character.cpp
	g++ -std=c++11 -c aiutante.cpp

character.o: character.cpp
	g++ -std=c++11 -c character.cpp

clean:
	rm -rf main *.o
