#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "parser.h"

void resultFileName(char f[]) {
    size_t len = strlen(f);
    while(f[len] != '.') {
        f[len] = '\0';
        len--;
    }
    f[len+1] = 's';

    fileNameR = f;
}

int main() {
    char fileName[128];
    printf("Enter file name: ");
    scanf("%s", fileName);
    file = fopen(fileName, "r");
    if(file == NULL) {
        printf("No se pudo leer el archivo.\n");
        exit(EXIT_FAILURE);
    }
    resultFileName(fileName);
    system_goal();
    printf("File compiled successfully in the file: %s \n", fileNameR);
    fclose(file);
    return 0;
}



