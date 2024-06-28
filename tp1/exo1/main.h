#ifndef MAIN_H
#define MAIN_H

int count_occurrences(FILE *file, const char *target);
FILE *open_file(const char *filename);
void close_file(FILE *file);

#endif
