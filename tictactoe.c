#include <stdio.h>
#include <math.h>
#include <unistd.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

#define WIDTH 3
#define HEIGHT 3

/* function declarations */
void ClearTable(unsigned char table[WIDTH][HEIGHT]);

void PlacePointO(unsigned int x, unsigned int y, unsigned char table[WIDTH][HEIGHT]);

void PlacePointX(unsigned int x, unsigned int y, unsigned char table[WIDTH][HEIGHT]);

void ShowMainScreen();

void DrawTable(unsigned char table[WIDTH][HEIGHT]);

int CanPlaceAtPoint(unsigned int x, unsigned int y, unsigned char table[WIDTH][HEIGHT]);

int CheckForWin(unsigned char table[WIDTH][HEIGHT]);

/* function definitions */
void PlacePointO(unsigned int x, unsigned int y, unsigned char table[WIDTH][HEIGHT]){
    table[HEIGHT - y][x - 1] = 'O'; 
}

void PlacePointX(unsigned int x, unsigned int y, unsigned char table[WIDTH][HEIGHT]){
    table[HEIGHT - y][x - 1] = 'X'; 
}

void ShowMainScreen(){
    clrscr();
    printf("-------------------------------------- \n      Welcome to Tic Tac Toe \n \n \n         Version 0.001 \n       2024 Kyle Sullivan \n \n --------------------------------------\n\n");
    sleep(2);
}

void DrawTable(unsigned char table[WIDTH][HEIGHT]){
    printf("\n3  %c | %c | %c \n", table[0][0], table[0][1], table[0][2]);
    printf("  ---+---+---\n");
    printf("2  %c | %c | %c \n", table[1][0], table[1][1], table[1][2]);
    printf("  ---+---+---\n");
    printf("1  %c | %c | %c \n", table[2][0], table[2][1], table[2][2]);
    printf("   1   2   3 \n\n");
}

int CanPlaceAtPoint(unsigned int x, unsigned int y, unsigned char table[WIDTH][HEIGHT]){
    if(table[HEIGHT - y][x - 1] == ' '){
        return 0;
    } else {
        return 1;
    }
}

int CheckForWin(unsigned char table[WIDTH][HEIGHT]){
    int i;
    unsigned char Winner;

    /* check columns */
    for(i = 0; i<WIDTH; i++){
        if((table[0][i] == table[1][i] && table[1][i] == table[2][i]) && table[0][i] != ' '){
            /* sets winner to char on matching coordinates*/
            Winner = table[0][i];
            break;
        } else {
            continue;
        }
    }

    /* check rows */
    for(i = 0; i < HEIGHT; i++){
        if((table[i][0] == table[i][1] && table[i][1] == table[i][2]) && table[i][1] != ' '){
            /* sets winner to char on matching coordinates*/
            Winner = table[i][0];
            break;
        } else{
            continue;
        }
    }

    

    if(((table[0][0] == table[1][1] && table[1][1] == table[2][2]) || (table[2][0] == table[1][1] && table[1][1] == table[0][2])) && table[1][1] != ' '){
        Winner = table[1][1];
    }
    
    if(Winner == 'O'){
        return 1;
    } else if(Winner == 'X'){
        return 2;
    } else {
        return 0;
    }
}

void ClearTable(unsigned char table[WIDTH][HEIGHT]){
    int i;
    int j;
    for(i = 0; i < WIDTH; i++){
        for(j = 0; j < HEIGHT; j++){
            table[i][j] = ' ';
        }
    }
}

/* main function */
int main(){
    /* create 3x3 array to represent tictactoe table */
    unsigned char table[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};

    int turnNum = 1;

    char userInput;

    /* alternate player turn */
    
    int playerTurn;

    /* input coordinates */
    int inputx;
    int inputy;

    ShowMainScreen();

    while(turnNum > 0){ /* set roundNum to 0 / break to end game */
        /* main game loop*/
        clrscr();
        DrawTable(table);

        /* printf("Checkforwin = %d", CheckForWin(table)); */

        if(CheckForWin(table) != 0){
            printf("\n   Player #%d Won!\n", CheckForWin(table));
            printf("Would you like to play again? (Y/N):");
            while(1){
                scanf(" %c", &userInput);
                if(userInput != 'Y' &&  userInput != 'N'){
                    printf("\n Invalid input. Try again: ");
                    continue;
                } else{
                    break;
                }
            }
            if(userInput == 'Y'){
                turnNum = 1;
                ClearTable(table);
                continue;
            } else {
                break;
            }
        }
        /* checks for tie */
        if(turnNum >= 9 && CheckForWin(table) == 0){
            printf("\n It's a tie! Would you like to play again? (Y/N):");
            while(1){
                scanf(" %c", &userInput);
                if(userInput != 'Y' && userInput != 'N'){
                    printf("\n Invalid input. Try again: ");
                    continue;
                } else { 
                    break;
                }
            }
            if(userInput == 'Y'){
                turnNum = 1;
                ClearTable(table);
                continue;
            } else {
                break;
            }
        }

        inputx = 0;
        inputy = 0;

        /* assign player turn */
        if(turnNum % 2 == 0){
            playerTurn = 2;
        } else {
            playerTurn = 1;
        }

        printf("    Turn %d\n", turnNum);
        printf("  Player #%d's Turn\n\n", playerTurn);
        
        /* checks if coordinates are valid*/
        while(1){
            /* take x input and check validity*/
            while(1){
                printf("Player #%d Enter Coordinates X: \n", playerTurn);
                scanf("%d", &inputx);
                if(inputx > 3 || inputx < 1){
                    printf("Invalid input, try again.\n");
                    continue;
                } else {
                    break;
                }
            }
            /* take y input and check validity */
            while(1){
                printf("Player #%d Enter Coordinates Y: \n", playerTurn);
                scanf("%d", &inputy);
                if(inputy > 3 || inputy < 1){
                    printf("Invalid input, try again.\n");
                    continue;
                } else {
                    break;
                }
            }
            if(CanPlaceAtPoint(inputx,inputy,table) == 1){
                printf("\n point already occupied. try again. \n");
                continue;
            }
            break;
        }

        /* place points */
        if(playerTurn == 1){
            PlacePointO(inputx,inputy,table);
        } else {
            PlacePointX(inputx,inputy,table);
        }
        
        /*begin next turn*/
        turnNum++;
    }
    return 0;
}