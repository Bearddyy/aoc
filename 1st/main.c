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

// accepts a line of text, returns the first and last digits combined
int process_line(size_t length, char * text)
{
    int left = length;
    int right = 0;
    char character;
    for(size_t i = 0; i < length; i++)
    {
        character = text[i];
        if(isdigit(character))
        {
            if(i < left)
            {
                left = i;
            }
            if(i > right)
            {
                right = i;
            }
        }
    }
    int result = ((text[left] - '0') * 10) + (text[right] - '0');
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
    printf("Test 1:%d\r\n", result);

    char testString2[] = "pqr3stu8vwx";
    result = test_process_line(testString2, 38);
    printf("Test 2:%d\r\n", result);


    char testString3[] = "a1b2c3d4e5f";
    result = test_process_line(testString3, 15);
    printf("Test 3:%d\r\n", result);

    char testString4[] = "treb7uchet";
    result = test_process_line(testString4, 77);
    printf("Test 4:%d\r\n", result);
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
        result += process_line(length,line);
    }
    fclose(filePointer);
    return result;
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

int main(void)
{
    test_1();
    test_2();
    return 0;
}