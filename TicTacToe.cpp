#include <bits/stdc++.h>
using namespace std;

#define Computer 1
#define Human 2

#define SIDE 3

#define Computermove 'O'
#define Humanmove '1'

// Function declarations
// void showboard(char board[][SIDE]);
// void showInstructions();
// void initialise(char board[][SIDE]);
// bool rowCrossed(char board[][SIDE]);
// bool columnCrossed(char board[][SIDE]);
// bool diagonalCrossed(char board[][SIDE]);
// bool gameOver(char board[][SIDE]);
// int minimax(char board[][SIDE], int depth, bool isAI);
// int bestmove(char board[][SIDE], int moveindex);
// void playTicTacToe(int whose_turn);
// void declareWinner(int whose_turn);

void declareWinner(int whose_turn)
{
    if (whose_turn == Computer)
        printf("Computer has won the game! Better luck next time.\n");
    else
        printf("Congratulations! You have won the game!\n");
}

void showboard(char board[][SIDE])
{
    printf("\n\n");
    for (int i = 0; i < SIDE; i++)
    {
        printf("\t\t\t ");
        for (int j = 0; j < SIDE; j++)
        {
            printf(" %c ", board[i][j]);
            if (j < SIDE - 1)
                printf("|");
        }
        printf("\n");
        if (i < SIDE - 1)
        {
            printf("\t\t\t-----------\n");
        }
    }
    printf("\n\n");
}

void showInstructions()
{
    printf("\n Choose a cell numbered from 1 to 9 as below and play :\n\n");
    printf("\t\t\t 1 | 2 | 3 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 4 | 5 | 6 \n");
    printf("\t\t\t-----------\n");
    printf("\t\t\t 7 | 8 | 9 \n");
}

void initialise(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
            board[i][j] = '*';
    }
}

bool rowCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '*')
            return true;
    }
    return false;
}

bool columnCrossed(char board[][SIDE])
{
    for (int i = 0; i < SIDE; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != '*')
            return true;
    }
    return false;
}

bool diagonalCrossed(char board[][SIDE])
{
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][2] != '*')
        return true;

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '*')
        return true;

    return false;
}

bool gameOver(char board[][SIDE])
{
    return (rowCrossed(board) || columnCrossed(board) || diagonalCrossed(board));
}

int minimax(char board[][SIDE], int depth, bool isAI)
{
    int score = 0;
    int bestScore = 0;
    if (gameOver(board) == true)
    {
        if (isAI == true)
            return -10;
        if (isAI == false)
            return +10;
    }
    else
    {
        if (depth < 9)
        {
            if (isAI == true)
            {
                bestScore = -999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = Computermove;
                            score = minimax(board, depth + 1, false);
                            board[i][j] = '*';
                            if (score > bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else
            {
                bestScore = 999;
                for (int i = 0; i < SIDE; i++)
                {
                    for (int j = 0; j < SIDE; j++)
                    {
                        if (board[i][j] == '*')
                        {
                            board[i][j] = Humanmove;
                            score = minimax(board, depth + 1, true);
                            board[i][j] = '*';
                            if (score < bestScore)
                            {
                                bestScore = score;
                            }
                        }
                    }
                }
                return bestScore;
            }
        }
        else
        {
            return 0;
        }
    }
}

int bestmove(char board[][SIDE], int moveindex)
{
    int x = -1, y = -1;
    int score = 0, bestScore = -999;
    for (int i = 0; i < SIDE; i++)
    {
        for (int j = 0; j < SIDE; j++)
        {
            if (board[i][j] == '*')
            {
                board[i][j] = Computermove;
                score = minimax(board, moveindex + 1, false);
                board[i][j] = '*';
                if (score > bestScore)
                {
                    bestScore = score;
                    x = i;
                    y = j;
                }
            }
        }
    }
    return x * 3 + y;
}

void playTicTacToe(int whose_turn)
{
    char board[SIDE][SIDE];
    int moveindex = 0;
    int x = 0, y = 0;

    initialise(board);
    showInstructions();

    while (gameOver(board) == false && moveindex != SIDE * SIDE)
    {
        int n; // Cell_no.
        if (whose_turn == Computer)
        {
            n = bestmove(board, moveindex);
            x = n / SIDE;
            y = n % SIDE;
            board[x][y] = Computermove;
            printf("Computer has put a %c in cell %d\n\n", Computermove, n + 1);
            showboard(board);
            moveindex++;
            whose_turn = Human;
        }

        else if (whose_turn == Human)
        {
            printf("You can insert in the following positions : ");
            for (int i = 0; i < SIDE; i++)
            {
                for (int j = 0; j < SIDE; j++)
                {
                    if (board[i][j] == '*')
                    {
                        printf("%d", (i * 3 + j) + 1);
                    }
                }
            }
            printf("\n\nEnter the position = ");
            scanf("%d", &n);

            n--;
            x = n / SIDE;
            y = n % SIDE;

            if (board[x][y] == '*' && n < 9 && n >= 0)
            {
                board[x][y] = Humanmove;
                printf("\nHuman ahs put a %c in cell %d\n\n", Humanmove, n + 1);
                showboard(board);
                moveindex++;
                whose_turn = Computer;
            }

            else if (board[x][y] != '*' && n < 9 && n >= 0)
            {
                printf("\nPosition is occupied, select any one place from the available places : ");
            }
            else if (n < 0 || n > 8)
            {
                printf("Invalid position\n");
            }
        }
    }

    if (gameOver(board) == false && moveindex == SIDE * SIDE)
        printf("It's a draw\n");

    else
    {
        if (whose_turn == Computer)
            whose_turn = Human;
        else if (whose_turn == Human)
            whose_turn = Computer;

        declareWinner(whose_turn);
    }
}

int main()
{
    printf("\n*********************************************\n\n");
    printf("\t\t\t Tic-Tac-Toe\n");
    printf("\n*********************************************\n\n");

    char option = 'y';

    do
    {
        char choice;
        printf("Do you want to start first? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y')
        {
            playTicTacToe(Human);
        }
        else if (choice == 'n')
        {
            playTicTacToe(Computer);
        }
        else
        {
            printf("Invalid choice\n");
        }

        printf("\nDo you want to quit the game? (y/n): ");
        scanf(" %c", &option);

    } while (option == 'n');

    return (0);
}