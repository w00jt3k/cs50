/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// blank and selected postions
int blank_row, blank_column, selected_row, selected_column;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

// custom functions
void search(int tile);
bool movePossible(void);
void swapTiles(void);


int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
    // Amount of tiles needed (minus one, cos of one blank needed)
    int tilesAmount = d * d - 1;

    // Iterate over rows of array
    for (int rows = 0; rows < d; rows++) {

        // Iterate over columns of current row
        for (int cols = 0; cols < d; cols++) {
            board[rows][cols] = tilesAmount;
            tilesAmount--;
        }
    }

    // If array has an odd number of tiles, tiles '1' and '2'need to be swapped
    if ((d * d - 1) % 2 != 0) {

        int temp = board[d - 1][d - 2];
        board[d - 1][d - 3] = temp;
        board[d - 1][d - 2] = 2;
    }

    blank_row = d - 1;
    blank_column = d - 1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // Iterate over rows of array
    for (int rows = 0; rows < d; rows++) {

        // Iterate over columns of current row
        for (int cols = 0; cols < d; cols++) {

            int currentTile = board[rows][cols];
            // Print number of tile
            // or underscore if tile is blank
            if (currentTile == 0) {
                printf(" _ ");
            } else {
                printf("%2i ", currentTile);
            }
        }

        // Print new line after row end
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */
bool move(int tile)
{
    // Check if tile exists
    if (tile > d * d - 1 || tile < 1) {
        return false;
    }

    // Search tile in board
    search(tile);

    if (movePossible()) {
        swapTiles();
        return true;
    }

    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // Amount of tiles needed (minus one, cos of one blank needed)
    int tilesAscending = 1;
    int max = d - 1;

    // Find board index of passed tile
    for (int rows = 0; rows < d; rows++) {

        for (int columns = 0; columns < d; columns++) {
            int currentTile = board[rows][columns];

            if (currentTile == tilesAscending) {
                tilesAscending++;
            }
        }
    }

    if (board[max][max] == 0 && tilesAscending == d * d) {
        return true;
    } else {
        return false;
    }
}

/**
 * Custom functions definitions.
 */
void search(int tile) {

    // Find board index of passed tile
    for (int rows = 0; rows < d; rows++) {

        for (int columns = 0; columns < d; columns++) {

            if (board[rows][columns] == tile) {
                selected_row = rows;
                selected_column = columns;
            }
        }
    }
}

bool movePossible(void) {

    // Check if passed tile is adjecent to '0' tile from:
    // top
    if (selected_row > 0 && board[selected_row - 1][selected_column] == 0) {
        return true;
    }

    // right
    if ((selected_column < d - 1) && board[selected_row][selected_column + 1] == 0) {
        return true;
    }

    // down
    if ((selected_row < d - 1) && board[selected_row + 1][selected_column] == 0) {
        return true;
    }

    // left
    if (selected_column > 0 && board[selected_row][selected_column - 1] == 0) {
        return true;
    }

    return false;
}

void swapTiles(void) {

    int tileValue = board[selected_row][selected_column];

    board[selected_row][selected_column] = board[blank_row][blank_column];
    board[blank_row][blank_column] = tileValue;

    blank_row = selected_row;
    blank_column = selected_column;
}
