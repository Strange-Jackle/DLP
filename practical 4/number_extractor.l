%{
#include <stdio.h>
%}

%%
[0-9]+    { printf("%s\n", yytext); }  /* Match one or more digits and print them */
[^0-9\n]+ /* Ignore non-digit characters except newline */
\n        /* Handle newline */
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter text with numbers (press Enter after each line):\n");
    yylex();
    return 0;
}