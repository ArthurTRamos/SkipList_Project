all: skiplist.o item.o main.o
	gcc item_skip.o skiplist.o main.o -o main -std=c99 -Wall

skiplist.o:
	gcc -c skiplist.c -o skiplist.o

item.o:
	gcc -c item_skip.c -o item_skip.o
	 	 
main.o:
	gcc -c main.c -o main.o

run:
	./main
clear:
	rm skiplist.o
	rm main.o
	rm item_skip.o