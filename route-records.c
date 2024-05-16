//route-records.c
//Christopher Bowman
//Created Wed 25 Oct 2023
#include "route-records.h"
RouteRecord *createRecords(FILE *fileIn) {
	int recordCount = 0;
	char currentChar = getc(fileIn);
	while (currentChar != EOF) { //count lines
		if (currentChar == '\n') {
			recordCount++;
		}
		currentChar = getc(fileIn);
	}
	RouteRecord *recordArr = (RouteRecord *) malloc(recordCount * sizeof(RouteRecord));
	int i;
	for (i = 0; i < recordCount; i++) { //initialize the passenger counts in each record to 0
		int j;
		for (j = 0; j < NUM_MONTHS; j++) {
			recordArr[i].passengers[j] = 0;
		}
	}
	rewind(fileIn);
	return recordArr;
}
int fillRecords(RouteRecord *r, FILE *fileIn) {
	char currentLine[LINE_LENGTH];
	fgets(currentLine, LINE_LENGTH, fileIn); //skip labels on the first line
	int arrLength = 0; //number of records in array
	while (fgets(currentLine, LINE_LENGTH, fileIn)) { //get each line in the file
		int month;
		char origin[4];
		char destination[4];
		char airline[3];
		char category[LINE_LENGTH];
		int passengers;
		if (sscanf(currentLine, "%d,%[^,],%[^,],%[^,],%[^,],%d", &month, origin, destination, airline, category, &passengers) != 6) {
			printf("failed to import the following line: %s\n", currentLine);
		}
		int i = findAirlineRoute(r, arrLength, origin, destination, airline, 0); //get the index of the record for that flight, if it exists
		if (i == -1) { //if it doesn't exist, make a new record
			i = arrLength++;
			strcpy(r[i].origin, origin);
			strcpy(r[i].destination, destination);
			strcpy(r[i].airline, airline);
		}
		r[i].passengers[month - 1] = passengers;
	}
	return arrLength;
}
int findAirlineRoute(RouteRecord *r, int length, const char *origin, const char *destination, const char *airline, int currIdx) {
	if (currIdx > length) { //already searched the whole array & didn't find it
		currIdx = -1;
	} else if (!((strcmp(r[currIdx].origin, origin) == 0) && (strcmp(r[currIdx].destination, destination) == 0) && (strcmp(r[currIdx].airline, airline) == 0))) {
		currIdx = findAirlineRoute(r, length, origin, destination, airline, currIdx + 1);
	}
	return currIdx;
}
void searchRecords(RouteRecord *r, int length, const char *key1, const char *key2, SearchType st) {
	char isResult = 0;
	int resultCount = 0;
	int passengersByMonth[NUM_MONTHS];
	int i;
	for (i = 0; i < NUM_MONTHS; i++) {
		passengersByMonth[i] = 0;
	}
	int resultIndex;
	for (resultIndex = 0; resultIndex < length; resultIndex++) {
		switch (st) {
			case ROUTE:
				isResult = ((strcmp(r[resultIndex].origin, key1) == 0) && (strcmp(r[resultIndex].destination, key2) == 0));
			break;
			case ORIGIN:
				isResult = (strcmp(r[resultIndex].origin, key1) == 0);
			break;
			case DESTINATION:
				isResult = (strcmp(r[resultIndex].destination, key1) == 0);
			break;
			case AIRLINE:
				isResult = (strcmp(r[resultIndex].airline, key1) == 0);
			break;
		}
		if (isResult) {
			isResult = 0;
			resultCount++;
			printf("%s to %s on %s\n", r[resultIndex].origin, r[resultIndex].destination, r[resultIndex].airline);
			for (i = 0; i < NUM_MONTHS; i++) {
				passengersByMonth[i] += r[resultIndex].passengers[i];
			}
		}
	}
	int totalPassengers = 0;
	printf("%d results.\n", resultCount);
	for (i = 0; i < NUM_MONTHS; i++) {
		printf("total month %d passengers: %d\n", i + 1, passengersByMonth[i]);
		totalPassengers += passengersByMonth[i];
	}
	printf("total passengers: %d\n", totalPassengers);
	printf("average per month: %.1lf\n", (double) totalPassengers / NUM_MONTHS);
}
void printMenu() {
	printf("\n\n######### Airline Route Records Database MENU #########\n");
	printf("1. Search by Route\n");
	printf("2. Search by Origin Airport\n");
	printf("3. Search by Destination Airport\n");
	printf("4. Search by Airline\n");
	printf("5. Quit\n");
	printf("Enter your selection: ");
}
