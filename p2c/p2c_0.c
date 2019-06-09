#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GOODS_BUF_SIZE 4

#define CUSTOMER_SIZE 10
#define PRODUCER_SIZE 10

typedef struct{
    int buf[GOODS_BUF_SIZE];
    pthread_mutex_t mutex;
    pthread_cond_t full;
    pthread_cond_t empty;
    int front;
    int rear;
}goods;

goods* create_goods();
void customer(void*);
void producer(void*);

int main()
{
    goods* good = create_goods();
    pthread_t customer_thread[CUSTOMER_SIZE];
    pthread_t producer_thread[PRODUCER_SIZE];
    for(int i = 0; i < CUSTOMER_SIZE; ++i){
        pthread_create(customer_thread+i, NULL, (void*)customer, good);
    }
    for(int i = 0; i < PRODUCER_SIZE; ++i){
        pthread_create(producer_thread+i, NULL, (void*)producer, good);
    }
    for(int i = 0; i < CUSTOMER_SIZE; ++i){
        pthread_join(customer_thread[i], NULL);
    }
    for(int i = 0; i < PRODUCER_SIZE; ++i){
        pthread_join(producer_thread[i], NULL);
    }

    return 0;
}

void customer(void* o)
{
    if(!o)
        return;
    goods* obj = (goods*)o;
    pthread_mutex_lock(&(obj->mutex));
    while(obj->front == obj->rear)
        pthread_cond_wait(&(obj->full), &(obj->mutex));

    int pos = (obj->front+1)%GOODS_BUF_SIZE;
    printf("customer customed %d\n", obj->buf[pos]);
    obj->front = pos;
    pthread_cond_signal(&(obj->empty));
    pthread_mutex_unlock(&(obj->mutex));

    pthread_exit(0);
}
void producer(void* o)
{
    if(!o)
        return;
    goods* obj = (goods*)o;
    pthread_mutex_lock(&(obj->mutex));
    while(obj->front == (obj->rear+1)%GOODS_BUF_SIZE)
        pthread_cond_wait(&(obj->empty), &(obj->mutex));

    int pos = (obj->rear+1)%GOODS_BUF_SIZE;

    printf("producer produced %d\n", obj->buf[pos]);
    obj->rear = pos;
    pthread_cond_signal(&(obj->full));
    pthread_mutex_unlock(&(obj->mutex));

    pthread_exit(0);
}

goods* create_goods()
{
    goods* ret = (goods*)malloc(sizeof(goods));
    for(int i = 0; i < GOODS_BUF_SIZE; ++i){
        ret->buf[i] = i;
    }
    ret->front = 0;
    ret->rear = 0;
    pthread_mutex_init(&(ret->mutex), NULL);
    pthread_cond_init(&(ret->empty), NULL);
    pthread_cond_init(&(ret->full), NULL);
    return ret;
}
void destroy_goods(goods* o)
{
    if(!o)
        return;
    pthread_mutex_destroy(&(o->mutex));
    pthread_cond_destroy(&(o->empty));
    pthread_cond_destroy(&(o->full));
}

