#include <conio.h> 
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include "repl.h"


// Interface to Database Engine (REPL).
char* REPL(void){
    // Variables
    array_of_char array_of_char = {
        .array_size = 1000,
        .current_index = 0,
        .last_index = -1,
    };
    array_of_char.array = (char*)malloc(sizeof(char)*array_of_char.array_size);
    int toggle = 1;
    COORD x_y = {.X = 0, .Y = 1};
    char scanned_char;
    // Conditional loop to take input from user until exit is written.
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
                        move_current_index(0, &array_of_char, &x_y);
                        break;

                    // Right arrow key case.
                    case 77:
                        move_current_index(1, &array_of_char, &x_y);
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
                remove_from_char_array(&array_of_char, &x_y);
                break;
            
            case 22:
                paste_from_clipboard(&array_of_char, &x_y);
                break;

            // Enter key case.
            case 13:
                toggle = 0;
                break;

            // Actual input characters.
            default:
                // Print character, Move cursor and save character.
                printf("%c", scanned_char);
                insert_or_replace_character(scanned_char, &array_of_char, &x_y);
                break;
        }
    }
    // Continue until toggle is turned.
    while(toggle);
    return array_of_char.array;
}

void move_current_index(int left_or_right, array_of_char* array_of_char, COORD* x_y){
    // Move right
    if (left_or_right){
        // Increment Index and move cursor to the right.
        if(array_of_char->current_index <= array_of_char->last_index){
            array_of_char->current_index += 1;
            move_cursor_left_right(1, x_y);
        }
    }
    // Move left
    // Decrement Index and move cursor to the left.
    else if(array_of_char->current_index > 0){
        --array_of_char->current_index;
        move_cursor_left_right(0, x_y);
    }
}

void insert_or_replace_character(char user_input, array_of_char* array_of_char, COORD* x_y){
    // Allocate an extra space for the new keyword.
    if(array_of_char->current_index > array_of_char->last_index){
        ++array_of_char->last_index;
        add_to_char_array(user_input, array_of_char);
    }
    else{
        // Replaces character in array.
        (array_of_char->array)[array_of_char->current_index] = user_input;
    }
    // Move current index to the upcoming index.
    move_current_index(1, array_of_char, x_y);
}

void add_to_char_array(char user_input, array_of_char* array_of_char){
    char* new_array = array_of_char->array;
    if(array_of_char->last_index+2 > array_of_char->array_size){
        // Allocating a new array with the new size (+1000).
        array_of_char->array_size += 1000;
        new_array = (char*)malloc((array_of_char->array_size)*sizeof(char));
        // Copying over old string.
        for(int i=0; i<array_of_char->last_index; i++){
            new_array[i] = (array_of_char->array)[i];
        }
        // Freeing old pointer.
        free(array_of_char->array);
    }
    // Adding new character.
    new_array[array_of_char->last_index] = user_input;
    // Adding delimiter.
    new_array[array_of_char->last_index+1] = '\0';
    // Assigning new address to the given character array pointer.
    array_of_char->array = new_array;
}

void remove_from_char_array(array_of_char* array_of_char, COORD* x_y){
    if(array_of_char->current_index){
        move_current_index(0, array_of_char, x_y);
        for(int i=0; i<array_of_char->last_index; i++){
            if(i>=array_of_char->current_index){
                array_of_char->array[i] = array_of_char->array[i+1];
                printf("%c", array_of_char->array[i+1]);
            }
        }
        array_of_char->array[array_of_char->last_index] = '\0';
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

void paste_from_clipboard(array_of_char* array_of_char, COORD* x_y){
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
            insert_or_replace_character(buffer_pointer[i], array_of_char, x_y);
        }
        else{
            toggle_copy = 0;
        }
    }
}
