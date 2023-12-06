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
    return waysToWin
}

int main(void)
{
    int raceTimes[] = {7,15,30};
    int recordTimes[] 
    return 0;
}