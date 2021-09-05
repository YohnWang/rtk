#include<stdlib.h>
#include<string.h>
#include<stddef.h>
#include<pthread.h>

#include"timer.h"

// 数据结构 动态数组 -- beign

struct vector
{
    ssize_t size;
    ssize_t capacity;
    rtk_timer_t *a;
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
        rtk_timer_t *p=(rtk_timer_t*)malloc(new_cap*sizeof(rtk_timer_t));
        if(p==NULL)
        {
            rtk_debug("vector memory alloc failed\n");
            exit(1);
        }
        memcpy(p,v->a,size*sizeof(rtk_timer_t));
        free(v->a);
        v->capacity=new_cap;
        v->a=p;
    }
    else
    {
        rtk_debug("vector capacity is bigger than this new capacity\n");
    }
}

static void vector_resize(vector *v,ssize_t new_size)
{
    ssize_t size=vector_size(v);
    if(size<new_size)
    {
        ssize_t cap=vector_capacity(v);
        if(new_size<=cap)
        {
            v->size=new_size;
        }
        else
        {
            vector_recapacity(v,new_size);
            v->size=new_size;
        }
    }
}
static inline void vector_assign(vector *t,vector *v);
static inline void vector_move(vector *t,vector *v);
static void vector_init(vector *v);
static void vector_del(vector *v);
static inline void vector_fit(vector *v)
{
    vector t;
    vector_init(&t);
    vector_assign(&t,v);
    vector_move(v,&t);
    vector_del(&t);
}

//vector interface
//初始化函数 等价于 vector v={};
static void vector_init(vector *v)
{
    v->size=0;
    v->capacity=0;
    v->a=NULL;
}

static void vector_del(vector *v)
{
    free(v->a);
    vector_init(v);
}

static inline void vector_clear(vector *v)
{
    v->size=0;
}

//using
static inline void vector_push_back(vector *v,rtk_timer_t e)
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

static inline rtk_timer_t* vector_at(vector *v,ssize_t index)
{
    rtk_assert(index>=0 && index<vector_size(v));

    return &v->a[index];
}

static inline void vector_insert(vector *v,ssize_t index,rtk_timer_t e)
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

static inline rtk_timer_t* vector_back(vector *v)
{
    return vector_at(v,vector_size(v)-1);
}

static inline rtk_timer_t* vector_front(vector *v)
{
    return vector_at(v,0);
}

static inline rtk_timer_t* vector_begin(vector *v)
{
    return &v->a[0];
}

static inline rtk_timer_t* vector_end(vector *v)
{
    return &v->a[vector_size(v)];
}

static inline rtk_timer_t* vector_data(vector *v)
{
    return vector_begin(v);
}

// 拷贝赋值
static inline void vector_assign(vector *t,vector *v)
{
    vector_del(t);
    vector_resize(t,vector_size(v));
    memcpy(vector_data(t),vector_data(v),vector_size(t)*sizeof(rtk_timer_t));
}

// 拷贝赋值
static inline void vector_copy(vector *t,vector *v)
{
    vector_assign(t,v);
}

// 移动赋值
static inline void vector_move(vector *t,vector *v)
{
    vector p=*t;
    *t=*v;
    *v=p;
}

// 数据结构 动态数组 -- end

// 数据结构 最小堆 -- begin

static inline ssize_t left(ssize_t i)
{
    return (i+1)*2-1;
}

static inline ssize_t right(ssize_t i)
{
    return (i+1)*2;
}

static inline ssize_t parent(ssize_t i)
{
    return (i-1)/2;
}

static void heapify(rtk_timer_t a[],ssize_t n,ssize_t i)
{
    ssize_t l=left(i);
    ssize_t r=right(i);
    ssize_t smallest=i;
    if(l<n && a[smallest].executable_time>a[l].executable_time)
        smallest=l;
    if(r<n && a[smallest].executable_time>a[r].executable_time)
        smallest=r;
    if(smallest!=i)
    {
        rtk_timer_t tmp=a[i];
        a[i]=a[smallest];
        a[smallest]=tmp;
        heapify(a,n,smallest);
    }
}

static void push_heap(rtk_timer_t a[],ssize_t n,ssize_t i)
{
    for(ssize_t j=parent(i);j<i;j=parent(i))
    {
        if(a[i].executable_time<a[j].executable_time)
        {
            rtk_timer_t r=a[j];
            a[j]=a[i];
            a[i]=r;
            i=j;
        }
        else 
        {
            break;
        }
    }
}

static void pop_heap(rtk_timer_t a[],ssize_t n,ssize_t i)
{
    rtk_timer_t r=a[0];
    a[0]=a[n-1];
    heapify(a,n-1,0);
    a[n-1]=r;
}

// 数据结构 最小堆 -- end


// 移植接口 -- begin
static pthread_mutex_t mutex= PTHREAD_MUTEX_INITIALIZER;

static inline void rtk_timer_critical_in(void)
{
    pthread_mutex_lock(&mutex);
}

static inline void rtk_timer_critical_out(void)
{
    pthread_mutex_unlock(&mutex);
}

// 移植接口 -- end

static vector timer_list={};
void rtk_timer_register(int (*timer_call)(void), rtk_clock_t waiting_time)
{
    rtk_timer_t timer={
                .executable_time=rtk_get_clock()+waiting_time,
                .waiting_time=waiting_time,
                .timer_call=timer_call
                };
    rtk_timer_critical_in();
    vector_push_back(&timer_list,timer);
    push_heap(vector_data(&timer_list),vector_size(&timer_list),vector_size(&timer_list)-1);
    rtk_debug("1\n");
    rtk_timer_critical_out();
}

static void* rtk_timer_thread(void *args)
{
    for(;;)
    {
        rtk_timer_critical_in();
        rtk_clock_t current_time=rtk_get_clock();
        rtk_debug("6\n");
        while(vector_size(&timer_list)>0 && current_time>=vector_at(&timer_list,0)->executable_time)
        {
            int is_repeat=vector_at(&timer_list,0)->timer_call();
            if(is_repeat == 0)
            {
                rtk_debug("4\n");
                pop_heap(vector_data(&timer_list),vector_size(&timer_list),0);
                vector_pop_back(&timer_list);
                rtk_debug("5\n");
            }
            else
            {
                rtk_debug("2\n");
                vector_at(&timer_list,0)->executable_time=current_time+vector_at(&timer_list,0)->waiting_time;
                pop_heap(vector_data(&timer_list),vector_size(&timer_list),0);
                push_heap(vector_data(&timer_list),vector_size(&timer_list),vector_size(&timer_list)-1);
                rtk_debug("3\n");
            }
        }
        rtk_timer_critical_out();
        rtk_timer_sleep(100);
    }
    return NULL;
}

void rtk_timer_init(void)
{
    pthread_t t;
    pthread_create(&t,NULL,rtk_timer_thread,NULL);
}