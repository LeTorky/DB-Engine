#include <conio.h> 
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

// Function to move index left or right, depending on user input.
void move_current_index(int left_or_right, int* current_index, int last_index, COORD* x_y);

// Function to insert/replace character into character array.
void insert_or_replace_character(char user_input, char** char_array, int* current_index, int* last_index, COORD* x_y);

// Function to allocate new memory for new character inputs.
void add_to_char_array(char user_input, char** char_array, int last_index);

void move_cursor_left_right(int left_right, COORD* x_y);

// Interface to Database (REPL).
void main(){
    system("cls");
    // Variables
    char* user_entry = (char*)malloc(sizeof(char));
    int toggle = 1;
    int current_index = 0;
    int last_index = -1;
    int current_y = 0;
    int current_x = 0;
    COORD x_y = {.X = 0, .Y = 1};
    // Conditional loop to take input from user until exit is written.
    char scanned_char;
    printf("%s \n", "Write a query or type -help.");
    do{
        // Scan character from user.
        scanned_char = getch();
        switch(scanned_char){

            // Extra key characters case.
            case 0:
                scanned_char = getch();
                switch(scanned_char){

                    // Left arrow key case.
                    case 75:
                        move_current_index(0, &current_index, last_index, &x_y);
                        break;

                    // Right arrow key case.
                    case 77:
                        move_current_index(1, &current_index, last_index, &x_y);
                        break;
                }
                break;

            // Esc key case.
            case 27:
                toggle = 0;
                printf("\n Exited successfully!");
                break;

            // Enter key case.
            case 13:
                // Process Statement.
                break;

            // Actual input characters.
            default:
                // Move cursor, print and save character.
                insert_or_replace_character(scanned_char, &user_entry, &current_index, &last_index, &x_y);
                printf("%c", scanned_char);
                break;
        }
    }
    // Continue until toggle is turned.
    while(toggle);
}

void move_current_index(int left_or_right, int* current_index, int last_index, COORD* x_y){
    // Move right
    if (left_or_right){
        // Increment Index and move cursor to the right.
        if(*current_index <= last_index){
            *current_index += 1;
            move_cursor_left_right(1, x_y);
        }
    }
    // Move left
    // Decrement Index and move cursor to the left.
    else if(*current_index > 0){
        --*current_index;
        move_cursor_left_right(0, x_y);
    }
}

void insert_or_replace_character(char user_input, char** char_array, int* current_index, int* last_index, COORD* x_y){
    // Allocate an extra space for the new keyword.
    if(*current_index > *last_index){
        ++*last_index;
        add_to_char_array(user_input, char_array, *last_index);
    }
    else{
        // Replaces character in array.
        (*char_array)[*current_index] = user_input;
    }
    // Move current index to the upcoming index.
    move_current_index(1, current_index, *last_index, x_y);
}

void add_to_char_array(char user_input, char** char_array, int last_index){
    // Allocating a new array with the new size. (+1)
    char* new_array = (char*)malloc(((last_index||1)+1)*sizeof(char));
    // Copying over old string.
    for(int i=0; i<last_index; i++){
        new_array[i] = (*char_array)[i];
    }
    // Adding new character.
    new_array[last_index] = user_input;
    // Adding delimiter.
    new_array[last_index+1] = '\0';
    // Freeing old pointer.
    free(*char_array);
    // Assigning new address to the given character array pointer.
    *char_array = new_array;
}

void move_cursor_left_right(int left_right, COORD* x_y){
    if(left_right)
        ++x_y->X;
    else
        --x_y->X;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *x_y);
}