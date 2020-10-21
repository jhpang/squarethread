squared_threaded: squared_threaded.c
	gcc -o squared_threaded squared_threaded.c -lpthread

clean: clean_all

clean_all:
	rm -f squared_threaded

