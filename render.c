#include"render.h"

#include<stdlib.h>


#ifdef RTK_DEBUG
rtk_pixel_t* rtk_board_pixel_at(rtk_board_t *board,int x,int y)
{
    if(x>=0 && x<board->width && y>=0 && y<board->height)
    {
        return &board->image[y*board->width + x];
    }
    else
    {
        rtk_debug("image pixel position error,at (%d,%d)\n",x,y);
        return NULL;
    }
}
#endif

int rtk_borad_init(rtk_board_t *board,int width,int height)
{
    board->width=width;
    board->height=height;
    board->image=malloc(sizeof(board->image[0]) * width*height );
    if (board->image==NULL)
    {
        rtk_debug("board init error,memory alloc failed\n");
        return RTK_MEMORY_ERR;
    }
    return 0;
}