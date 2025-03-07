all: analyse


analyse: lexer.o symbole.o etat.o automate.o main.o
	g++ -o analyse lexer.o symbole.o etat.o automate.o main.o

lexer.o: lexer.cpp lexer.h
	g++ -o lexer.o -c lexer.cpp -Wall

symbole.o: symbole.cpp symbole.h
	g++ -o symbole.o -c symbole.cpp -Wall

etat.o: etat.cpp etat.h
	g++ -o etat.o -c etat.cpp -Wall

automate.o: automate.cpp automate.h
	g++ -o automate.o -c automate.cpp -Wall

main.o: main.cpp symbole.h lexer.h etat.h
	g++ -o main.o -c main.cpp -Wall

clean:
	rm -rf *.o
	rm -rf analyse
