#include <stdlib.h> /*malloc, free*/
#include <string.h> /*strcmp*/
#include <sys/stat.h> /*stat*/
#include <sys/mman.h>
#include "../utils/test.h"
#include "hash.h"


#define FALSE (0)
#define TRUE (1)

int fileno(FILE *stream);

size_t Stringhash(const void *str)
{
    size_t hash = 5381;
    int c = 0;

    while( (*(char *)str != '\0'))
    {
        c = *(char *)str;
        str = (char *)str + 1;
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

 int StringMatch(const void *data, const void *data_to_compare)
 {
     return !strcmp(data, data_to_compare);;
 }

static void Load(hash_table_ty *hash)
{
    char *ptr = NULL;
    char *token = NULL;
    char *delim = "\n\0";
    FILE *src_file= NULL;
    struct stat st = {0};
    size_t file_length = 0;
    src_file = fopen("/usr/share/dict/american-english", "r");
    stat("/usr/share/dict/american-english", &st);
    file_length = st.st_size;
    ptr = (char *)mmap(NULL, file_length, PROT_READ | PROT_WRITE, MAP_PRIVATE, fileno(src_file), 0);
    token = strtok(ptr, delim);
        
    while (token != NULL)
    {
        HashInsert(hash, token);
        token = strtok(NULL, delim);
    }
    fclose(src_file);
}

static int IsWordInDict(hash_table_ty *hash, const char * str)
{
    int ans = FALSE;
    char *m_word = HashFind(hash, str);
    if(NULL != m_word)
    {
        ans = TRUE;
    }
    return ans; 
}

int main(int argc, char *argv[])
{
    char *word = argv[argc - 1];
    hash_table_ty *hash = HashCreate(Stringhash, StringMatch, 26);
    Load(hash);
    if (!IsWordInDict(hash, word))
    {
        printf("the word: %s is not in the dictionary\n please check your spelling\n", word);
    }
    else
    {
        printf("the word: %s is spelled correctly\n", word);
    }
    HashDestroy(hash);
    return 0;
}