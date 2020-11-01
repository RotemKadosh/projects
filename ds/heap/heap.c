#include <stdlib.h> /*malloc free*/
#include <assert.h> /*assert*/
#include "heap.h"
#include "vector.h"

#define VECTOR_SIZE_DEF (10)
#define SUCCESS (0)
#define FAIL (112)
#define ROOT_IDX (0)
#define TRUE (1)
#define LEFT_CHILD(idx) (2 * idx + 1)
#define RIGHT_CHILD(idx) (2 * idx + 2)

struct heap
{
    Vector_t *vector;
    cmp_func_ty compare_func; 
};


static void HeapifyDown(Heap_ty *heap, size_t root_idx); 
static void swap(Heap_ty *heap, size_t num_idx1, size_t num_idx2);
static void *FindAndRemoveRecursive(Heap_ty *heap, size_t idx, is_match_func_ty match_func, void *param);
static void HeapifyUp(Heap_ty *heap, size_t child_idx);

Heap_ty *HeapCreate(cmp_func_ty cmp)
{
    Heap_ty *heap = NULL;
    Vector_t *vector = NULL;

    assert(NULL != cmp);

    vector = VectorCreate(VECTOR_SIZE_DEF);
    if(NULL != vector)
    {
        heap = (Heap_ty *)malloc(sizeof(Heap_ty));
        if(NULL != heap)
        {
            heap->vector = vector;
            heap->compare_func = cmp;
        }
        else
        {
            VectorDestroy(vector);
        } 
    }
    return heap;
}

void HeapDestroy(Heap_ty *heap)
{
    assert(NULL != heap);

    VectorDestroy(heap->vector);
    heap->vector = NULL;
    free(heap);
    heap = NULL;
}

void HeapPop(Heap_ty *heap)
{
    Vector_t *vec = NULL;

    assert(NULL != heap);
    
    vec = heap->vector;
    if(1 < HeapSize(heap))
    {   
        swap(heap, ROOT_IDX, VectorSize(vec) - 1);
        VectorPopBack(vec);
        HeapifyDown(heap, ROOT_IDX);
    }
    else
    {
        VectorPopBack(vec);
    }
    
  
}

int HeapPush(Heap_ty *heap, void *data)
{
    int ans = FAIL;

    assert(NULL != heap);

    ans = VectorPushBack(heap->vector, data);
    if(SUCCESS == ans)
    {
        HeapifyUp(heap, HeapSize(heap) - 1);
    }

    return ans;
}

void *HeapPeek(const Heap_ty *heap)
{
    assert(NULL != heap);

    return VectorGetElement(heap->vector, ROOT_IDX);
}

int HeapIsEmpty(const Heap_ty *heap)
{
    assert(NULL != heap);

    return (0 == VectorSize(heap->vector));
}

size_t HeapSize(const Heap_ty *heap)
{
    assert(NULL != heap);

    return VectorSize(heap->vector);
}

void *HeapRemove(Heap_ty *heap ,is_match_func_ty match_func ,void *param)
{

    assert(NULL != heap);
    assert(NULL != match_func);

    return FindAndRemoveRecursive(heap, ROOT_IDX ,match_func, param);
}

static void *FindAndRemoveRecursive(Heap_ty *heap, size_t idx, is_match_func_ty match_func, void *param)
{
    void *data_to_ret = NULL;
    Vector_t *vec = NULL;

    assert(NULL != heap);
    vec = heap->vector;
    if(idx >= VectorSize(vec))
    {
        return NULL;
    }
    data_to_ret = VectorGetElement(vec, idx);
    if(TRUE == match_func(data_to_ret, param))
    {
        swap(heap, idx, ROOT_IDX);
        HeapPop(heap);
        return data_to_ret;
    }
    return FindAndRemoveRecursive(heap, idx + 1, match_func, param);
    
    

}

static void HeapifyDown(Heap_ty *heap, size_t root_idx) 
{ 
    Vector_t *vec = NULL;
    void *largest = NULL;
    size_t largest_idx = 0;
    size_t left_idx = 0;
    size_t right_idx = 0;
    size_t size = 0;

    assert(NULL != heap);

    vec = heap->vector;
    largest_idx = root_idx;
    left_idx = LEFT_CHILD(root_idx);
    right_idx = RIGHT_CHILD(root_idx);
    size = VectorSize(vec); 
    largest = VectorGetElement(vec, root_idx);

    if(left_idx < size && heap->compare_func(VectorGetElement(vec, left_idx), largest) > 0)
    {
        
        largest_idx = left_idx; 
        largest = VectorGetElement(vec, left_idx);
        
    }
    if(right_idx < size && heap->compare_func(VectorGetElement(vec, right_idx), largest) > 0)
    {
        
        largest_idx = right_idx; 
        
    }
    if (largest_idx != root_idx) 
    { 
        swap(heap, root_idx, largest_idx);
        HeapifyDown(heap, largest_idx); 
    } 
} 

static void HeapifyUp(Heap_ty *heap, size_t child_idx)
{
    void *parent = NULL;
    Vector_t *vec = NULL;
    size_t size = 0;
    void *child = NULL;
    size_t parent_idx = 0;

    assert(NULL != heap);

    vec = heap->vector;
    size = VectorSize(vec); 
    child = VectorGetElement(heap->vector, child_idx);
    parent_idx = (child_idx - 1) / 2 ;
    if (parent_idx < size)
    {
        parent = VectorGetElement(heap->vector, parent_idx);
        if(heap->compare_func(child, parent) > 0 )
        {
            swap(heap, child_idx, parent_idx);
            HeapifyUp(heap, parent_idx);
        }  
    }
  

}

static void swap(Heap_ty *heap, size_t num_idx1, size_t num_idx2)
{
    void *num1 = NULL;
    Vector_t *vec = NULL;
    assert(NULL != heap);
    vec = heap->vector;
    assert(num_idx2 < VectorSize(vec));
    assert(num_idx1 < VectorSize(vec));

    num1 = VectorGetElement(vec, num_idx1);
    VectorSetElement(vec, VectorGetElement(vec, num_idx2), num_idx1);
    VectorSetElement(vec, num1, num_idx2);
}


























