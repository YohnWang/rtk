#include"control.h"

static int control_respond(const char *event_name)
{
    return 0;
}

int rtk_control_init(rtk_control_t *control,rtk_control_attr_t attr)
{
    control->type_name="rtk_control_t";
    control->name=(attr.name==NULL)?"":attr.name;
    vector_init(&control->event_list);
    control->respond=control_respond;
    return 0;
}

