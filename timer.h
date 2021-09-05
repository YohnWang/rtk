#ifndef RTK_TIMER_H
#define RTK_TIMER_H

#include<stdint.h>
#include<time.h>
#include<windows.h>

typedef int32_t rtk_clock_t;

// 移植接口 -- begin

static inline rtk_clock_t rtk_get_clock(void)
{
    return clock();
}

static inline void rtk_timer_sleep(rtk_clock_t waiting_time)
{
    Sleep(waiting_time);
}

// 移植接口 -- end

struct rtk_timer_t
{
    rtk_clock_t executable_time;
    rtk_clock_t waiting_time;
    int (*timer_call)(void);
};
typedef struct rtk_timer_t rtk_timer_t;

void rtk_timer_register(int (*timer_call)(void), rtk_clock_t waiting_time);
void rtk_timer_init(void);

#endif