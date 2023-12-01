#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

//1abc2
//pqr3stu8vwx
//a1b2c3d4e5f
//treb7uchet

static const char* stringNumbers[] = {
    "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
static const size_t stringNumbersLength = 10;

// accepts a line of text, returns the first and last digits combined
int process_line(size_t length, char * text)
{
    // Unclear if we need to handle if there are no numbers in the line
    // So will just return 0 if there are no numbers
    int left = 0;
    int right = 0;
    bool leftFound = false;

    for(size_t i = 0; i < length; i++)
    {
        if(isdigit(text[i]))
        {
            if (!leftFound) // We have not found left yet
            {
                //We have found left
                left = text[i] - '0';
                leftFound = true;
            }
            // always update right
            right = text[i] - '0';
        }
        else //It cant be a number, so check if it is a string number
        {
            // check if there is at least the minimum length left
            // This avoids checking the last few characters, will be slightly slower on very long lines
            // but will be faster on short lines
            int remaining = length - i;
            if(remaining >= (strlen(stringNumbers[1])-1)) // -1 as we dont need to check the null
            {
                // Starting at j = 1 as challenge didnt state zero
                for (size_t j = 1; j < stringNumbersLength; j++)
                {
                    size_t currentLength = strlen(stringNumbers[j]) - 1; 
                    if(currentLength <= remaining) // Protect against reading over end
                    {
                        if(0 == strncmp(&text[i], stringNumbers[j], currentLength))
                        {
                            if (!leftFound) // We have not found left yet
                            {
                                //We have found left, so we can set right too
                                left = j;
                                leftFound = true;
                            }
                            // always update right
                            right = j;
                        }
                    }
                }
            }
        }
    }
    int result = (left * 10) + right;
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

    size_t maxLineLength = 512;
    char line[maxLineLength];

    //Overall result
    int result = 0;

    // get each line
    while (fgets(line, maxLineLength, filePointer))
    {
        // handle each line
        size_t length = strlen(line);
        int temp = process_line(length,line);
        result += temp;
        //printf("result:%d\r\n", temp);
    }
    fclose(filePointer);
    return result;
}


bool test_process_line(char * nullTermString, int expected)
{
    size_t length = strlen(nullTermString);
    int result = process_line(length, nullTermString);
    if(result != expected)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void test_1(void)
{
    char testString1[] = "1abc2";
    bool result = test_process_line(testString1, 12);
    printf("Test 1.1:%d\r\n", result);

    char testString2[] = "pqr3stu8vwx";
    result = test_process_line(testString2, 38);
    printf("Test 1.2:%d\r\n", result);


    char testString3[] = "a1b2c3d4e5f";
    result = test_process_line(testString3, 15);
    printf("Test 1.3:%d\r\n", result);

    char testString4[] = "treb7uchet";
    result = test_process_line(testString4, 77);
    printf("Test 1.4:%d\r\n", result);
}

void test_2(void)
{
    int result = processFile("testFile1.txt");
    if(result != 142)
    {
        printf("Failed test 2 with result:%d\r\n", result);
        exit(1);
    }
    else
    {
        printf("Passed test 2\r\n");
    }
}

void test_challenge_file(void)
{
    int result = processFile("challengeFile.txt");
    int expected = 54094;
    if(result != expected)
    {
        printf("Failed test with example file, got:%d != %d\r\n", result, expected);
        exit(1);
    }
    else
    {
        printf("Passed with challenge file\r\n");
    }
}

void test_3(void)
{
    int result = processFile("seccondHalfFile.txt");
    if(result != 281)
    {
        printf("Failed test 3 with result:%d\r\n", result);
        exit(1);
    }
    else
    {
        printf("Passed test 3\r\n");
    }
}

void test_4(void)
{
    char testString[] = "eighthree";
    int result = test_process_line(testString, 83);
    printf("Test 4.1:%d\r\n", result);
    
    char testString2[] = "sevenine";
    result = test_process_line(testString2, 79);
    printf("Test 4.2:%d\r\n", result);

    char testString3[] = "9g";
    result = test_process_line(testString3, 99);
    printf("Test 4.3:%d\r\n", result);
}

int main(void)
{
    test_1();
    test_2();
    test_3();
    test_4();

    // Test with the challenge file
    test_challenge_file();
    return 0;
}