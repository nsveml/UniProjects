#include"stdio.h"
#include"pthread.h"
#include"stdlib.h"
#include<time.h>
#include<unistd.h>

typedef struct{
    int *array, left, right, thread_number, isthread;
} pthrData;

int partition(int* array, int left, int right){
    int pivot = array[(left+right)/2], i = left, j = right, tmp;
    while(1){
        while(array[i]<pivot) i++;
        while(array[j]>pivot) j--;
        if(i>=j) return j;
        tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
        i++;
        j--;
    }
    return j;
}

void quick_sort(int*array, int left, int right){
    if(left<right){    
        int p=partition(array, left, right);
        quick_sort(array, left, p);
        quick_sort(array, p+1, right);
    }
}

void* quick_sort_parallel_thread(void* thread_data/* int*array, int left, int right */){
    pthrData *data=(pthrData*)thread_data;
    if(data->left<data->right){
        int p=partition(data->array, data->left, data->right), tmp;
        pthrData* dataToPthr=NULL;
        pthread_t thread;
        if(data->thread_number > 0){
            data->thread_number--;//здесь я создаю поток, поэтому фактически число доступных потоков для родительского и дочернего будет на одно меньше
            dataToPthr=(pthrData*)malloc(sizeof(pthrData));
            dataToPthr->array=data->array;//новый поток будет работать с тем же массивом
            dataToPthr->right=data->right;//его конец будет совпадать с родительским
            data->right=p;//родительский конец изменится на р 
            dataToPthr->left=p+1;//дочернее начало будет р+1
            tmp=data->thread_number;//далее распределим количество доступных процессов между родителем и ребенком
            data->thread_number=tmp/2;
            //data->thread_number=(int)((float)(data->right-data->left)/(float)(dataToPthr->right-dataToPthr->left)*(float)tmp);
            dataToPthr->thread_number=tmp-data->thread_number;
            dataToPthr->isthread = 1;
            pthread_create(&thread, NULL, quick_sort_parallel_thread, dataToPthr);//создадим ребенка и передадим в него нужные данные
            quick_sort_parallel_thread(data);//родитель продолжает рекурсивно
            pthread_join(thread, NULL);//ловим созданный процесс
            free(dataToPthr);
        }
        else{
            quick_sort(data->array, data->left, data->right);//если процессы больше создавать нельзя, то остаток сортируем обычным рекурсивным quicksort
        }
        return 0;
    }
}


void quick_sort_parallel(int *array, int left, int right, int thread_number){
    pthrData data;
    data.array=array;
    data.left=left;
    data.right=right;
    data.thread_number=thread_number;
    data.isthread=0;
    quick_sort_parallel_thread(&data);
}

int main(int argc, char *argv[]){
    int *array, *array1, length = 0, capacity = 1;
    array=(int*)malloc(sizeof(int));
    while(scanf("%d", &array[length]) > 0){
        length++;
        if(capacity == length){
            capacity *= 2;
            array = (int*)realloc(array, sizeof(int)*capacity);
        }
    }
    array = (int*)realloc(array, sizeof(int)*length);
    array1 = (int*)malloc(sizeof(int)*length);
    for(int i=0; i<length; i++){
        array1[i]=array[i];
    }
    if(argc == 1){
        printf("\nquick\n");
        quick_sort(array, 0, length-1);
    }
    else{
        printf("\nparallel\n");
        quick_sort_parallel(array, 0, length-1, (int)strtol(argv[1], NULL, 10));
    }
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    free(array1);
    free(array);
}