#include <stdio.h> /*printf, fopen , fclose*/
#include <stdlib.h>/*malloc, free*/
#include <string.h> /*memcpy*/
#include <sys/stat.h> /*stat*/
#include <pthread.h> /*create, mutex, join*/
#include <assert.h> /*assert*/
#include <stdatomic.h> /*atomic fetch add*/

#define NUM_OF_COPIES (1000)
#define NUM_OF_THREAD (8)

char *buffer = NULL;
size_t char_counters [256] = {0};
pthread_mutex_t count_lock = PTHREAD_MUTEX_INITIALIZER;
size_t num_of_bytes_per_thread = 0;

char *load();
char *DuplicateBuffer(char *buff, size_t size);
void *CountSortThread(void *arg);
void PrintSummary();


char *Load()
{
    char *buffer = NULL;
    FILE *src_file= NULL;
    size_t copied = 0;
    size_t i = 0;
    struct stat st = {0};
    size_t file_length = 0;
    
    src_file = fopen("american-english", "r");
    if(NULL == src_file)
    {
        return NULL;
    }
    stat("american-english", &st);
    file_length = st.st_size;
    buffer = (char *)malloc(file_length * NUM_OF_COPIES);
    if(NULL == buffer)
    {
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

    for( i = 1; i < NUM_OF_COPIES ; i++)
    {
       memcpy((void *)(buffer + (i * file_length)), buffer , file_length);
    } 

    num_of_bytes_per_thread = (file_length * NUM_OF_COPIES) / NUM_OF_THREAD;

    return buffer;
}

void *CountSortThread(void *arg)
{
    size_t t_char_counter[256] = {0};
    size_t i = 0;
    char *read_ptr = arg;
    char *end_ptr = (char *)arg + num_of_bytes_per_thread;

    assert(NULL != arg);

    while(read_ptr < end_ptr)
    {
        ++t_char_counter[(int)*read_ptr];
        ++read_ptr;
    }
    for(i = 0; i < 256; i++)
    {
        atomic_fetch_add(&char_counters[i], t_char_counter[i]) ;
    }
    
    return NULL;
}

void PrintSummary()
{
    char ch = 'A';
    printf("-------------chars summary-----------------\n");
    while(ch <= 'Z')
    {
        printf("%c - %ld \n", ch, char_counters[(int)ch]);
        ch++;
    }
    ch = 'a';
    while(ch <= 'z')
    {
        printf("%c - %ld \n", ch, char_counters[(int)ch]);
        ch++;
    }
}

int main(int argc, char **argv)
{
    size_t thread_i = 0;
    pthread_t tids[NUM_OF_THREAD] = {0};
    buffer = Load();
    for(thread_i = 0; thread_i < NUM_OF_THREAD; ++thread_i)
    {
        pthread_create(&tids[thread_i],NULL ,CountSortThread, buffer + (thread_i * num_of_bytes_per_thread ));
    }
    for(thread_i = 0; thread_i < NUM_OF_THREAD; ++thread_i)
    {
        pthread_join(tids[thread_i], NULL);
    }
    PrintSummary();
    free(buffer);
    buffer = NULL;
    (void)argc;
    (void)argv;
    return 0;
}
