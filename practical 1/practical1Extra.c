

//a+bb

#include <stdio.h>
#include <string.h>

int isValid(char str[]) {
    int i = 0;
    int size = strlen(str);

   
    while (str[i] == 'a') {
        i++;
    }

   
    if (i == 0) {
        return 0;
    }

    
    if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
        return 1; 
    }

    return 0; 
}

int main() {
    char input[100];

    while (1) {
        printf("Enter ");
        scanf("%s", input);

        if (strcmp(input, "e") == 0) {
            break;
        }

        if (isValid(input)) {
            printf("%s: Valid\n", input);
        } else {
            printf("%s: Invalid\n", input);
        }
    }

    return 0;
}