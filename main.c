#include "stdio.h"

#include "src/str.h"

int main(int argc, char const *argv[]){
    
    String * a = new_string("kelvi");
    String * b = new_string("julho");
    String * c = string_concate(a, b);

    String * d = string_sub(c, 0, 5);

    printf("%s %s", c->data, d->data);

    String * e = string_sub(d, 0, 1);

    printf("%s", e->data);

    string_deinit(a);
    string_deinit(c);

    return 0;
}
