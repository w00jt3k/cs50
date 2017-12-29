#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char switchLetters(char letter, int key);

int main(int argc, string argv[]) {

    // Immediately exit program if passed incorrect number of arguments
    if (argc != 2) {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    // Declare needed variables
    int k;
    string plaintext;

    // Store 2nd argument as 'key' value
    k = atoi(argv[1]);

    // Prompt user for plaintext
    printf("plaintext: ");
    plaintext = get_string();

    printf("ciphertext: ");

    // Iterate over plaintext's letters
    for (int i = 0, n = strlen(plaintext); i < n; i++) {
        printf("%c", switchLetters(plaintext[i], k));
    }

    printf("\n");

    return 0;
}

// Letter switching function
char switchLetters(char letter, int key) {

    // Check if passed letter is indeed letter,
    // otherwise return passed symbol
    if (!isalpha(letter)) {
        return letter;
    }

    // Change ASCII index for alphabewtical index
    int alphIndex = isupper(letter) ? 65 : 97;

    // Calculate Caesar's alhorithm
    int c = (((int) letter - alphIndex) + key) % 26;

    // Return ASCII value of switched letter
    return isupper(letter) ? c + 65 : c + 97;
}