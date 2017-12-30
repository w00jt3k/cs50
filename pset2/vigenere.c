#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

bool isAlphaString(string arg);

void applyVigenere(string plaintext, string key);

int alphIndex(char letter);

int main(int argc, string argv[]) {

    // Immediately exit program if passed incorrect number of arguments
    // or argument doesn't contain only letters
    if (argc != 2) {
        printf("Usage: ./vigenere k\n");
        return 1;
    } else if (!isAlphaString(argv[1])) {
        printf("Usage: ./vigenere k - only letters\n");
        return 1;
    }

    // Declare needed variables
    string key = argv[1],
           plaintext;

    printf("plaintext: ");
    plaintext = get_string();
    printf("ciphertext: ");
    applyVigenere(plaintext, key);
    printf("\n");
    return 0;
}

// Function to test if passed argument contains only alphabetic letters
bool isAlphaString(string arg) {

    for (int i = 0, n = strlen(arg); i < n; i++) {
        if (!isalpha(arg[i])) {
            return false;
        }
    }

    return true;
}

// Use vigenere algorithm
void applyVigenere(string plaintext, string key) {

    // Declare letters index excluding special characters
    // and both lengths of plaintext and key
    int lettersIndex = 0,
        n = strlen(plaintext),
        keyLength = strlen(key);

    // Iterating over passed plaintext
    for (int i = 0; i < n; i++) {

        char l = plaintext[i];

        // If current character isn't letter, skip that char and continue
        if (!isalpha(l)) {
            printf("%c", l);
            continue;
        }

        // Determine, what letter of 'key' is processed
        int keyLetterIndex = lettersIndex % keyLength;

        lettersIndex++;

        // Calculate Vigenere
        int v = (alphIndex(plaintext[i]) + alphIndex(key[keyLetterIndex])) % 26;

        printf("%c", isupper(plaintext[i]) ? v + 65 : v + 97);
    }
}

// Function changing ASCII letter into alphabetical index
int alphIndex(char letter) {
    return isupper(letter) ? letter - 65 : letter - 97;
}