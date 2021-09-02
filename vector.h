#ifndef VECTOR_H
#define VECTOR_H

#include<stdlib.h>
#include<string.h>
#include<stddef.h>

//data structure of vector
typedef void* rtk_generic_t;

struct vector
{
    ssize_t size;
    ssize_t capacity;
    rtk_generic_t *a;
};
typedef struct vector vector;

//vector information
static inline ssize_t vector_size(vector *v)
{
    return v->size;
}

static inline ssize_t vector_capacity(vector *v)
{
    return v->capacity;
}

//resource management

static void vector_recapacity(vector *v,ssize_t new_cap)
{
    ssize_t cap=vector_capacity(v);
    ssize_t size=vector_size(v);
    //only when new_cap>cap can change capacity
    if(new_cap>cap)
    {
        rtk_generic_t *p=(rtk_generic_t*)malloc(new_cap*sizeof(rtk_generic_t));
        //add exception
        if(p==NULL)
        {
            rtk_debug("vector memory alloc failed\n");
            exit(1);
        }
        memcpy(p,v->a,size*sizeof(rtk_generic_t));
        free(v->a);
        v->capacity=new_cap;
        v->a=p;
    }
}

static void vector_resize(vector *v,ssize_t new_size)
{
    ssize_t size=vector_size(v);
    if(size<new_size)
    {
        ssize_t cap=vector_capacity(v);
        if(new_size<=cap)
            v->size=new_size;
        else
        {
            vector_recapacity(v,new_size);
            v->size=new_size;
        }
    }
}

static inline void vector_fit(vector *v)
{
    vector_recapacity(v,vector_size(v));
}

//vector interface
//初始化函数 等价于 vector v={};
static inline vector* vector_init(vector *v)
{
    v->size=0;
    v->capacity=0;
    v->a=NULL;
    return v;
}

static void vector_del(vector *v)
{
    v->size=0;
    v->capacity=0;
    free(v->a);
    v->a=NULL;
}

static inline void vector_clear(vector *v)
{
    v->size=0;
}

//using
static inline void vector_push_back(vector *v,rtk_generic_t e)
{
    ssize_t size=vector_size(v);
    ssize_t cap =vector_capacity(v);
    if(size==cap)
        vector_recapacity(v,cap+cap/2+1);
    v->a[v->size++]=e;
}

static inline void vector_pop_back(vector *v)
{
    if(v->size>0)
        v->size--;
}

static inline rtk_generic_t* vector_at(vector *v,ssize_t index)
{
    rtk_assert(index>=0 && index<vector_size(v));

    return &v->a[index];
}

static inline void vector_insert(vector *v,ssize_t index,rtk_generic_t e)
{
    rtk_assert(index>=0 && index<vector_size(v));

    vector_push_back(v,*vector_at(v,index));
    for(ssize_t i=vector_size(v)-2;i>=index;i--)
        *vector_at(v,i)=*vector_at(v,i+1);
}

static inline void vector_erase(vector *v,ssize_t index)
{
    rtk_assert(index>=0 && index<vector_size(v));

    for(ssize_t i=index;i<vector_size(v)-1;i++)
        *vector_at(v,i)=*vector_at(v,i+1);
    vector_pop_back(v);
}

static inline rtk_generic_t* vector_back(vector *v)
{
    return vector_at(v,vector_size(v)-1);
}

static inline rtk_generic_t* vector_front(vector *v)
{
    return vector_at(v,0);
}

static inline rtk_generic_t* vector_begin(vector *v)
{
    return &v->a[0];
}

static inline rtk_generic_t* vector_end(vector *v)
{
    return &v->a[vector_size(v)];
}

static inline rtk_generic_t* vector_data(vector *v)
{
    return vector_begin(v);
}

// 拷贝赋值
static inline void vector_assign(vector *t,vector *v)
{
    vector_del(t);
    vector_resize(t,vector_size(v));
    memcpy(vector_data(t),vector_data(v),vector_size(t)*sizeof(rtk_generic_t));
}
 
// 拷贝赋值
static inline void vector_copy(vector *t,vector *v)
{
    vector_assign(t,v);
}

// 移动赋值
static inline void vector_move(vector *t,vector *v)
{
    *t=*v;
}

#endif