%{
#include <stdio.h>
#include <string.h>

int has_lower = 0;
int has_upper = 0;
int has_digit = 0;
int has_special = 0;
int length = 0;

void reset_flags() {
    has_lower = has_upper = has_digit = has_special = length = 0;
}
%}

%%
[a-z]    { has_lower = 1; length++; }
[A-Z]    { has_upper = 1; length++; }
[0-9]    { has_digit = 1; length++; }
[*;#$@]  { has_special = 1; length++; }
.        { length++; }
\n       {
    if (length >= 9 && length <= 15 && 
        has_lower && has_upper && 
        has_digit && has_special) {
        printf("Valid password!\n");
    } else {
        printf("Invalid password. Requirements not met:\n");
        if (length < 9 || length > 15)
            printf("- Length must be between 9 and 15 characters (current: %d)\n", length);
        if (!has_lower)
            printf("- Missing lowercase letter\n");
        if (!has_upper)
            printf("- Missing uppercase letter\n");
        if (!has_digit)
            printf("- Missing digit\n");
        if (!has_special)
            printf("- Missing special character (*;#$@)\n");
    }
    reset_flags();
}
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Password Validator\n");
    printf("=================\n\n");
    printf("Enter a password to validate. Press Enter after each password.\n");
    printf("Password requirements:\n");
    printf("- Length: 9-15 characters\n");
    printf("- Must contain at least one: lowercase, uppercase, digit, special char (*;#$@)\n");
    printf("Type Ctrl+D (Unix) or Ctrl+Z (Windows) to exit.\n\n");
    yylex();
    return 0;
}