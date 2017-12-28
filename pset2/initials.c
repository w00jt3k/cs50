#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void) {

    // Declare variable and prompt user for name
    string name = get_string();

    // Make sure name is string
    if (name != NULL) {

        // Iterate over every letter and print initials
        for (int i = 0, n = strlen(name); i < n; i++) {

            // Print first letter
            if (i == 0) {
                printf("%c", toupper(name[0]));
            }

            // Print every part of name as uppercased letter
            if (name[i] == ' ') {
                printf("%c", toupper(name[i + 1]));
            }
        }

        printf("\n");
    }
}