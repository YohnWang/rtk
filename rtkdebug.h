#ifndef RTKDEBUG_H
#define RTKDEBUG_H

#include<stdio.h>

#ifndef rtk_debug
#define rtk_debug(format,...) fprintf(stderr,"[file:%s][line:%d]"format,__FILE__,__LINE__,##__VA_ARGS__);
#endif

enum rtk_error_code
{
    RTK_SUCCESS=0,
    RTK_MEMORY_ERR,

};



#endif