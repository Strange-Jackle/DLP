%{
#include <stdio.h>

int char_count = 0;
int word_count = 0;
int line_count = 0;
int in_word = 0;  // Flag to track if we're inside a word
%}

%%
[^ \t\n]+    { 
    char_count += yyleng;  // Add length of the word
    if (!in_word) {
        word_count++;
        in_word = 1;
    }
}

[ \t]       { 
    char_count++;  // Count spaces and tabs
    in_word = 0;   // Mark that we're not in a word
}

\n          { 
    char_count++;  // Count the newline character
    line_count++;  // Increment line count
    in_word = 0;   // Mark that we're not in a word
}

<<EOF>>     {
    if (char_count > 0 && !line_count) line_count = 1;  // Handle single line without newline
    printf("\nCharacters : %d\n", char_count);
    printf("Words : %d\n", word_count);
    printf("Lines : %d\n", line_count);
    return 0;
}

%%

int yywrap() {
    return 1;
}

int main() {
    printf("Text Counter\n");
    printf("============\n\n");
    printf("Enter text to count characters, words, and lines.\n");
    printf("Type Ctrl+D (Unix) or Ctrl+Z (Windows) to see results.\n\n");
    yylex();
    return 0;
}