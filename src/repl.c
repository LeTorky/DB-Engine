#include <conio.h> 
#include <stdlib.h>
#include <stdio.h>

// Function to move index left or right, depending on user input.
void move_current_index(int left_or_right, int* current_index, int last_index);

// Function to insert/replace character into character array.
void insert_or_replace_character(char user_input, char* char_array, int* current_index, int* last_index);

// Function to allocate new memory for new character inputs.
void add_to_char_array(int add, char user_input, char** char_array, int last_index);

// Interface to Database (REPL).
void main(){
    // Variables
    char* user_entry = (char*)malloc(sizeof(char));
    *user_entry = '\0';
    int toggle = 1;
    int current_index = 0;
    int last_index = -1;

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

                    // Left arrow key case.
                    case 75:
                        move_current_index(0, &current_index, last_index);
                        break;

                    // Right arrow key case.
                    case 77:
                        move_current_index(1, &current_index, last_index);
                        break;
                }
                break;

            // Enter key case.
            case 13:
                printf("\n %s", user_entry);

            // Actual input characters.
            default:
                // Move cursor, print and save character.
                insert_or_replace_character(scanned_char, user_entry, &current_index, &last_index);
                printf("%c", scanned_char);
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
            *current_index += 1;
        }
    }
    // Move left
    // Decrement Index and move cursor to the left.
    else if(*current_index > 0){
        --*current_index;
    }
}

void insert_or_replace_character(char user_input, char* char_array, int* current_index, int* last_index){
    // Move index if a character was inserted.
    if(*current_index > *last_index){
        ++*last_index;
        move_current_index(1, current_index, *last_index);
        add_to_char_array(1, user_input, &char_array, *last_index);
    }
    else{
        // Replaces character in array.
        char_array[*current_index] = user_input;
    }
}

void add_to_char_array(int add, char user_input, char** char_array, int last_index){
    if(add){
        // Allocating a new array with the new size. (+1)
        char* new_array = (char*)malloc((last_index+1)*sizeof(char));
        for(int i=0; i<last_index; i++){
            new_array[i] = (*char_array)[i];
        }
        new_array[last_index] = user_input;
        new_array[last_index+1] = '\0';
        free(*char_array);
        *char_array = new_array;
    }
    else{
        // Removing last character.

    }
}