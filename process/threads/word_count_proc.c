#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

size_t wc(const char *string) {

    size_t count = 0;

    for (bool inword = false; *string; ++string) {
        if (isspace(*string)) {
            if (inword) {
                inword = false;
            }
        } else {
            if (!inword) {
                inword = true;
                ++count;
            }
        }
    }
    return count;
}

size_t wc_file(const char *filename) {
    char * file_content = 0;//how to init? 0 or null?
    long length;//what is the modern typ?

    FILE * f = fopen(filename, "rb");

    if (f) {
        fseek(f, 0, SEEK_END);
        length = ftell(f);
        fseek(f, 0, SEEK_SET);
        file_content = malloc(length);
        if (file_content) {
            fread(file_content, 1, length, f);
        }
        fclose(f);

        return wc(file_content);
    }

    return -1;
}

int main(void) {
    char * data = " manel   manel";
    printf("%zu\n", wc(data));
    return EXIT_SUCCESS;
}
