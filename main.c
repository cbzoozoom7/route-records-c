#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "route-records.h"
#define MAX_ARG_LENGTH 100

int main( int argc, char *argv[] )
{
    /* 1. Declare variables here */
    
    /* 2. Check command line arguments here. If a command line argument (for the file name) is missing, print out the following: */
	if (argc > 1) {
		char fileName[MAX_ARG_LENGTH];
		strcpy(fileName, argv[1]);
    /* 3. Attempt to open the file. Print out Opening <filename>... before you call fopen(). */
		printf("Opening %s...\n", fileName);
		FILE *fileIn = fopen(fileName, "r");
    /* 4. Check to see if the file opens. If it does not open, print out ERROR: Could not open file and end the program. */
		if (fileIn != NULL) {
    /* 5. Do the following to load the records into an array of RouteRecords
    	
    		5.1 Call createRecords(), which will read through the file once to find the total number of lines/records in the file. Use this count, to dynamically allocate memory for an array of RouteRecords. It returns a pointer to that array. Don't forget to rewind the file pointer.

    		5.2 Call fillRecords() to go through the CSV file again to fill in the values. It will then return the actual number of items the array has. Recall that not all records in the original CSV file will be entered into the array. Print the number of unique routes operated by different airlines: Unique routes operated by airlines: ???
    		
    		5.3 Close the the file.
    */
			RouteRecord *routes = createRecords(fileIn);
			int numRoutes = fillRecords(routes, fileIn);
			printf("Unique routes operated by airlines: %d\n", numRoutes);
			fclose(fileIn);
    /* 6. Create an infinite loop that will do the following:
    
    		6.1 Call printMenu()
    		
    		6.2 Ask the user to input a value for the menu
    		
    		6.3 Handle the case in which a non-integer value is entered
    		
    		6.4 Create a switch/case statement to handle all the menu options
    		
	    		6.4.1 Each option requires the user to enter a search key
	    		
	    		6.4.2 Quit needs to free the array
    
    */
			char menu = 1;
			while (menu) {
				printMenu();
				char selection[5];
				scanf("%s", selection);
				SearchType st;
				char runSearch = 0;
				char key1[4];
				char key2[4] = {'\0'};
				if (strcmp(selection, "1") == 0) { //search by route
					st = ROUTE;
					printf("Origin airport code: ");
					scanf("%s", key1);
					printf("Destination airport code: ");
					scanf("%s", key2);
					runSearch = 1;
				} else if (strcmp(selection, "2") == 0) { //search by origin
					st = ORIGIN;
					printf("Origin airport code: ");
					scanf("%s", key1);
					runSearch = 1;
				} else if (strcmp(selection, "3") == 0) { //search by destination
					st = DESTINATION;
					printf("Destination airport code: ");
					scanf("%s", key1);
					runSearch = 1;
				} else if (strcmp(selection, "4") == 0) { //search by airline
					st = AIRLINE;
					printf("Airline code: ");
					scanf("%s", key1);
					runSearch = 1;
				} else if (strcmp(selection, "5") == 0) { //quit
					menu = 0;
					free(routes);
				} else {
					printf("Please enter a number 1–5. 5 to quit.\n");
				}
				if (runSearch) {
					searchRecords(routes, numRoutes, key1, key2, st);
				}
			}
		} else {
			printf("ERROR: Could not open file\n");
		}
	} else {
		printf("ERROR: Missing file name\n");
	}
    return 0;
}
