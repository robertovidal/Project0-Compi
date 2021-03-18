#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "global.h"
#include "parser.h"

int main() {
    char fileName[128];
    printf("Enter file name: ");
    scanf("%s", fileName);
    file = fopen(fileName, "r");
    if(file == NULL) {
        printf("No se pudo leer el archivo.\n");
        exit(EXIT_FAILURE);
    }
    fileNameR = "result.txt";
    system_goal();
    fclose(file);
    return 0;
}



