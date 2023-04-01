#include <stdlib.h>
#include<stdio.h>
#include "tokenizer.h"

tokenArray tokenizer(char* query_string){
    // Initial token array size is 100 strings.
    int initial_tokens_array_size = 100;
    tokenArray token_array = {.array=(char**)malloc(sizeof(char*)*initial_tokens_array_size),
                              .size=0};
    int initial_token_array_size;
    int toggle_tokenizing = 1;
    int double_tokens_array_size = 1;
    int current_query_string_index = 0;
    int get_previous_token = 0;
    int escape_toggle;
    int next_token_toggle;
    int current_token_char_index;
    int double_token_size;
    for(int i=0; toggle_tokenizing; i++){
        // Initial token size is 50 characters.
        token_array.array[i] = (char*)malloc(sizeof(char)*50);
        escape_toggle = current_token_char_index = next_token_toggle = 0;
        double_token_size = 1;
        initial_token_array_size = 50;
        if(i < double_tokens_array_size*initial_tokens_array_size){
            ++token_array.size;
            while(!next_token_toggle){
                if (current_token_char_index < 50*double_token_size){
                    if(get_previous_token){
                        token_array.array[i][current_token_char_index] = query_string[current_query_string_index-1];
                        token_array.array[i][current_token_char_index+1] = '\0';
                        get_previous_token = 0;
                        next_token_toggle = 1;
                    }
                    else{
                        switch(query_string[current_query_string_index]){
                            case 32:
                                if(!escape_toggle){
                                    if(current_token_char_index)
                                        token_array.array[i][current_token_char_index] = '\0';
                                    else
                                        --i;
                                    next_token_toggle = 1;
                                }
                                else {
                                    token_array.array[i][current_token_char_index] = query_string[current_query_string_index];
                                }
                                break;
                            case '\0':
                                token_array.array[i][current_token_char_index] = '\0';
                                next_token_toggle = 1;
                                toggle_tokenizing = 0;
                                break;
                            case '\'':
                                token_array.array[i][current_token_char_index] = query_string[current_query_string_index];
                                escape_toggle = !escape_toggle;
                                break;
                            case ',':
                            case '=':
                            case '>':
                            case '<':
                                if(current_token_char_index && !escape_toggle){
                                    token_array.array[i][current_token_char_index] = '\0';
                                    get_previous_token = 1;
                                    next_token_toggle = 1;
                                }
                                else if(!current_token_char_index && query_string[current_token_char_index+1] != 32 && !escape_toggle){
                                    get_previous_token = 1;
                                    next_token_toggle = 1;
                                    i--;
                                }
                                else
                                    token_array.array[i][current_token_char_index] = query_string[current_query_string_index];
                                break;
                            default:
                                token_array.array[i][current_token_char_index] = query_string[current_query_string_index];
                                break;
                        }
                        ++current_token_char_index;
                        ++current_query_string_index;
                    }
                }
                else{
                    // Double the token size and copy it over.
                    double_token_size *= 2;
                    char* new_token_array = (char*)malloc(sizeof(char)*double_token_size*initial_token_array_size);
                    for (int j=0; j<initial_token_array_size*double_token_size/2; j++){
                        new_token_array[j] = token_array.array[i][j];
                    }
                    free(token_array.array[i]);
                    token_array.array[i] = new_token_array;
                }
            }
        }
        else{
            // Double the tokens array size and copy it over.
            double_tokens_array_size *= 2;
            char** new_tokens_array = (char**)malloc(sizeof(char*)*double_tokens_array_size*initial_tokens_array_size);
            for (int i=0; i<initial_tokens_array_size*double_token_size/2; i++){
                new_tokens_array[i] = token_array.array[i];
            }
            free(token_array.array);
            token_array.array = new_tokens_array;
        }
    }
    return token_array;
}
