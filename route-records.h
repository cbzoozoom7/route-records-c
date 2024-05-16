//route-records.h
//Christopher Bowman
//created 25 Oct 2023
#ifndef ROUTE_RECORDS_H
	#define ROUTE_RECORDS_H
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#define NUM_MONTHS 6
	#define LINE_LENGTH 45
	typedef struct STRUCT_ROUTERECORD {
		char origin[4];
		char destination[4];
		char airline[3];
		int passengers[NUM_MONTHS];
	} RouteRecord;
	typedef enum ENUM_SEARCHTYPE {ROUTE, ORIGIN, DESTINATION, AIRLINE} SearchType;
	RouteRecord *createRecords(FILE *);
	int fillRecords(RouteRecord *, FILE *);
	int findAirlineRoute(RouteRecord *, int, const char *, const char *, const char *, int);
	void searchRecords(RouteRecord *, int, const char *, const char *, SearchType);
	void printMenu();
#endif
