#include <conio.h> 
#include <stdlib.h>
#include <stdio.h>

// Function to move index left or right, depending on user input.
void move_current_index(int left_or_right, int* current_index, int last_index);

// Function to insert/replace character into character array.
void insert_or_replace_character(char user_input, char* char_array, int* current_index, int* last_index);

// Interface to Database (REPL).
void main(){
    // Variables
    char* user_entry;
    int toggle = 1;
    int current_index = 0;
    int last_index = 0;

    // Conditional loop to take input from user until exit is written.
    char scanned_char;
    printf("%s \n", "Write a query or type -help.");
    do{
        scanned_char = getch();
        switch(scanned_char){

            // Extra key characters case.
            case 0:
                scanned_char = getch();
                switch(scanned_char){

                    // Left arrow case.
                    case 75:
                        move_current_index(0, &current_index, last_index);
                        break;

                    // Right arrow case.
                    case 77:
                        move_current_index(1, &current_index, last_index);
                        break;
                }
                break;

            // Enter character case.
            case 13:
                printf("%s", user_entry);

            // Actual input characters.
            default:
                // Move cursor, print and save character.
                printf("%c", scanned_char);
                insert_or_replace_character(scanned_char, &user_entry, &current_index, &last_index);
                break;
        }
    }
    // Continue until toggle is turned.
    while(toggle);
}

void move_current_index(int left_or_right, int* current_index, int last_index){
    // Move right
    if (left_or_right){
        // Increment Index and move cursor to the right.
        if(*current_index <= last_index){
            ++*current_index;
        }
    }
    // Move left
    // Decrement Index and move cursor to the left.
    if(*current_index > 0){
        --*current_index;
    }
}

void insert_or_replace_character(char user_input, char* char_array, int* current_index, int* last_index){
    // Add character to character array.
    char_array[*current_index] = user_input;
    // Move index if a character was inserted.
    if(*current_index > *last_index){
        ++*last_index;
        move_current_index(1, current_index, *last_index);
    }
}