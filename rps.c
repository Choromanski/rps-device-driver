//Brian Choromanski
//CS449 Project 4
//Lecture Section 19730 (Tu/Th 11:00-12:15)
//Recitation Section 20024 (Tu 3:00-3:50)

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>

void play();

int compScore;          //How many times the computer has won
int playerScore;        //How many times the player has won
char input[10];         //Array for capturing user input
int main(){
    printf("Welcome to Rock, Paper, Scissors\n\nWould you like to play? ");
    scanf("%s", input);                             //Gets user input to see if they want to play
    while(strcmp(input, "yes")==0){                 //If the user wants to play/play again 
        compScore = 0;                              //Sets the times the computer has won to 0
        playerScore = 0;                            //Sets the times the player has won to 0
        while(compScore < 3 && playerScore < 3){    //Loops while both the computer and player have not yet won 3 rounds
            play();                                 //Plays a round of RPS
        }
        printf("\nThank you for playing. Would you like to play again? ");
        scanf("%s", input);                         //Gets user input to see if they want to play again
    }
    return 0;                                       //Terminates the program
}

void play(){
    printf("\nWhat is your choice? ");
    scanf("%s", input);                                                         //Gets the users input either "rock", "paper", or "scissors"
    unsigned char value;
    int file = open("/dev/rps", O_RDONLY);
    read(file, &value, sizeof(unsigned char));                                  //Generates computers choice: 1 for rock, 2 for paper, or 3 for scissors
    if(value == 1){                                                             //Computers choice is rock
        if(strcmp(input, "rock") == 0){                                         //Users choice is rock
            printf("The computer chooses rock. You tie this game!\n");
        }else if(strcmp(input, "paper") == 0){                                  //Users choice is paper
            printf("The computer chooses rock. You win this game!\n");
            playerScore++;                                                      //Increments the players wins by 1
        }else if(strcmp(input, "scissors") == 0){                               //Users choice is scissors
            printf("The computer chooses rock. You lose this game!\n");
            compScore++;                                                        //Increments the computers wins by 1
        }else{                                                                  //Users choice is invalid
            printf("Invalid input select \"rock\", \"paper\", or \"scissors\"\n");
        }
    }else if(value == 2){                                                       //Computers choice is paper
        if(strcmp(input, "rock")==0){                                           //Users choice is rock
            printf("The computer chooses paper. You lose this game!\n");
            compScore++;                                                        //Increments the computers wins by 1
        }else if(strcmp(input, "paper") == 0){                                  //Users choice is paper
            printf("The computer chooses paper. You tie this game!\n");
        }else if(strcmp(input, "scissors") == 0){                               //Users choice is scissors
            printf("The computer chooses paper. You win this game!\n");
            playerScore++;                                                      //Increments the players wins by 1
        }else{                                                                  //Users choice is invalid
            printf("Invalid input select \"rock\", \"paper\", or \"scissors\"\n");
        }
    }else if(value == 3){                                                       //Computers choice is scissors
        if(strcmp(input, "rock") == 0){                                         //Users choice is rock
            printf("The computer chooses scissors. You win this game!\n");
            playerScore++;                                                      //Increments the players wins by 1
        }else if(strcmp(input, "paper") == 0){                                  //Users choice is paper
            printf("The computer chooses scissors. You lose this game!\n");
            compScore++;                                                        //Increments the computers wins by 1
        }else if(strcmp(input, "scissors") == 0){                               //Users choice is scissors
            printf("The computer chooses scissors. You tie this game!\n");
        }else{                                                                  //Users choice is invalid
            printf("Invalid input select \"rock\", \"paper\", or \"scissors\"\n");
        }
    }
    printf("\nThe score is now you: %i computer: %i", playerScore, compScore);  //Prints out the score

}
