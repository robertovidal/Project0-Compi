#include <stdio.h>
#include <stdlib.h>
#include "global.h"


int main()
{
    char fileName[20];
    printf("Enter file name: ");
    scanf("%s", fileName);
    file = fopen(fileName, "r");
    system_goal();
    return 0;
}




