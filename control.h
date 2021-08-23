#ifndef CONTROL_H
#define CONTROL_H



struct rtk_control_t
{
    const char *type_name;
    const char *name;
    const char *event_name[5];
    int (*respond)(const char *event_name);
};
typedef struct rtk_control_t rtk_control_t;

struct rtk_control_attr_t
{
    const char *name;
    
};
typedef struct rtk_control_attr_t rtk_control_attr_t;
int rtk_control_init(rtk_control_t *control,rtk_control_attr_t attr)
{
    control->type_name="rtk_control_t";
    control->name=(attr.name==NULL)?"":attr.name;
    //control->respond=(attr.re)
    return 0;
}
#endif