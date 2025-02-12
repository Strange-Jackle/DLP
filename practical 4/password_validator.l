%{
#include <stdio.h>
#include <string.h>

int lowercase = 0;
int uppercase = 0;
int digits = 0;
int symbols = 0;
int length = 0;
%}

%%
[a-z]    { lowercase++; length++; }
[A-Z]    { uppercase++; length++; }
[0-9]    { digits++; length++; }
[*;#$@]  { symbols++; length++; }
\n       { 
            if (length >= 9 && length <= 15 && 
                lowercase >= 1 && uppercase >= 1 && 
                digits >= 1 && symbols >= 1) {
                printf("Valid password\n");
            } else {
                printf("Invalid password\n");
            }
            
            /* Reset counters for next input */
            lowercase = 0;
            uppercase = 0;
            digits = 0;
            symbols = 0;
            length = 0;
        }
.        { length++; } /* Count other characters in length but don't validate them */
%%

int yywrap() {
    return 1;
}
