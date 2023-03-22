#include <conio.h> 
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "repl.h"

void remove_from_char_array(char* char_array, int* current_index, int* last_index, COORD* x_y);

// Interface to Database Engine (REPL).
char* REPL(void){
    system("cls");
    // Variables
    int char_array_size = 1000;
    char* char_array = (char*)malloc(sizeof(char)*char_array_size);
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
            
            // Backspace Key case.
            case 8:
                remove_from_char_array(char_array, &current_index, &last_index, &x_y);
                break;
            
            case 22:
                paste_from_clipboard(&char_array, &current_index, &last_index, &x_y, &char_array_size);
                break;

            // Enter key case.
            case 13:
                toggle = 0;
                break;

            // Actual input characters.
            default:
                // Print character, Move cursor and save character.
                printf("%c", scanned_char);
                insert_or_replace_character(scanned_char, &char_array, &current_index, &last_index, &x_y, &char_array_size);
                break;
        }
    }
    // Continue until toggle is turned.
    while(toggle);
    return char_array;
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

void insert_or_replace_character(char user_input, char** char_array, int* current_index, int* last_index, COORD* x_y,  int* char_array_size){
    // Allocate an extra space for the new keyword.
    if(*current_index > *last_index){
        ++*last_index;
        add_to_char_array(user_input, char_array, *last_index, char_array_size);
    }
    else{
        // Replaces character in array.
        (*char_array)[*current_index] = user_input;
    }
    // Move current index to the upcoming index.
    move_current_index(1, current_index, *last_index, x_y);
}

void add_to_char_array(char user_input, char** char_array, int last_index, int* char_array_size){
    char* new_array = *char_array;
    if(last_index+2 > *char_array_size){
        // Allocating a new array with the new size (+1000).
        *char_array_size += 1000;
        new_array = (char*)malloc((*char_array_size)*sizeof(char));
        // Copying over old string.
        for(int i=0; i<last_index; i++){
            new_array[i] = (*char_array)[i];
        }
        // Freeing old pointer.
        free(*char_array);
    }
    // Adding new character.
    new_array[last_index] = user_input;
    // Adding delimiter.
    new_array[last_index+1] = '\0';
    // Assigning new address to the given character array pointer.
    *char_array = new_array;
}

void remove_from_char_array(char* char_array, int* current_index, int* last_index, COORD* x_y){
    if(*current_index){
        move_current_index(0, current_index, *last_index, x_y);
        for(int i=0; i<*last_index; i++){
            if(i>=*current_index){
                char_array[i] = char_array[i+1];
                printf("%c", char_array[i+1]);
            }
        }
        char_array[*last_index] = '\0';
        printf("%c", ' ');
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *x_y);
    }
}

void move_cursor_left_right(int left_right, COORD* x_y){
    if(left_right)
        ++x_y->X;
    else
        --x_y->X;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), *x_y);
}

void paste_from_clipboard(char** char_array, int* current_index, int* last_index, COORD* x_y,  int* char_array_size){
    char* buffer_pointer;
    int toggle_copy = 1;
    HANDLE data_handler;
    OpenClipboard(NULL);
    data_handler = GetClipboardData(CF_TEXT);
    CloseClipboard();
    buffer_pointer = (char*)GlobalLock(data_handler);
    for(int i=0;toggle_copy;i++){
        if(buffer_pointer[i] != '\0'){
            printf("%c",buffer_pointer[i]);
            insert_or_replace_character(buffer_pointer[i], char_array, current_index, last_index, x_y, char_array_size);
        }
        else{
            toggle_copy = 0;
        }
    }
}