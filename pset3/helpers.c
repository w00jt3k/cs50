/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <math.h>

#include "helpers.h"

bool binarySearch(int values[], int l, int r, int n);

bool isSorted(int values[], int n);

void bubbleSort(int values[], int n);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0) return false;

    return binarySearch(values, 0, n - 1, value);
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int iterations = n;

    while (!isSorted(values, n))
    {
        bubbleSort(values, iterations);
        iterations--;
    }
}

/**
 * Custom additional functions
 */
bool binarySearch(int values[], int l, int r, int n)
{
    if (r >= l)
    {
        int mid = (int) floor((l + r) / 2);

        if (values[mid] == n)
        {
            return true;
        }
        else if (values[mid] > n)
        {
            return binarySearch(values, l, mid - 1, n);
        }
        else if (values[mid] < n)
        {
            return binarySearch(values, mid + 1, r, n);
        }
    }

    return false;
}

bool isSorted(int values[], int n)
{
    if (n == 1) {
        return true;
    }

    for (int i = 0; i < n - 1; i++)
    {
        if (values[i] > values[i + 1]) {
            return false;
        }
    }

    return true;
}

void bubbleSort(int values[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int a = values[i],
            b = values[i + 1];

        if (a > b) {
            values[i] = b;
            values[i + 1] = a;
        }
    }
}