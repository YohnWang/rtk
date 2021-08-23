#ifndef VECTOR_H
#define VECTOR_H

#include<stdlib.h>
#include<string.h>

//data structure of vector
typedef void* rtk_generic_t;

struct vector
{
    int size;
    int capacity;
    rtk_generic_t *a;
};
typedef struct vector vector;

//vector information
static inline int vector_size(vector *v)
{
    return v->size;
}

static inline int vector_capacity(vector *v)
{
    return v->capacity;
}

//resource management

static void vector_recapacity(vector *v,int new_cap)
{
    //static int count=0;
    //printf("call %d\n",++count);
    int cap=vector_capacity(v);
    int size=vector_size(v);
    //only when new_cap>cap can change capacity
    if(new_cap>cap)
    {
        rtk_generic_t *p=(rtk_generic_t*)malloc(new_cap*sizeof(rtk_generic_t));
        //add exception
        memcpy(p,v->a,size*sizeof(rtk_generic_t));
        free(v->a);
        v->capacity=new_cap;
        v->a=p;
    }
}

static void vector_resize(vector *v,int new_size)
{
    int size=vector_size(v);
    if(size<new_size)
    {
        int cap=vector_capacity(v);
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
    int size=vector_size(v);
    int cap =vector_capacity(v);
    if(size==cap)
        vector_recapacity(v,cap+cap/2+1);
    v->a[v->size++]=e;
}

static inline void vector_pop_back(vector *v)
{
    if(v->size!=0)
        v->size--;
}

static inline rtk_generic_t* vector_at(vector *v,int position)
{
    return &v->a[position];
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

static inline void vector_assign(vector *t,vector *v)
{
    vector_del(t);
    vector_resize(t,vector_size(v));
    memcpy(vector_data(t),vector_data(v),vector_size(t)*sizeof(rtk_generic_t));
}
#endif