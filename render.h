#ifndef RENDER_H
#define RENDER_H

#include<stdint.h>
#include<stdbool.h>

#include"container.h"

struct rtk_color_t
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
};
typedef struct rtk_color_t rtk_color_t;

struct rtk_color_attr_t
{
    uint8_t writable:1;
    uint8_t transparent:1;
    //reserver
};
typedef struct rtk_color_attr_t rtk_color_attr_t;

struct rtk_pixel_t
{
    rtk_color_t color;
    rtk_color_attr_t attr;
};
typedef struct rtk_pixel_t rtk_pixel_t;

//attr各个位的表示
// 7-2:预留
// 1:像素是否透明，1代表透明，0代表有颜色
// 0:写入使能位，0代表可写入，1代表不可变

static inline bool rtk_is_pixel_writable(rtk_pixel_t p)
{
    return p.attr.writable==0;
}

static inline bool rtk_is_pixel_transparent(rtk_pixel_t p)
{
    return p.attr.transparent==1;
}

struct rtk_board_t
{
    int width;
    int height;
    rtk_pixel_t *image;
};
typedef struct rtk_board_t rtk_board_t;

struct rtk_layer_t
{
    rtk_board_t board;
    rtk_container_t *list;
};
typedef struct rtk_layer_t rtk_layer_t;


#ifdef RTK_DEBUG
extern rtk_pixel_t* rtk_board_pixel_at(rtk_board_t *board,int x,int y);
#else
static inline rtk_pixel_t* rtk_board_pixel_at(rtk_board_t *board,int x,int y)
{
        return &board->image[y*board->width + x];
}
#endif


#endif