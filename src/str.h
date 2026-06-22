#include "string.h"
#include "stdlib.h"

#ifndef _K_STR_H
#define _K_STR_H

typedef struct {
    char * data;
    unsigned long length;
} Str;

//create a new empty str with length defined
//it is not necessary to consider a null terminator in the `capacity` parameter
Str * new_str_capacity(unsigned int capacity) {
    //create new str ptr
    Str * str = (Str*)malloc(sizeof(Str));

    //allocate chars
    //note: length + 1 for null terminator
    str->data = (char*)malloc(capacity + 1);
    ((char*)str->data)[capacity + 1] = '\0';
    //set str length
    str->length = capacity;

    return str;
}

//create a new initialized str
Str * new_str(const char * value) {
    //get value length
    unsigned int length = strlen(value);

    //create new str ptr
    Str * str = new_str_capacity(length);
    //set str value
    memcpy(str->data, value, length + 1);

    return str;
}

void str_deinit(Str * self) {
    free(self->data);
    free(self);
}

//create a new duplicated str
Str * str_duplicate(Str * self) {
    return new_str(self->data);
}

//create a new str as substr of another str
Str * str_substr(Str * self, unsigned int start, unsigned int end) {
    //check if range is valid
    if (start < 0 || start >= end || end >= self->length) {
        return NULL;
    }
    
    //calculate byte count for substring
    unsigned long length = end - start;
    //create substring ptr
    Str * str = new_str_capacity(length);
    //copy bytes for substring between start and end
    memcpy(str->data, self->data + start, length);
    
    return str;
}

//create a new concatenated str
Str * str_concate(Str * a, Str * b) {
    //create concatenate str ptr
    Str * str = new_str_capacity(a->length + b->length);

    memcpy(str->data, a->data, a->length);
    memcpy(str->data + a->length, b->data, b->length + 1);

    return str;
}

int str_equal(Str * a, Str * b) {
    if(a->length != b->length) {
        return 0;
    }
    return memcmp(a->data, b->data, a->length) == 0;
}

Str * str_repeat(char * value, unsigned long length) {
    unsigned long count = strlen(value);
    
    //create repeat str ptr
    Str * str = new_str_capacity(length);
    //repeat chars

    unsigned long index = 0;
    while (index < length) {
        unsigned int diff = length - index;
        unsigned long steps = diff < count ? diff : count;

        memcpy(str->data + index, value, steps);
        index += steps;
    }

    return str;
}

#endif