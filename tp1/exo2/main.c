#include <stdio.h>
#include <stdlib.h>
#include "main.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s <filename> <target>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *target = argv[2];

    FILE *file = open_file(filename);
    int occurrences = count_occurrences(file, target);
    close_file(file);

    printf("The string '%s' occurred %d times in the file '%s'\n", target, occurrences, filename);
    return EXIT_SUCCESS;
}
