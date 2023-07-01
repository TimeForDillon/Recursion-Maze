/************************************************************
 * AUTHOR:      David Dang, Dillon Welsh
 * ASSIGNMENT:  Lab 14 - Recursion Maze
 * CLASS:       CS_003A_71206
 * SECTION:     MTWR 7:00AM-9:05AM
 * DUE DATE:    10/27/2020
 ************************************************************/

/**********************************************************
 * Recursion Maze
 *_________________________________________________________
 * This program randomly generates a maze using recursion.
 *_________________________________________________________
 * INPUT:
 *   Does not accept input from user
 *
 * OUTPUT:
 *   Prints the randomly generated maze to the screen
 ***********************************************************/

#include <iostream>
#include <fcntl.h>
#include <io.h>
#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <vector>

using namespace std;

// GLOBAL CONSTANTS         //DATA TABLE
const int ROW_SIZE = 11;    //CALC : number of rows in maze
const int COLUMN_SIZE = 26; //CALC : number of columns in array


/**************************************************************************
 * mazeGenerator
 *  This function will randomly generate a maze in the form of an array
 *  - returns nothing
 *************************************************************************/
void mazeGenerator(char maze[][COLUMN_SIZE], // IN: array that holds the
                                             //     maze
                   int rows,                 // CALC: row being processed
                   int columns);             // CALC: column being
                                             //       processed


/**************************************************************************
 * display
 * This function will display the array that contains the maze
 * - returns nothing
 *************************************************************************/
void display(char maze[][COLUMN_SIZE]); // IN: array that holds the
                                        //     maze

int main()
{
    // variables                        //Data Table
    char maze [ROW_SIZE][COLUMN_SIZE];  // CALC : array to hold the maze
    int entrance;                       // CALC : holds the entrance to the
                                        //        maze
    int exit;                           // CALC : holds the exit to the
                                        //        maze

    // CALC : fills the maze with walls
    for (unsigned i = 0; i < ROW_SIZE; i++)
    {
        for (unsigned j = 0; j < COLUMN_SIZE; j++)
        {
            if (j % 2 == 0)
            {
                //maze[i][j] = '\u25A0';
                maze[i][j] = '*';
            }
            else
            {
                maze[i][j] = ' ';
            }
        }
    }

    // CALC : seed the rand generator
    srand(time(NULL));

    // CALC : ensures the entrance is not in the corner or in the gap
    //        between the asterisks
    do
    {
        entrance = rand() % COLUMN_SIZE;
        //cout << entrance << endl;
    }while(entrance%4==0 || entrance%2!=0);

    //entrance and exit was calculated by Dillon. Since the
    //column size is 26 (13x2) we are placing the walls on
    //all of the odd even numbers instead of just excluding the odd numbers
    //this corrected the doubling of walls on certain even indicies.
    //entrance = 4;

    // CALC : constructs entrance to the maze
    maze[0][entrance] = ' ';
    maze[1][entrance] = ' ';


    // CALC : calls mazeGenerator to generate the maze
    mazeGenerator(maze, 1, entrance);

    // CALC : generate a random exit to the maze
    //exit = rand() % COLUMN_SIZE;
    exit = 10;

    // CALC : ensures the exit is not in the corner or in the gap
    //        between the asterisks
//    while (exit == 0 || exit == COLUMN_SIZE - 2 || exit % 2 != 0)
//    {
//        exit = rand() % COLUMN_SIZE;
//    }

    do
    {
        exit = rand() % COLUMN_SIZE;
        //cout << exit << endl;
    }while(exit%4==0 || exit%2!=0);

    // CALC : constructs exit to the maze
    maze[9][exit] = ' ';
    maze[10][exit] = ' ';

    // OUTPUT : calls display to display maze
    display(maze);

    return 0;
}

