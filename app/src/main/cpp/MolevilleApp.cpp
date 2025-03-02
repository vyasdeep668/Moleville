/*
 * Copyright Kardium Inc. 2024.
 */

#include <stdio.h>
#include "MoleGuide.h"


int askForNumber(const char* prompt, int maximum) {
    while (1) {
        printf("%s (1-%d): ", prompt, maximum);
        int response;
        int fieldsRead = scanf("%d", &response);

        if (fieldsRead == 1 && response > 0 && response <= maximum) {
            return response;
        }
        printf("\tInvalid response.  Please enter a number between 1 and %d.\n", maximum);
        fflush(stdin);
    }
}


Location askForLocation(const char* prompt, bool showOptions) {
    if (showOptions) {
        printf("Locations:\n");
        for (int i = 0; i < NUM_LOCATIONS; i++) {
            printf("\t%c - %s\n", (char) (i + 'a'), Location_getName((Location) i));
        }
    }

    while (1) {
        printf("%s: ", prompt);
        char buffer[2];
        int fieldsRead = scanf("%1s", buffer);

        int locationIndex = buffer[0] - 'a';
        if (fieldsRead == 1 && locationIndex >= 0 && locationIndex < NUM_LOCATIONS) {
            return (Location) locationIndex;
        }
        printf("\tInvalid response.  Please enter a letter between a and %c.\n", 'a' + NUM_LOCATIONS - 1);
        fflush(stdin);
    }
}


Direction askForDirection(const char* prompt) {
    const char keys[] = {'n', 's', 'w', 'e'};

    printf("Directions:\n");
    for (int i = 0; i < NUM_DIRECTIONS; i++) {
        printf("\t%c - %s\n", keys[i], Direction_getName((Direction) i));
    }

    while (1) {
        printf("%s: ", prompt);
        char buffer[2];
        int fieldsRead = scanf("%1s", buffer);

        if (fieldsRead == 1) {
            for (int i = 0; i < NUM_DIRECTIONS; i++) {
                if (buffer[0] == keys[i]) {
                    return (Direction) i;
                }
            }
        }
        printf("\tInvalid response.  Please enter n|s|e|w.\n");
        fflush(stdin);
    }
}


void performRouteSearch() {
    printf("\n\nM O L E V I L L E  G U I D E\n\n");

    Location start = askForLocation("Starting location", true);
    Location finish = askForLocation("Destination", false);
    printf("Finding a route from %s to %s...\n", Location_getName(start), Location_getName(finish));

    Route_print(findRoute(start, finish));
}


void reportCaveIn() {
    printf("\n\nR E P O R T  C A V E - I N\n\n");

    Location nearby = askForLocation("Location nearby the cave-in", true);
    Direction direction = askForDirection("Direction towards the cave-in");

    int result = reportCaveIn(nearby, direction);
    if (result == 0) {
        printf("The tunnel %s of %s is now closed.\n", Direction_getName(direction), Location_getName(nearby));
    } else {
        printf("Invalid tunnel: %s of %s\n", Direction_getName(direction), Location_getName(nearby));
    }
}


void reportCaveInCleared() {
    printf("\n\nR E P O R T  C A V E - I N  C L E A R E D\n\n");

    Location nearby = askForLocation("Location nearby the repair", true);
    Direction direction = askForDirection("Direction towards the repair");

    int result = reportCaveInCleared(nearby, direction);
    if (result == 0) {
        printf("The tunnel %s of %s is now open.\n", Direction_getName(direction), Location_getName(nearby));
    } else {
        printf("Invalid tunnel: %s of %s\n", Direction_getName(direction), Location_getName(nearby));
    }
}


int main() {
    initGuide();

    while (1) {
        printf("\n\n\nW E L C O M E  T O  M O L E V I L L E !\n\n");

        printf("Menu:\n");
        printf("1 - Moleville Guide\n");
        printf("2 - Report a cave-in\n");
        printf("3 - Report cave-in cleared\n");
        printf("4 - Quit\n");
        int response = askForNumber("Please select an option", 4);

        switch (response) {
            case 1:
                performRouteSearch();
                break;

            case 2:
                reportCaveIn();
                break;

            case 3:
                reportCaveInCleared();
                break;

            case 4:
                printf("Goodbye.  Please visit again!\n\n");
                return 0;

            default:
                printf("*** Error: invalid option=%d\n", response);
                break;
        }
    }
}