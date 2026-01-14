#include "string.h"
#include <stdio.h>

// int main() {
//   string *string = create_string();
//   string_append_str(string, "hello guys");

//   const char *first = string_cstr(string);
//   printf("append str '%s'\n", first);

//   string_append_char(string, 'c');

//   const char *second = string_cstr(string);
//   printf("append char c '%s'\n", second);

//   string_prepend_char(string, 'c');

//   const char *third = string_cstr(string);
//   printf("prepend char c '%s'\n", third);

//   string_prepend_str(string, "niggers");

//   const char *fourth = string_cstr(string);
//   printf("prepend str '%s'\n", fourth);

//   // string_remove_range(string,10 , 5);

//   // const char *fifth = string_cstr(string);
//   // printf("remove range str '%s'\n", fifth);

//   // string_remove_from(string,0);

//   // const char *sixth = string_cstr(string);
//   // printf("remove range str '%s'\n", sixth);

//   string_replace_char(string,'h','0');

//   const char *seventh = string_cstr(string);
//   printf("replace char '%s'\n", seventh);

//   string_replace_str(string,"niggers","123");

//   const char *eigth = string_cstr(string);
//   printf("replace str '%s'\n", eigth);

//   string_trim(string,'c');

//   const char *ninth = string_cstr(string);
//   printf("trim '%s'\n", ninth);

//   string_toupper(string);

//   const char *tenth = string_cstr(string);
//   printf("toupper '%s'\n", tenth);

//   string_tolower(string);

//   const char *eleventh = string_cstr(string);
//   printf("tolower '%s'\n", eleventh);

//   clear_string(string);
//   free_string(&string);
// }

int main(){
    string *string = create_string();
    string_append_str(string, "hello,guys,this,is,loren,hahahahahhahahah");

    vector* stringvec=string_split_char(string, ',');

    clear_string(string);
    free_string(&string);
}
