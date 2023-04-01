#include "repl.c"
#include "tokenizer.c"
#include <stdio.h>
void main(){
    //Variables
    char* user_entry;
    tokenArray token_array;
    user_entry = REPL();
    token_array = tokenizer(user_entry);
    printf("\n");
    for(int i = 0; i < token_array.size; i++){
        printf("%s \n", token_array.array[i]);
    }
}