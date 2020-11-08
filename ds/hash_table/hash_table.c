#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include <string.h> /*memset*/
#include <math.h>

#include "hash.h"
#include "../dlist/dlist.h"


#define FALSE (0)
#define TRUE (1)
#define INSERT_SUCCESS (0)
#define INSERT_FAIL (1)



struct hash_table 
{
    hash_func_ty hash_func;
    is_match_func_ty match_func;
    size_t capacity;
    Dlist_t **hash_arr;
}; 

hash_table_ty *HashCreate(hash_func_ty hash_func, is_match_func_ty is_match_func, size_t capacity)
{
    size_t i = 0;
    hash_table_ty *hash = NULL;
    Dlist_t *dlist = NULL;

    assert(NULL != hash_func);

    hash = malloc(sizeof(hash_table_ty)); 
    if(NULL != hash)
    {
        hash->hash_arr = malloc(sizeof(Dlist_t *) * capacity);
        if(hash->hash_arr != NULL)
        {
            hash->hash_func = hash_func;
            hash->capacity = capacity;
            hash->match_func = is_match_func;
            for(i = 0; i < hash->capacity; ++i )
            {
                dlist = DlistCreate();
                if(dlist == NULL)
                {
                    hash->capacity = i;
                    HashDestroy(hash);
                    return NULL;
                }
                hash->hash_arr[i] = dlist;
            }
        }
        else
        {
            free(hash);
            hash = NULL;
        }
      
    }
    return hash;
}

void HashDestroy(hash_table_ty *hash)
{
    size_t i = 0;
    size_t capacity = 0;

    assert(NULL != hash);
    
    capacity = hash->capacity;
    for(i = 0; i < capacity; ++i)
    {
        DlistDestroy(hash->hash_arr[i]);
    }
    free(hash->hash_arr);
    hash->hash_arr = NULL;
    free(hash);
    hash = NULL;
}

int HashIsEmpty(const hash_table_ty *hash)
{
    size_t i = 0;
    size_t capacity = 0;

    assert(NULL != hash);

    capacity = hash->capacity;
    for(i = 0; i < capacity; ++i)
    {
        if(!DlistIsEmpty(hash->hash_arr[i]))
        {
            return FALSE;
        }
    }
    return TRUE;
}

size_t HashSize(const hash_table_ty *hash)
{
    size_t i = 0;
    size_t size = 0;
    size_t capacity = 0;

    assert(NULL != hash);

    capacity = hash->capacity;
    for(i = 0; i < capacity; ++i)
    {
        size += DlistSize(hash->hash_arr[i]);
    }
    return size;
}

int HashInsert(hash_table_ty *hash_table, void *data)
{
    Dlist_iter_t iter = NULL;
    Dlist_iter_t end = NULL;
    Dlist_t *dlist = NULL;
    size_t idx = 0;
    int ans = INSERT_SUCCESS;

    assert(NULL != hash_table);
    
    idx = hash_table->hash_func(data);
    dlist = hash_table->hash_arr[idx % hash_table->capacity];
    end = DlistEnd(dlist);
    
    iter = DlistFind(DlistBegin(dlist), end, hash_table->match_func, data);
    if(!DlistIsSameIter(iter, end))
    {
        DlistSetData(iter, data);
    }
    else
    {
        iter = DlistInsert(dlist, iter, data);
        if(DlistIsSameIter(iter, end))
        {
            ans = INSERT_FAIL;
        }
    }
    return ans;
}

void HashRemove(hash_table_ty *hash_table, const void *data)
{
    Dlist_iter_t iter = NULL;
    Dlist_t *dlist = NULL;
    size_t idx = 0;
    Dlist_iter_t end = NULL;

    assert(NULL != hash_table);

    idx = hash_table->hash_func(data);
    dlist = hash_table->hash_arr[idx % hash_table->capacity];
    end = DlistEnd(dlist);

    iter = DlistFind(DlistBegin(dlist), end,hash_table->match_func, data);
    if(!DlistIsSameIter(iter, end))
    {
        DlistRemove(dlist, iter);
    }
}

void *HashFind(hash_table_ty *hash_table, const void *data)
{
    Dlist_iter_t iter = NULL;
    Dlist_t *dlist = NULL;
    size_t idx = 0;
    void *data_to_return = NULL;
    Dlist_iter_t end = NULL;

    assert(NULL != hash_table);
    
    idx = hash_table->hash_func(data);
    dlist = hash_table->hash_arr[idx % hash_table->capacity];
    end = DlistEnd(dlist);
    
    
    iter = DlistFind(DlistBegin(dlist), end,hash_table->match_func, data);
    if(!DlistIsSameIter(iter, end))
    {
        data_to_return = DlistGetData(iter);
        
        if(!DlistIsSameIter(DlistPushFront(dlist, data_to_return), end))
        {
            DlistRemove(dlist, iter);
        }    
    }
    return data_to_return;
}

int HashForEach(hash_table_ty *hash, action_func_ty action_func, void *param)
{
    size_t i = 0;
    Dlist_t *dlist = NULL;
    size_t capacity = 0;
    int action_status = INSERT_SUCCESS;

    assert(NULL != hash);
    assert(NULL != action_func);
    
    capacity = hash->capacity;

    for(i = 0; (i < capacity) && (action_status == INSERT_SUCCESS) ; ++i)
    {
        dlist = hash->hash_arr[i];
        action_status = DlistForEach(DlistBegin(dlist), DlistEnd(dlist), action_func, param);
    }
    return action_status;
}

double HashLoadFactor(hash_table_ty *hash)
{
    assert(NULL != hash);
    return (HashSize(hash) / hash->capacity);
}

double HashSD(hash_table_ty *hash) 
{
    size_t i = 0;
    Dlist_t *dlist = NULL; 
    double mu = 0;
    double xi = 0;
    double diff_square_sum = 0;
    double ans = 0;
    size_t capacity = 0;

    assert(NULL != hash);

    capacity = hash->capacity;
    mu = HashLoadFactor(hash);
    for(i = 0; i < capacity ; ++i)
    {
        dlist = hash->hash_arr[i];
        xi = DlistSize(dlist);
        diff_square_sum += ((xi - mu) * (xi - mu)); 
    }
    ans = diff_square_sum / hash->capacity;
    ans = sqrt(ans);
    return ans;
}





























