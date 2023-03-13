#include <windows.h>

// REPL signature.
char* REPL(void);

// Function to move index left or right, depending on user input.
void move_current_index(int left_or_right, int* current_index, int last_index, COORD* x_y);

// Function to insert/replace character into character array.
void insert_or_replace_character(char user_input, char** char_array, int* current_index, int* last_index, COORD* x_y);

// Function to allocate new memory for new character inputs.
void add_to_char_array(char user_input, char** char_array, int last_index);

// Function to move cursor left or right.
void move_cursor_left_right(int left_right, COORD* x_y);