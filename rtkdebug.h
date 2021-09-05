#ifndef RTKDEBUG_H
#define RTKDEBUG_H

#include<stdio.h>
#include<stdbool.h>

// 如果定义了调试选项，那么rtk的调试项也应该开启
#if defined(DEBUG) || defined(_DEBUG)
#ifndef RTK_DEBUG
#define RTK_DEBUG
#endif
#endif


// rtk相关的调试项
#ifdef  RTK_DEBUG
#define rtk_debug(format,...) fprintf(stderr,"[file:%s][line:%d]"format,__FILE__,__LINE__,##__VA_ARGS__)
#define rtk_assert(condition) ({ if((condition)==false) {rtk_debug("assert error :%s\n",#condition);exit(1);} })
#elif
#define rtk_debug(format,...) ()
#define rtk_assert() ()
#endif



enum rtk_error_code
{
    RTK_SUCCESS=0,
    RTK_MEMORY_ERR,

};



#endif