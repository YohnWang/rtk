#include"acllib.h"
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<time.h>

enum 
{
    width=360,
    height=210
};

void time_call(int id)
{
    static clock_t start=0;
    static int offset=0;
    beginPaint();
    clearDevice();
    int s=1;
    int t=rand()%2;
    for(int y=0;y<300;y++)
        for(int x=0;x<400;x++)
        {
            if(sin(0.1*(x-offset))+sin(0.1*(y))<0.01)
            {
                uint8_t c=rand()%255;
                
                //putPixel(x,y,RGB(rand()%255,rand()%255,rand()%255));
                if(s==0)
                    putPixel(x,y,RGB(255,0,0));
                else if(s==1)
                    putPixel(x,y,RGB(0,255,0));
                else
                    putPixel(x,y,RGB(0,0,255));
            }
            
        }
    endPaint();
    if(t)
        offset-=1;
    else 
        offset+=1;
    printf("time=%d\n",clock()-start);
    start=clock();
}

int Setup()
{
    initWindow("fuck",-1,-1,190*2,120*2);
    registerTimerEvent(time_call);
    startTimer(1,30);CLOCKS_PER_SEC;
    
    return 0;
}
