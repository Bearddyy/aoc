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
    
    //printf("Processing Winning Numbers \r\n");
    while (winningNumber != NULL)
    {
        sscanf(winningNumber, "%d", &winningNumbers_i[totalWinningNumbers]);
        totalWinningNumbers++;
        winningNumber = strtok_r(winningNumbers, " ", &winningNumbers);
    }    

    char * guessedNumber_s = strtok_r(numbersGuessed, " ", &numbersGuessed);
    int numverOfWinningNumbers = 0;
    int guessedNumber_i = 0;
    // Parse the guessed numbers
    while (guessedNumber_s != NULL)
    {
        sscanf(guessedNumber_s, "%d", &guessedNumber_i);

        for (size_t i = 0; i < totalWinningNumbers; i++)
        {
            if(guessedNumber_i == winningNumbers_i[i])
            {
                numverOfWinningNumbers++;
            }
        }
        guessedNumber_s = strtok_r(numbersGuessed, " ", &numbersGuessed);
    }
    return numverOfWinningNumbers;
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

    int numberOfCardsEarned[512] = {0};
    for (size_t i = 0; i < 512; i++)
    {
        numberOfCardsEarned[i] = 1;
    }
    
    size_t currentCard = 1;
    int totalCards = 0;
    // get each line
    while (fgets(line, maxLineLength, filePointer))
    {
        // handle each line
        size_t length = strlen(line);
        if(numberOfCardsEarned[currentCard] > 0)
        {
            int numberOfWiningCards = process_line(length, line);
            
            for (size_t i = currentCard + 1; i <= (numberOfWiningCards + currentCard); i++)
            {
                numberOfCardsEarned[i] += (1 * numberOfCardsEarned[currentCard]);
            }
            totalCards += numberOfCardsEarned[currentCard];
            
            //printf("Line [%d] won:%d cards, had:%d so now total:%d\r\n", currentCard, numberOfWiningCards, numberOfCardsEarned[currentCard], totalCards);
            currentCard++;
        }
        else
        {
            break;
        }
        
    }

    // Count the total
    fclose(filePointer);
    return totalCards;
}

void test_1()
{
    int result = processFile("testp2.txt");
    
    if (result != 30)
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