#ifndef RENDER_H
#define RENDER_H

#include<stdint.h>
#include<stdbool.h>

#include"container.h"
#include"vector.h"

// 统一初始化结构体
struct rtk_init_t
{
    int width;
    int height;
    double width_scale;
    double height_scale;
    char *name;
    
};
typedef struct rtk_init_t rtk_init_t;

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
    bool disable;
    rtk_pixel_t *image;
};
typedef struct rtk_board_t rtk_board_t;

struct rtk_layer_t
{
    rtk_board_t board;
    vector containers;
};
typedef struct rtk_layer_t rtk_layer_t;

int rtk_layer_init(rtk_layer_t *layer,int width,int height);

#ifdef RTK_DEBUG
extern rtk_pixel_t* rtk_board_pixel_at(rtk_board_t *board,int x,int y);
#else
static inline rtk_pixel_t* rtk_board_pixel_at(rtk_board_t *board,int x,int y)
{
        return &board->image[y*board->width + x];
}
#endif

struct rtk_render_t
{
    rtk_board_t view;
    vector layers;
    vector view_stack;
};
typedef struct rtk_render_t rtk_render_t;

int rtk_render_init(rtk_render_t *render,int width,int height);

#endif