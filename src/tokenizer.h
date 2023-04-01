typedef struct {
    int size;
    char** array;
} tokenArray;
tokenArray tokenizer(char* query_string);
