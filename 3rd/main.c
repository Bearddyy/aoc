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
    
     printf("\r\n\r\n\r\n\r\n");
    printf("Line -1: %s\r\n", lines[0]);
    printf("Line  0: %s\r\n", lines[1]);
    printf("Line +1: %s\r\n", lines[2]);
    
    for (size_t i = 1; i < length; i++)
    {
        int offset = 0;
        bool symbolFound = false;
        if(lines[1][i] == '*')
        {
            int digitsFound = 0;
            int ratio = 0;
            printf("Found *: %c \r\n",lines[1][i]);
            
            //Look around
            for (int x = -1; (x <= 1); x++)
            {
                for (int y = -1; (y <= 1); y++)
                {
                    printf("Checking %c\r\n",lines[1+x][i + y]);
                    if(isdigit(lines[1+x][i + y]))
                    {
                        printf("Found digit: %c\r\n",lines[1+x][i + y]);
                        digitsFound++;
                        if(digitsFound <= 2)
                        {
                            printf("Found a digit: %c\r\n",lines[1+x][i + y]);
                            //Walk back to the start of the number
                            int offset = 0;
                            while(isdigit(lines[1+x][i + y + offset]))
                            {
                                offset--;
                            }
                            offset++;
                            //Get the number
                            int value;
                            sscanf(&lines[1+x][i + y + offset], "%d", &value);
                            if(ratio == 0)
                            {
                                ratio = value;
                            }
                            else
                            {
                                printf("Multiplying %d by %d\r\n", ratio, value);
                                ratio *= value;
                            }
                            //skip to the end of the number
                            while(isdigit(lines[1+x][i + y + 1]))
                            {
                                y++;
                            }
                        }
                        
                        
                    }
                }
            }
            if(digitsFound == 2)
            {
                result += ratio;
            }
        }
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
        printf("Result: %d\r\n", result);

        //copy all the arrays to the previous lines
        strcpy(lines[0], lines[1]);
        strcpy(lines[1], lines[2]);
    }

    //printf("Processing last line\r\n");
    // process the last line
    strcpy(lines[2], lines[1]);
    for (int i = 0; i < maxLineLength; i++)
    {
        lines[2][i] = '.';
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
    if(result == 467835)
    {
        printf("Test 1 passed\r\n");
    }
    else
    {
        printf("Test 1 failed, got:%d\r\n", result);
    }
}

void test_2(void)
{
    // process the firstTest file
    int result = processFile("puzzleInput.txt");

    
    printf("Test 2 got: %d\r\n", result);

}

int main(void)
{
    //test_1();
    test_2();
    return 0;
}