#include "string.h"
#include "stdlib.h"

#include "str.h"

#ifndef _K_STRBUILDER_H
#define _K_STRBUILDER_H

typedef struct {
    char * data;
    unsigned long length;
    unsigned long capacity;
} StrBuilder;

StrBuilder * new_str_builder(unsigned long capacity, const char * value) {
    StrBuilder * builder = (StrBuilder*)malloc(sizeof(StrBuilder));

    builder->data = (char*)malloc(capacity);
    if (value != NULL) {
        unsigned long length = strlen(value);

        builder->length = length;
        memcpy(builder->data, value, length + 1);
    } else {
        builder->length = 0;
    }
    builder->capacity = capacity;

    return builder;
}

void str_builder_deinit(StrBuilder * self) {
    free(self->data);
    free(self);
}

Str * str_builder_to_str(StrBuilder * self) {
    return new_str(self->data);
}

void str_builder_push_str(StrBuilder * self, Str * str) {
    unsigned long fill = self->length + str->length;

    if (fill >= self->capacity) {
        unsigned long new_capacity = self->capacity * 2 + fill;
        char * new_data = (char*)realloc(self->data, new_capacity);

        if (new_data == NULL) {
            return;
        }

        self->data = new_data;
        self->capacity = new_capacity;
    }

    memcpy(self->data + self->length, str->data, str->length + 1);
    self->length += str->length;
}

void str_builder_set_str(StrBuilder * self, unsigned long position, Str * str) {
    memcpy(self->data + position, str->data, str->length);
}

void str_builder_push(StrBuilder * self, const char * value) {
    unsigned long length = strlen(value);
    unsigned long fill = self->length + length;

    if (fill >= self->capacity) {
        unsigned long new_capacity = self->capacity * 2 + fill;
        char * new_data = (char*)realloc(self->data, new_capacity);

        if (new_data == NULL) {
            return;
        }

        self->data = new_data;
        self->capacity = new_capacity;
    }

    memcpy(self->data + self->length, value, length + 1);
    self->length += length;
}

void str_builder_set(StrBuilder * self, unsigned long position, char * value) {
    memcpy(self->data + position, value, strlen(value));
}

#endif