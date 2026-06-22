#include "stdio.h"

#include "src/str.h"
#include "src/strbuilder.h"

int main(int argc, char const *argv[]){
    StrBuilder * s = new_str_builder(10, NULL);

    str_builder_push(s, "kelvi ");
    str_builder_push(s, "julho");

    Str * t = str_builder_to_str(s);
    str_builder_deinit(s);

    printf("%s", t->data);

    return 0;
}
