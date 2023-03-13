#include "repl.h"
#include <stdio.h>
#include "repl.c"

void main(){
    //Variables
    char* user_entry;
    user_entry = REPL();
    printf("\n %s", user_entry);
}