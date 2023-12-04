#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>



// accepts a line of text and the totals of red green blue
int process_line(size_t length, char * text)
{
    // Game string
    char * gameString = strtok(text, ":");
    // Fetch remainder of the game
    char * gameScores = strtok(NULL, ":");

    char * winningNumbers = strtok(gameScores, "|");
    char * numbersGuessed = strtok(NULL, "|");

    
    char * winningNumber = strtok_r(winningNumbers, " ", &winningNumbers);
    // Parse the winning numbers

    int winningNumbers_i[512] = {0};
    size_t totalWinningNumbers = 0;
    
    printf("Processing Winning Numbers \r\n");
    while (winningNumber != NULL)
    {
        sscanf(winningNumber, "%d", &winningNumbers_i[totalWinningNumbers]);
        totalWinningNumbers++;
        winningNumber = strtok_r(winningNumbers, " ", &winningNumbers);
    }    

    char * guessedNumber_s = strtok_r(numbersGuessed, " ", &numbersGuessed);
    int winnings = 0;
    int guessedNumber_i = 0;
    // Parse the guessed numbers
    while (guessedNumber_s != NULL)
    {
        sscanf(guessedNumber_s, "%d", &guessedNumber_i);

        for (size_t i = 0; i < totalWinningNumbers; i++)
        {
            if(guessedNumber_i == winningNumbers_i[i])
            {
                if(winnings == 0)
                {
                    winnings = 1;
                }
                else
                {
                    winnings = winnings*2;
                }
            }
        }
        guessedNumber_s = strtok_r(numbersGuessed, " ", &numbersGuessed);
    }
    return winnings;
}

int processFile(char * path)
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
        printf("result:%d\r\n", temp);
    }
    fclose(filePointer);
    return result;
}

void test_1()
{
    int result = processFile("testCase.txt");
    
    if (result != 13)
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
    
    if (result != 13)
    {
        printf("Test 1 failed, result: %d\r\n", result);
    }
    else
    {
        printf("Test 1 passed\r\n");
    }
}


int main(void)
{
    test_1();
    test_2();
    return 0;
}