#include <cs50.h>
#include <stdio.h>

int main(void) {

    // Declare long long type variable "x"
    long long x, temp, tempx2;
    int sum, sumtemp, sumtempx2;


    // Prompt user for card number
    do {
        x = get_long_long("Number: ");
    } while (x < 0);

    // Multiply every other digit by 2,
    // starting with the number’s second-to-last digit,
    // and then add those products' digits together
    for (tempx2 = x / 10, sumtempx2 = 0; tempx2 > 0; tempx2 /= 100) {

        if ((tempx2 % 10) * 2 > 9) {
            sumtempx2 += 2 * (tempx2 % 10) / 10;
            sumtempx2 += 2 * (tempx2 % 10) % 10;
        } else {
            sumtempx2 += 2 * tempx2 % 10;
        }
    }

    // Add the sum to the sum of the digits that weren’t multiplied by 2
    for (temp = x, sumtemp = 0; temp > 0; temp /= 100) {
        sumtemp += temp % 10;
    }

    // Sum both subsums
    sum = sumtemp + sumtempx2;

    // If that sum last digit is 0, then card number is valid
    if (sum % 10 == 0) {
        if ((x >= 340000000000000 && x < 350000000000000) || (x >= 370000000000000 && x < 380000000000000)) {
            printf("AMEX\n");
        } else if (x >= 5100000000000000 && x < 5600000000000000) {
            printf("MASTERCARD\n");
        } else if ((x >= 4000000000000 && x < 5000000000000) || (x >= 4000000000000000 && x < 5000000000000000)) {
            printf("VISA\n");
        } else {
            printf("INVALID\n");
        }
    } else {
        printf("INVALID\n");
    }
}