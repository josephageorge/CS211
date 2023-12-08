#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    char* string = argv[1];
    int i;
    for (i = 0; i < strlen(string); i++) {
        char letter = string[i];
        if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z')) {
            char base = (letter >= 'a') ? 'a' : 'A';
            putchar((letter - base + 13) % 26 + base);
        } else {
            putchar(letter);
        }
    }
    putchar('\n');

    return 0;
}


