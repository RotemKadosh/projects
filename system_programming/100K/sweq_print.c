#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/
#include <unistd.h>
#include <assert.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond3 = PTHREAD_COND_INITIALIZER;

char *paragraph = "this is a paragraph, each thread prints a word";
char *runner;
char word[10];

typedef struct conds
{
    pthread_cond_t *mine;
    pthread_cond_t *next;
} conds;

char *GetNextWord()
{
    size_t i = 0;
    while(*runner != '\0' && *runner != ' ')
    {
        word[i] = *runner;
        ++runner;
        ++i;
    }
    word[i] = '\0';
    return word;
}

void *Thread1Func(void* arg)
{
    char *word;
    printf("thread1\n");
    while(*runner != '\0')
    {
        printf("1\n");
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond1, &lock);
        printf("2\n");
        word = GetNextWord();
        printf("%s\n", word);
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&cond2);
        printf("3\n");
    }
    return NULL;
}
void *Thread2Func(void* arg)
{
    char *word;
    printf("thread2\n");
    while(*runner != '\0')
    {
        printf("1\n");
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond2, &lock);
        printf("2\n");
        word = GetNextWord();
        printf("%s\n", word);
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&cond3);
        printf("3\n");
    }
    return NULL;
}
void *Thread3Func(void* arg)
{
    char *word;
    printf("thread3\n");
    while(*runner != '\0')
    {
        printf("1\n");
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&cond3, &lock);
        printf("2\n");
        word = GetNextWord();
        printf("%s\n", word);
        pthread_mutex_unlock(&lock);
        pthread_cond_broadcast(&cond1);
        printf("3\n");
    }
    return NULL;
}


int main(int argc, char **argv)
{
    
}