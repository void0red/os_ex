#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

typedef struct {
    int *data;
    int num;
}sort_param, *sort_param_ptr;

void sort(void*);
void merge(void*);

int main(){
    int n = 0;
    scanf("%d", &n);
    int data[n];
    for(int i = 0; i < n; ++i) {
        scanf("%d", data+i);
    }
    pthread_t sort1, sort2;
    sort_param sort1_param = {
        .data = data,
        .num = n/2
    };
    sort_param sort2_param = {
        .data = data + n/2,
        .num = n - n/2
    };
    pthread_create(&sort1, NULL, (void*)&sort, &sort1_param);
    pthread_create(&sort2, NULL, (void*)&sort, &sort2_param);

    pthread_join(sort1, NULL);
    pthread_join(sort2, NULL);

    pthread_t merge1;
    sort_param merge_param = {
        .data = data,
        .num = n
    };
    pthread_create(&merge1, NULL, (void*)&merge, &merge_param);
    pthread_join(merge1, NULL);

    for(int i = 0; i < n; ++i) {
        printf("%d ", data[i]);
    }
    return 0;
}

void sort(void* arg) {
    sort_param_ptr d = (sort_param_ptr)arg;
    for(int i = 0; i < d->num - 1; ++i) {
        for(int j = 0; j < d->num - 1 - i; ++j) {
            if(d->data[j] > d->data[j+1]) {
                int temp = d->data[j];
                d->data[j] = d->data[j+1];
                d->data[j+1] = temp;
            }
        }
    }
    pthread_exit(0);
}

void merge(void* arg) {
    sort_param_ptr d = (sort_param_ptr)arg;
    int data[d->num];

    memcpy(data, d->data, sizeof(int)*d->num);

    int* p1 = d->data;
    int* p2 = d->data+d->num/2;
    int p1n = d->num/2;
    int p2n = d->num-d->num/2;

    for(int i = 0, j = 0, k = 0; i < d->num; ++i) {
        if(p1[j] > p2[k]) {
            data[i] = p2[k++];
        } else {
            data[i] = p1[j++];
        }

        if(j == p1n) {
            for(int _i = i+1; _i < d->num; ++_i) {
                data[_i] = p2[k++];
            }
            break;
        } else if (k == p2n) {
            for(int _i = i+1; _i < d->num; ++_i) {
                data[_i] = p1[j++];
            }
        }
    }

    memcpy(d->data, data, sizeof(int)*d->num);
    pthread_exit(0);
}
