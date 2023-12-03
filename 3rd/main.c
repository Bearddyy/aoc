#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


static const size_t maxLineLength = 512;
static char lines[3][512];

int processLines()
{
    int result = 0;
    // handle each line
    size_t length = strlen(lines[1]);
    
    printf("Line -1: %s\r\n", lines[0]);
    printf("Line  0: %s\r\n", lines[1]);
    printf("Line +1: %s\r\n", lines[2]);
    
    for (size_t i = 1; i < length; i++)
    {
        int offset = 0;
        bool symbolFound = false;
        while(isdigit(lines[1][i+offset]))
        {
            printf("Found number: %c \r\n",lines[1][i + offset]);
            
            //Look around
            for (int x = -1; (x <= 1) && (!symbolFound); x++)
            {
                for (int y = -1; (y <= 1) && (!symbolFound); y++)
                {
                    printf("Checking %c\r\n",lines[1+x][i + y + offset]);
                    if(lines[1+x][i + y + offset] != '.')
                    {
                        if(!isdigit(lines[1 + x][i + y + offset]))
                        {
                            //valid number
                            int value;
                            sscanf(&lines[1][i], "%d", &value);  
                            result += value;
                            symbolFound = true;
                            printf("Got Value: %d \r\n", value);
                        }
                    }
                }
            }
            offset++;
        }
        // skip to the next non-digit
        i += offset;       

    }
    return result;
}


int processFile(char * path)
{
    FILE *filePointer = fopen(path, "r");
    if (filePointer == NULL)
    {
        printf("Error reading file\r\n");
        exit(1);
    }

    printf("Running...\r\n");

    //initialise lines to '.'s
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < maxLineLength; j++)
        {
            lines[i][j] = '.';
        }
        lines[i][maxLineLength-1] = '\0';
    }
    
    //Overall result
    int result = 0;

    // get each line, read into the active index, offest by 1 so no symbols to the 'left'
    while (fgets(&lines[2][1], maxLineLength, filePointer))
    {
        result += processLines();

        //copy all the arrays to the previous lines
        strcpy(lines[0], lines[1]);
        strcpy(lines[1], lines[2]);
    }

    printf("Processing last line\r\n");
    // process the last line
    strcpy(lines[2], lines[1]);
    for (int i = 0; i < maxLineLength; i++)
    {
        lines[1][i] = '.';
    }
    
    result += processLines();

    fclose(filePointer);
    return result;
}


void test_1(void)
{
    // process the firstTest file
    int result = processFile("initialInput.txt");

    // Expected result is 8
    if(result == 4361)
    {
        printf("Test 1 passed\r\n");
    }
    else
    {
        printf("Test 1 failed, got:%d\r\n", result);
    }
}

int main(void)
{
    test_1();
    return 0;
}