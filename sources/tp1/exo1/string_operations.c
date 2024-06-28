#include <stdio.h>
#include <string.h>

int count_occurrences(FILE *file, const char *target)
{
    int count = 0;
    char buffer[1024];
    size_t target_len = strlen(target);

    while (fgets(buffer, sizeof(buffer), file))
    {
        char *pos = buffer;
        while ((pos = strstr(pos, target)) != NULL)
        {
            count++;
            pos += target_len;
        }
    }

    return count;
}
