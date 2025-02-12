%{
#include <stdio.h>
#include <string.h>
%}

%%
[cC][hH][aA][rR][uU][sS][aA][tT] { printf("university"); }
.    { printf("%s", yytext); }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Word Replacer\n");
    printf("=============\n\n");
    printf("Enter text containing 'charusat'. Press Enter after each line.\n");
    printf("Type Ctrl+D (Unix) or Ctrl+Z (Windows) to exit.\n\n");
    yylex();
    return 0;
}