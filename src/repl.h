#include <windows.h>

// Struct that holds the character array and all its properties.
typedef struct {
    int current_index;
    int last_index;
    int array_size;
    char* array;
} array_of_char;

// REPL wrapper function.
char* REPL(void);

// Function to move index left or right, depending on user input.
void move_current_index(int left_or_right, array_of_char* array_of_char, COORD* x_y);

// Function to insert/replace character into character array.
void insert_or_replace_character(char user_input, array_of_char* array_of_char, COORD* x_y);

// Function to remove character from character array.
void remove_from_char_array(array_of_char* array_of_char, COORD* x_y);

// Function to allocate new memory for new character inputs.
void add_to_char_array(char user_input, array_of_char* array_of_char);

// Function to move cursor left or right.
void move_cursor_left_right(int left_right, COORD* x_y);

// Function to paste from clipboard.
void paste_from_clipboard(array_of_char* array_of_char, COORD* x_y);
