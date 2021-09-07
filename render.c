#include"render.h"

#include<stdlib.h>


static int rtk_borad_init(rtk_board_t *board,int width,int height)
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

int rtk_layer_init(rtk_layer_t *layer,int width,int height)
{
    int ret=rtk_borad_init(&layer->board,width,height);
    vector_init(&layer->containers);
    return ret;
}

int rtk_render_init(rtk_render_t *render,int width,int height)
{
    rtk_assert(width>=0 && height>=0);

    int ret=rtk_borad_init(&render->view,width,height);
    vector_init(&render->layers);
    vector_init(&render->view_stack);
    return ret;
}

void rtk_render(rtk_render_t *render)
{
    
}