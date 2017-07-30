all: build.sh addlevel.sh animals.txt cities.txt Hangman.c Select.h words.txt 
	sh ./build.sh
	gcc Hangman.c -o Hangman

install: Hangman
	cp Hangman /usr/local/bin
	chmod +x /usr/local/bin/Hangman
	rm Hangman
clean:
	rm /usr/local/bin/Hangman build.sh addlevel.sh animals.txt cities.txt Hangman.c Select.h words.txt Makefile .max.txt
