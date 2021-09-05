#include"acllib.h"
#include<stdlib.h>
#include<stdint.h>
#include<math.h>
#include<time.h>

#include"render.h"
#include"timer.h"

rtk_layer_t layer;

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
    for(int y=0;y<200;y++)
        for(int x=0;x<300;x++)
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
    //printf("time=%ld\n",clock()-start);
    start=clock();
}
// #include"gvector.h"

// vector_generic(vector(int))
// vector_func_register(int)

int Setup()
{

    rtk_timer_init();
    int i=0;
    int print1()
    {
        static int i=0;
        printf("fuck you %d\n",i++);
        return 0;
    }
    int print2()
    {
        static int i=0;
        printf("shit you %d\n",i++);
        if(i>3)
            return 0;
        return 1;
    }
    for(int i=0;i<100;i++)
        rtk_timer_register(print1,1000*(rand()%100));
    
    // for(;;)
    // {
    //     i++;
    //     Sleep(500);
    // }
    initWindow("fuck",-1,-1,300,200);
    rtk_layer_init(&layer,200,100);
    registerTimerEvent(time_call);
    startTimer(1,20);CLOCKS_PER_SEC;
    
    return 0;
}