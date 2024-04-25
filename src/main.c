#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "avl.h"

#define YLEN 100
#define MAX_LINE 4096
#define DELIM "\t\r "
#define IS_NUM(x) (strspn((x), "0123456789.,") == strlen((x)))

void fix_num(char *s) {
    for ( ; *s ; ++s) {
        if (*s == ',') *s = '.';
    }
}

int main(void) {
    AVLTree *tree = avl_create_node(0);
    char buffer[MAX_LINE];
    while (fgets(buffer, MAX_LINE, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
        // NF behavior
        char *token = strtok(buffer, DELIM), *last_num = token;
        while ((token = strtok(NULL, DELIM))) {
            if (IS_NUM(token)) last_num = token;
        }
        fix_num(last_num);
        double grade = strtod(last_num, NULL);
        tree = avl_insert(tree, grade);
        if (errno) {
            perror("strtod@main");
            exit(errno);
        }
    }
    int total_stud = avl_total(tree);
    int passed = avl_more_than(tree, 5);
    int good = avl_more_than(tree, 8);
    avl_inorder(tree);
    printf("\n%.2lf%% passed, %.2lf%% gud\n", (double) passed / total_stud * 100, (double) good / total_stud * 100);
    return 0;
}