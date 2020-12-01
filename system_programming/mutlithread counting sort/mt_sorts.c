#include <stdio.h> /*printf, fopen , fclose*/
#include <stdlib.h>/*malloc, free*/
#include <string.h> /*memcpy*/
#include <sys/stat.h> /*stat*/
#include <pthread.h> /*create, mutex, join*/
#include <assert.h> /*assert*/
#include <stdatomic.h> /*atomic fetch add*/
#include "../../ds/sort/merge.h"
#include "comparation_sorts.h"

#define NUM_OF_THREAD (7)
#define NUM_OF_WORDS (21)
#define N (3)
#define NUM_OF_WORDS_PER_THREAD ((NUM_OF_WORDS * N) / NUM_OF_THREAD)
#define REST ((NUM_OF_WORDS * N) - (NUM_OF_THREAD * NUM_OF_WORDS_PER_THREAD))

char **word_buffer;
char *buffer;

void DivideStringToWords()
{
    
    size_t count = 0;
    size_t i = 0;
    char **word_buffer_run = word_buffer;
    char *buf_ptr = buffer;
    word_buffer[0] = buffer;
    ++count;
    while('\0' != *buf_ptr)
    {
        if('\n' == *buf_ptr)
        {
            *buf_ptr = '\0';
            word_buffer[count] = buf_ptr + 1;
            ++count;
        }
        ++buf_ptr;
    }

    for (i = 1 ; i < N; ++i)
    {
        word_buffer_run = word_buffer_run + NUM_OF_WORDS;
        memcpy(word_buffer_run, word_buffer, (sizeof(char *) * NUM_OF_WORDS ));
    } 
}

int Comp(const void *ptr1, const void *ptr2)
{
    return (*(size_t *)ptr1 - *(size_t *)ptr2);
}

int RandCompare(const void *ptr1,const void *ptr2)
{
  
    assert(NULL != ptr1);
    assert(NULL != ptr2);
    (void)ptr1;
    (void)ptr2;
    return (rand() - rand());

}

void PrintSummary()
{
    size_t count = 0;
    printf("-------------word summary-----------------\n");
    for(count = 0; count < NUM_OF_WORDS * N; count+= 1)
    {
        printf("%ld: %s\n",count ,word_buffer[count]);
    }
    
}

char *Load()
{
    FILE *src_file= NULL;
    size_t copied = 0;

    struct stat st = {0};
    size_t file_length = 0;
    
    src_file = fopen("american-english1", "r");
    if(NULL == src_file)
    {
        return NULL;
    }
    stat("american-english1", &st);
    file_length = st.st_size;
    buffer = (char *)malloc(file_length + 1);
    word_buffer = (char **)malloc(NUM_OF_WORDS * N * sizeof(char *));
    if(NULL == buffer || NULL == word_buffer)
    {
        free(buffer);
        free(word_buffer);
        return NULL;
    }
    copied = fread(buffer, 1, file_length, src_file);
    if(copied != file_length)
    {
        return NULL;
    }
    if(EOF == fclose(src_file))
    {
        return NULL;
    }
    *(buffer + file_length) = '\0';
    DivideStringToWords();
    
    return buffer;
}

void *ThreadSort(void *arg)
{
    assert(NULL != arg);
    /*Qsort(arg, NUM_OF_WORDS_PER_THREAD ,sizeof(char *), Comp);*/
    /*InsertionSort((size_t *)arg, NUM_OF_WORDS_PER_THREAD);*/
    /*BubbleSort((size_t *)arg, NUM_OF_WORDS_PER_THREAD);*/
    /*SelectionSort((size_t *)arg, NUM_OF_WORDS_PER_THREAD);*/
    /*CountSort((size_t *)arg, NUM_OF_WORDS_PER_THREAD);*/
    /*RadixSort((size_t *)arg, NUM_OF_WORDS_PER_THREAD);*/
    return arg;
}

void CopyArr(char **dest, char **src, size_t size)
{
    size_t count = 0;
    for(count = 0; count < size; ++count)
    {
        *dest = *src;
        dest++;
        src++;
    }
}

void* MergeTwoParts(char **left, char **right, size_t left_size,size_t right_size)
{
    size_t left_r = 0;
    size_t right_r = 0;
    size_t total_size = (left_size + right_size);
    size_t temp_ptr = 0;

    char **temp_arr = malloc(total_size* sizeof(char *));
    if(NULL == temp_arr)
    {
        return NULL;
    }
    memset(temp_arr, 0, (sizeof(char *) * total_size));
    while (left_r < left_size && right_r < right_size)
    {
        if(left[left_r] < right[right_r])
        {
            temp_arr[temp_ptr] = left[left_r];
            ++left_r;
        }
        else
        {
            temp_arr[temp_ptr] = right[right_r];
            ++right_r;
        }
        ++temp_ptr;
    }
    /*
    CopyArr(temp_arr + temp_ptr, right + right_r, size_per_side - right_r);
    temp_ptr += size_per_side - right_r;
    */
    while (left_r < left_size)
    {
        temp_arr[temp_ptr] = left[left_r];
        ++left_r;
        ++temp_ptr;
    }
    
    while (right_r < right_size)
    {
        temp_arr[temp_ptr] = right[right_r];
        ++right_r;
        ++temp_ptr;
    }
    temp_ptr = 0;
    left_r = 0;
    while(left_r < total_size )
    {
        left[left_r] = temp_arr[temp_ptr];
        ++left_r;
        ++temp_ptr;
    }
    free(temp_arr);
    return left;

}

void MergeThread()
{
    size_t size = NUM_OF_WORDS_PER_THREAD;
    size_t i = 1;
    for(i = 1; i < NUM_OF_THREAD; i += 1)
    {
        MergeTwoParts(word_buffer , 
                word_buffer + (i * NUM_OF_WORDS_PER_THREAD), size, NUM_OF_WORDS_PER_THREAD);
                size += NUM_OF_WORDS_PER_THREAD;
    }
           
}

void Shuffle()
{
    qsort(word_buffer, NUM_OF_WORDS * N, sizeof(char *), RandCompare);
}

void InsertionOfRest()
{
    size_t selection_idx = 0;
    char * selection = 0;
    __ssize_t where = 0; 
    size_t size = (NUM_OF_WORDS * N);
    
    for (selection_idx = size - REST; selection_idx < size; selection_idx++) { 
        
        selection = word_buffer[selection_idx]; 
        where = selection_idx - 1; 
        
        while ((long)where >= 0 && word_buffer[where] > selection)
        { 
            word_buffer[where + 1] = word_buffer[where]; 
            where = where - 1; 
        } 
        word_buffer[where + 1] = selection; 
    }
}
        
int main(int argc, char **argv)
{
    size_t thread_i = 0;
    pthread_t tids[NUM_OF_THREAD] = {0};
    char **word_buffer_ptr = word_buffer;
    buffer = Load();

    Shuffle();

    for(thread_i = 0; thread_i < NUM_OF_THREAD; ++thread_i)
    {
        word_buffer_ptr =(word_buffer + (thread_i * NUM_OF_WORDS_PER_THREAD));
        pthread_create(&tids[thread_i], NULL, ThreadSort, word_buffer_ptr);
    }
    for(thread_i = 0; thread_i < NUM_OF_THREAD; ++thread_i)
    {
        pthread_join(tids[thread_i], NULL);
    }
    
    MergeThread();
    InsertionOfRest();
    PrintSummary();
    free(buffer);
    free(word_buffer);
    buffer = NULL;
    word_buffer = NULL;
    (void)argc;
    (void)argv;
    return 0;

}