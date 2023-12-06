#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>


int race(int totalTime, int recordTime)
{
    int waysToWin = 0;
    for (size_t holdTime = 0; holdTime < totalTime; holdTime++)
    {
        int timeForRace = (holdTime * (totalTime-holdTime));
        if (timeForRace > recordTime)
        {
            waysToWin++;
        }
        
    }
    return waysToWin;
}

int main(void)
{
    int raceTimes[] = {42,68,69,85};
    int recordTimes[] = {284, 1005, 1122, 1341};
    int total = 1;
    for (size_t i = 0; i < 4; i++)
    {
        int result = race(raceTimes[i], recordTimes[i]);
        total *= result;
        printf("Race 1: %d \r\n", result);
    }
    printf("Got: %d\r\n", total);
    
    return 0;
}