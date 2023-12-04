#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>



// accepts a line of text and the totals of red green blue
int process_line(size_t length, char * text)
{

}

int processFile(char * path, int red, int green, int blue)
{
    FILE *filePointer = fopen(path, "r");
    if (filePointer == NULL)
    {
        printf("Error reading file\r\n");
        exit(1);
    }

    size_t maxLineLength = 512;
    char line[maxLineLength];

    //Overall result
    int result = 0;

    // get each line
    while (fgets(line, maxLineLength, filePointer))
    {
        // handle each line
        size_t length = strlen(line);
        int temp = process_line(length, line);
        result += temp;
        //printf("result:%d\r\n", temp);
    }
    fclose(filePointer);
    return result;
}



int main(void)
{
    return 0;
}