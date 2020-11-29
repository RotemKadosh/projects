#include <stdio.h> /*printf*/
#include <pthread.h>/*pthread_create*/

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
    pthread_cond_t mine;
    pthread_cond_t next;
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
void *ThreadFunc(void* arg)
{
    char *word;
    while(*runner != '\0')
    {
        pthread_mutex_lock(&lock);
        pthread_cond_wait(&((conds *)arg)->mine, &lock);

        word = GetNextWord();
        printf("%s", word);
        pthread_cond_broadcast(&((conds *)arg)->next);
    }
    return NULL;
}



int main(int argc, char **argv)
{
    conds c1 = {cond1, cond2};
    conds c2 = {cond2, cond3};
    conds c3 = {cond3, cond1};
    conds cond[3] = {c1, c2, c3};
    pthread_t tid[3] = {0};
    size_t i = 0;
    runner = paragraph;
    for(i = 0; i< 3; i++)
    {   
        pthread_create(&tid[i], NULL, ThreadFunc,(void *)&cond[i]);
    }
    for(i = 0; i < 3; i++)
    {
        pthread_join(tid[i], NULL);
    }
    return 0;
}