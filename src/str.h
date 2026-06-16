#include "string.h"
#include "stdlib.h"

#ifndef SIMPLE_STRING_H
#define SIMPLE_STRING_H

typedef struct {
    char * data;
    unsigned long length;
} String;

//create a new empty string with defined length
//this function considers the null terminator, so it is not necessary to include it in the length argument
String * new_string_cap(unsigned long length) {
    String * str = (String*)malloc(sizeof(String));

    str->data = (char*)malloc(length + 1);
    str->length = length;

    return str;
}
String * new_string(char * data) {
    unsigned long length = strlen(data);

    String * str = new_string_cap(length);
    memcpy(str->data, data, length + 1);

    return str;
}
void string_deinit(String * self) {
    free(self->data);
    free(self);
}
unsigned long string_length(String * self) {
    return self->length;
}
String * string_concate(String * a, String * b) {
    String * str = new_string_cap(a->length + b->length);

    memcpy(str->data, a->data, a->length);
    memcpy(str->data + a->length, b->data, b->length + 1);

    return str;
}
String * string_sub(String * self, unsigned int start, unsigned int end) {
    if (start >= end || end >= self->length) {
        return NULL;
    }

    unsigned long length = end - start;

    String * str = new_string_cap(length);

    memcpy(str->data, self->data + start, length);
    ((char*)str->data)[length] = '\0';
    
    return str;
}
char string_at(String * self, unsigned int index) {
    return ((char*)self->data)[index];
}
int string_equal(String * a, String * b) {
    if (a->length != b->length) {return 0;}
    return memcmp(a->data, b->data, a->length) == 0;
}

#endif