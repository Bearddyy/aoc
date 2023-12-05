#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

int processFile(char * path)
{
    FILE *filePointer = fopen(path, "r");
    if (filePointer == NULL)
    {
        printf("Error reading file\r\n");
        exit(1);
    }

    int result;
    size_t maxLineLength = 512;
    char line[maxLineLength];

    // Fetch first line with the seeds on it
    fgets(line, maxLineLength, filePointer);

    char * ignore = strtok(line, ":");

    char * seedsStringList = strtok(NULL, ":");
    
    unsigned long seeds[512] = {0};
    size_t seedIndex = 0;
    char * seedNumber = strtok_r(seedsStringList, " ", &seedsStringList);
    
    //printf("Processing Winning Numbers \r\n");
    while (seedNumber != NULL)
    {
        seeds[seedIndex] = (unsigned long)atol(seedNumber);
        seedNumber = strtok_r(seedsStringList, " ", &seedsStringList);
        seedIndex++;
    }
    
    printf("Starting Seeds: [");
    for (size_t i = 0; i < seedIndex; i++)
    {
        printf("%lu,", seeds[i]);
    }
    printf("]\r\n");

    bool done = false;
    // get each line after the seeds
    while (fgets(line, maxLineLength, filePointer))
    {
        if(isalpha(line[0]) != 0)
        {

            bool endOfMap = false;
            
            long destination[512] = {0};
            long source[512] = {0};
            long length[512] = {0};
            size_t mapEntries = 0;

            while(fgets(line, maxLineLength, filePointer))
            {
                if(isdigit(line[0]) == 0)
                {
                    //printf("got line: %c \r\n", line[0]);
                    break;
                }

                destination[mapEntries] = atol(strtok(line, " "));
                source[mapEntries] = atol(strtok(NULL, " "));
                length[mapEntries] = atol(strtok(NULL, " "));

                mapEntries++;
            }
            for (size_t j = 0; j < seedIndex; j++)
            {
                for (size_t i = 0; i < mapEntries; i++)
                {
                    if(seeds[j] >= source[i])
                    {
                        if(seeds[j] < (source[i] + length[i]))
                        {
                            seeds[j] = (seeds[j] - source[i]) + destination[i];
                            break;
                        }
                    }
                }
            }
        }
    }

    unsigned long minSeed = seeds[0];

    printf("Final Seeds: [");
    for (size_t i = 0; i < seedIndex; i++)
    {
        
        printf("%lu,", seeds[i]);
        if (seeds[i] < minSeed)
        {
            minSeed = seeds[i];
        }
    }
    printf("]\r\n");

    printf("Found min seed: %lu\r\n", minSeed);
    
    fclose(filePointer);
    return minSeed;
}

void test_1()
{
    int result = processFile("initialTest.txt");
    
    if (result != 35)
    {
        printf("Test 1 failed, result: %d\r\n", result);
    }
    else
    {
        printf("Test 1 passed\r\n");
    }
}

void test_2()
{
    int result = processFile("puzzleInput.txt");
    
    if (result != 35)
    {
        printf("Test 2 failed, result: %ld\r\n", result);
    }
    else
    {
        printf("Test 2 passed\r\n");
    }
}

int main(void)
{
    test_1();
    test_2();
    return 0;
}