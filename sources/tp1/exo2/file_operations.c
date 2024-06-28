#include <stdio.h>
#include <stdlib.h>
#include "main.h"

FILE *open_file(const char *filename)
{
    FILE *file = fopen(filename, "r+");
    if (!file)
    {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    return file;
}

void close_file(FILE *file)
{
    if (fclose(file) != 0)
    {
        perror("Unable to close file");
        exit(EXIT_FAILURE);
    }
}
