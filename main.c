#include <stdio.h>
#include "string.h"

int main(){
    string* string=create_string();
    string_append_str(string, "hello guys ");
    string_append_char(string, 'c');
    const char* realstring=string_cstr(string);
    printf("%s",realstring);
    clear_string(string);
    free_string(&string);
}
