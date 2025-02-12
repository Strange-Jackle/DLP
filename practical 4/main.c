#include <stdio.h>

extern int yylex();
extern FILE* yyin;

int main() {
    printf("Enter password (press Enter after each password):\n");
    
    // Read from standard input
    yyin = stdin;
    
    // Start lexical analysis
    yylex();
    
    return 0;
}
