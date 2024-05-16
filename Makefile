project-2: main.o route-records.o
	gcc main.o route-records.o -lm -Wall -o project-2
main.o: main.c route-records.h
	gcc -c main.c -Wall
route-records.o: route-records.c route-records.h
	gcc -c route-records.c -Wall
