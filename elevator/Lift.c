#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PASSENGERS 2

// Array to check if input provided from user is correct.
int lift(char currentFloor[3]) {
    const char* array_of_strings[9] = {
        "B3",
        "B2",
        "B1",
        "G",
        "1",
        "2",
        "3",
        "4",
        "5",
    };

    // Initiate variables here.
    char input[3];
    char destinationFloor[3];
    char newFloor[3];
    
    // Giving information about state right now and options
    printf("\nYour current floor is: %s", currentFloor);
    printf("\n\nYou can travel to these floors:\n  5\n 3 4\n 1 2\n G B1\nB2 B3\n\n");
    scanf("%2s", destinationFloor);

    // Validate that floor exists.
    for (int i = 0; i < 9; i++) {
        if (strcmp(array_of_strings[i], destinationFloor) == 0) {
            printf("You are passing all floors to your destination, is there another passenger?\n");
            scanf("%s", input);

            if (strcmp(input, "yes") == 0) {
                printf("What floor do they need to reach?\n");
                scanf("%s", newFloor);

                int found = 0;
                for (int i = 0; i < 9; i++) {
                    if (strcmp(array_of_strings[i], newFloor) == 0) {
                        found = 1;
                        break;
                    }
                }

                if (!found) {
                    printf("\nThere is no such floor, you arrived at %s", destinationFloor);
                    return lift(destinationFloor);
                } else {
                    printf("is there another passenger?\n");
                    scanf("%s", input);

                    if (strcmp(input, "yes") == 0) {
                        printf("\nYou can have a maximum of %d passengers in the lift.", MAX_PASSENGERS);
                        printf("\nYou skip passenger");
                    } else {
                        printf("\nYour current floor is: %s", destinationFloor);
                        printf("\nYou went to the second passenger's destination: %s", newFloor);
                        return lift(newFloor);
                    }

                    printf("\nYour current floor is: %s", destinationFloor);
                    printf("\nYou went to the second passenger's destination: %s", newFloor);
                    return lift(newFloor);
                }
            } else if (strcmp(input, "no") == 0) {
                return lift(destinationFloor);
            }
        }
    }

    printf("\nPlease provide correct input\n");
    return lift(currentFloor);
}

int main(void) {
    int result = lift("G");
    return result;
}
