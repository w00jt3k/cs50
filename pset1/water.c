#include <cs50.h>
#include <stdio.h>

int main(void) {
    // Declaring integet variable "n"
    int n;

    // Prompting user for shower time in minutes
    printf("Minutes: ");

    // Check if number of minutes is equal to 0 or more, if not - propmpt again
    do {
        n = get_int();
    } while (n < 0);

    printf("Bottles: %i\n", n * 12);
}