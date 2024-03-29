#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


#define colourStartDefault 3

// accepts a line of text and the totals of red green blue
int process_line(size_t length, char * text)
{
    int  min_red = 0;
    int  min_green = 0;
    int  min_blue = 0;
    char * gameString = strtok(text, ":");
    int gameNumber = 0;
    sscanf(&gameString[5], "%d", &gameNumber);
    printf("Game %d\r\n", gameNumber);

    char * gameLog = strtok(NULL, ":");

    char * remainingRounds = gameLog;
    char * round = strtok_r(gameLog, ";", &remainingRounds);
    
    int i = 0;
    while (round != NULL)
    {
        //printf("Round: [%d] : ",i);

        // Parse each draw
        char * remainingDraws = round;
        char * draw = strtok_r(round, ",", &remainingDraws);

        while (draw != NULL)
        {
            //printf("draw: %s \r\n", draw);
            int colourStart = colourStartDefault;
            // 3 blue
            int number = 0;
            sscanf(draw, "%d", &number);
            printf("number: %d \r\n", number);
            
            // offset for colour start by number of digits in number, lazy way of doing it for now
            if(number > 9)
            {
                colourStart++;
            }
            if(number > 99)
            {
                colourStart++;
            }
            
            // If the number of drawn is greater than the combinations passed in, game is invalid and return.
            switch (draw[colourStart])
            {
            case 'r':
                if(number > min_red)
                {
                    min_red = number;
                }
                break;
            case 'g':
                if(number > min_green)
                {
                    min_green = number;
                }
                break;
            case 'b':
                if(number > min_blue)
                {
                    min_blue = number;
                }
                break;        
            default:
                printf("Got unknown letter %c\r\n",draw[colourStart] );
                exit(0);
                break;
            }

            draw = strtok_r(remainingDraws, ",", &remainingDraws);
        }
        
        //printf("\r\n");

        round = strtok_r(remainingRounds, ";", &remainingRounds);        
        i++;
    }

    
    return min_red * min_blue * min_green;
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


void test_1(void)
{
    // process the firstTest file
    int result = processFile("firstTest.txt", 12, 13, 14);

    // Expected result is 8
    if(result == 8)
    {
        printf("Test 1 passed\r\n");
    }
    else
    {
        printf("Test 1 failed\r\n");
    }
}


void test_2(void)
{
    // process the firstTest file
    int result = processFile("firstProblemFile.txt", 12, 13, 14);

    printf("Test 2 Result: %d", result);
}


int main(void)
{
    test_1();
    test_2();
    return 0;
}