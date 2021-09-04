#ifndef CONTAINER_H
#define CONTAINER_H

#include"control.h"

typedef struct rtk_layer_t rtk_layer_t;
//typedef struct rtk_control_t rtk_control_t;

//容器的基类
struct rtk_container_t
{
    int place_x;
    int place_y;
    int width;
    int height;
    rtk_layer_t   *master;
    rtk_control_t *control;
};
typedef struct rtk_container_t rtk_container_t;

#endif