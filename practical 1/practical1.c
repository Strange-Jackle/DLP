//a*bb

#include <stdio.h>
#include <string.h>

int isValid(char str[]) {
    int i = 0;
    int size;
    size = strlen(str);
    
    if(size==2){
        if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
        return 1; //V
    }

    return 0; //I
    }
    else{

    while (str[i] == 'a') {
        i++;
    }

    
    if (str[i] == 'b' && str[i + 1] == 'b' && str[i + 2] == '\0') {
        return 1; //V
    }

    return 0; //I
}
}

int main() {
    char i[100];

    while (1) {
        printf("Enter : ");
        scanf("%s", i);
        if (strcmp(i, "e") == 0) {
            break;
        }
        if (isValid(i)) {
            printf("%s: Valid\n", i);
        } else {
            printf("%s: Invalid\n", i);
        }
    }
    return 0;
}