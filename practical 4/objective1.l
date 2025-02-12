%{
#include <stdio.h>
%}

%%
[0-9]+ { printf("%s\n", yytext); }
.|\n    /* ignore all other characters */
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Number Extractor\n");
    printf("================\n\n");
    printf("Enter text containing numbers. Press Enter after each line.\n");
    printf("Type Ctrl+D (Unix) or Ctrl+Z (Windows) to exit.\n\n");
    yylex();
    return 0;
}        