#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "monty.h"

stack_t *stack = NULL;

int main(int argc, char *argv[]) {
    FILE *file;
    char *line = NULL;
    size_t len = 0;
    unsigned int line_number = 0;

    if (argc != 2) {
        fprintf(stderr, "USAGE: monty file\n");
        return EXIT_FAILURE;
    }

    file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    line = malloc(sizeof(char) * 1024);
    if (line == NULL) {
        fprintf(stderr, "Error: Unable to allocate memory for line\n");
        fclose(file);
        return EXIT_FAILURE;
    }

    while (fgets(line, len, file) != NULL) {
        char *opcode = strtok(line, " \t\n");
	char *value_str;
        int value;
        if (opcode == NULL || opcode[0] == '#') {
            continue; /* Ignore empty lines and comments */
        }

        if (strcmp(opcode, "push") == 0) {
            value_str = strtok(NULL, " \t\n");
            if (value_str == NULL) {
                fprintf(stderr, "L%u: usage: push integer\n", line_number);
                fclose(file);
                free(line);
                return EXIT_FAILURE;
            }

            value = atoi(value_str);
            push(&stack, value, line_number);
        } else if (strcmp(opcode, "pall") == 0) {
            pall(&stack, line_number);
        } else {
            fprintf(stderr, "L%u: unknown instruction %s\n", line_number, opcode);
            fclose(file);
            free(line);
            return EXIT_FAILURE;
        }

        line_number++;
    }

    fclose(file);
    free(line);
    return EXIT_SUCCESS;
}