/**************************************************************************
 *
 * FUNCTION mazeGenerator
 *_________________________________________________________
 * This function randomly generates the maze
 *   - returns nothing but updates the array containg the
 *     maze
 *_________________________________________________________
 * PRE-CONDITIONS:
 *  The following need previously defined values:
 *    maze: the randomly generated maze
 *    rows: row being processed
 *    columns: column being processed
 *
 * POST-CONDITIONS:
 *    returns nothing but updates the array containg the
 *     maze
 *************************************************************************/
void mazeGenerator(char maze[][COLUMN_SIZE], // IN: array that holds the
                                             //     maze
                   int rows,    // CALC: row being processed
                   int columns) // CALC: column being processed
{
    // variables                        Data Table
    vector <int> directions{0, 1, 2, 3}; // CALC : vector filled with
                                         //        possible directions
    int random;                          // CALC : stores position of
                                         //        random direction in
                                         //        directions vector
    int direction;                       // CALC : stores random direction

    // CALC : function uses a do while loop to build the maze. It builds in
    //        a random direction until it is not possible and leaves the
    //        function recursively
    do
    {
        // CALC : generates random direction for the maze to build towards
        //        and then deletes the direction from the vector
        random = rand() % directions.size();
        direction = directions.at(random);

        for (unsigned i = 0; i < directions.size(); i++)
        {
            if (directions[i] == direction)
            {
                directions.erase(directions.begin() + i);
            }
        }


        // CALC : builds the maze downwards
        if (direction == 0 && maze[rows + 1][columns] != ' ' &&
                maze[rows + 2][columns] != ' ' && rows + 2 < ROW_SIZE - 1)
        {
            maze[rows + 1][columns] = ' ';
            maze[rows + 2][columns] = ' ';
            mazeGenerator(maze, rows + 2, columns);
        }

        // CALC : builds the maze to the right
        if (direction == 1 && maze[rows][columns + 2] != ' ' &&
                maze[rows][columns + 4] != ' ' && columns + 4 < COLUMN_SIZE - 2)
        {
            maze[rows][columns + 2] = ' ';
            maze[rows][columns + 4] = ' ';
            mazeGenerator(maze, rows, columns + 4);
        }

        // CALC : builds the maze upwards
        if (direction == 2 && maze[rows - 1][columns] != ' '
                && maze[rows - 2][columns] != ' ' && rows - 2 > 0)
        {
            maze[rows - 1][columns] = ' ';
            maze[rows - 2][columns] = ' ';
            mazeGenerator(maze, rows - 2, columns);
        }

        // CALC : builds the maze to the left
        if (direction == 3 && maze[rows][columns - 2] != ' '
                && maze[rows][columns - 4] != ' ' && columns - 4 > 0)
        {
              maze[rows][columns - 2] = ' ';
              maze[rows][columns - 4] = ' ';
              mazeGenerator(maze, rows, columns - 4);
        }

    }
    while (directions.size() > 0);
}


/**************************************************************************
 * FUNCTION display
 *_________________________________________________________
 * This function displays the generated maze
 *   - returns nothing
 *_________________________________________________________
 * PRE-CONDITIONS:
 *  The following need previously defined values:
 *    maze: the randomly generated maze
 *
 * POST-CONDITIONS:
 *    returns nothing but displays array that holds
 *    randomly generated maze
 *************************************************************************/
void display(char maze[][COLUMN_SIZE]) // IN: array that holds the maze
{
    //allows output to accept 16 bit unicode instead of 8 bit ascii
    _setmode(_fileno(stdout), _O_U16TEXT);
    // OUTPUT : uses a for loop to display the maze
    for (unsigned i = 0; i < ROW_SIZE; i++)
    {
        for (unsigned j = 0; j < COLUMN_SIZE; j++)
        {
            //change all asterics to unicode block
            if(maze[i][j] == '*')
                wprintf(L"\u25A0");
            else wprintf(L"%c",maze[i][j]);
            if (j == COLUMN_SIZE - 1)
            {
                wprintf(L"\n");
            }
        }
    }
    wprintf(L"\n");
}
