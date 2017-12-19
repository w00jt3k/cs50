#include <cs50.h>
#include <stdio.h>

int main(void) {
    // Declaring integer variable "h"
    int h;

    // Prompting user for height of the pyramid, where
    // it has to be positive number less than 23 (including)

    do {
        printf("Height: ");
        h = get_int();
    } while (h < 0 || h > 23);

    // Iterating over height value
    for (int i = 0; i < h; i++) {

        // Printing in row
        for (int j = 0, k = h + 1; j < k; j++) {

            if (j < (k - 2 - i)) {
                printf(" ");
            } else {
                printf("#");
            }
        }

        printf("\n");
    }
}

/* h = 4

xxx**

xx***

x****

*****

*/