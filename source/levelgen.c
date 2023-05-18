#include <citro2d.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <3ds.h>
#include <time.h>
#include "variables.h"


int level[300];
int start = 11;
void level_generator(){
    for (int i = 0; i < start; i++)
    {
        level[i]=1;
    }
    printf("%d ",rand());
    for(int filled=start+1;filled < 300-start;filled++){
        level[filled] = rand() % 9 + 2;
    }
    //print level
    for (int arr = 0; arr < 300; arr++ ) 
    {
        printf("%d ", level[arr]);
    }
}