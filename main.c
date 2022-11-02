#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_lower(char c)
{
    return c >= 'a' && c <= 'z';
}

bool is_upper(char c)
{
    return c >= 'A' && c <= 'Z';
}

char to_lower(char c)
{
    return c + 32;
}

char to_upper(char c)
{
    return c - 32;
}

char switch_case(char c)
{
    return is_lower(c) ? to_upper(c) : to_lower(c);
}

// length of newline terminated strings
// ugly underscore to avoid builtin conflict
int str_len(char *str)
{
    int i;
    for (i = 0; str[i] != '\0'; i++)
        ;
    return i;
}

// replace \n with \0 to trim the newline
void trim_newline(char *str)
{
    int i;
    for (i = 0; str[i] != '\n'; i++)
    {
        // no need to trim
        if (str[i] == '\0')
            return;
    }

    str[i] = '\0';
}

// processes to string, prints results to stdout
void process_string(char *str)
{
    trim_newline(str);

    // initial word
    printf("%s ", str);

    int upper_chars = 0;
    int lower_chars = 0;

    bool palindrom = true; // initially assume true

    int len = str_len(str);

    char c;
    for (int i = 0; (c = str[i]) != '\0'; i++)
    {

        // count upper & lower
        if (is_lower(c))
        {
            lower_chars++;
        }
        else if (is_upper(c))
        {
            upper_chars++;
        }

        // print switched case
        printf("%c", switch_case(c));

        // palindrom check
        if (str[i] != str[len - i - 1])
        {
            palindrom = false;
        }
    }

    printf(" %d %d ", lower_chars, upper_chars);

    // all to lower
    for (int i = 0; (c = str[i]) != '\0'; i++) {
        printf("%c", is_upper(c) ? to_lower(c) : c);
    }

    printf(" ");

    // all to upper
    for (int i = 0; (c = str[i]) != '\0'; i++) {
        printf("%c", is_lower(c) ? to_upper(c) : c);
    }

    printf(" %d\n", palindrom);
}

int main()
{
    char line[100];

    int line_count = 0;

    // Read line count
    if (fgets(line, 100, stdin) != NULL)
    {
        char *endptr;
        long num = strtol(line, &endptr, 10);

        if (num > __INT_MAX__)
        {
            fprintf(stderr, "Line count out of bounds.\n");
            return 1;
        }

        if (*endptr != '\n')
        {
            fprintf(stderr, "Line count contains invalid characters (%s).\n", line);
            return 1;
        }

        line_count = (int)num;
    }

    int line_index = 0;
    int word_index = 0;

    while (fgets(line, 100, stdin) != NULL && line_index < line_count)
    {
        char *token = strtok(line, " \n\0");
        if (token != NULL) {
            do
            {
                printf("Slovo %d: ", word_index);
                process_string(token);
                word_index++;
            } while ((token = strtok(NULL, " \0")) != NULL);
            
            line_index++;
        }

    }
    return 0;
}