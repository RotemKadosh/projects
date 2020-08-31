#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include "vector.h"

#define GROWTH_FACTOR (2)

struct vector
{
    void **items;
    size_t capacity;
    size_t last;
}; 

Vector_t *VectorCreate(size_t capacity)
{
	Vector_t *vec = NULL;
	assert(0 < capacity);
	vec = (Vector_t *)malloc(sizeof(Vector_t));
	if(NULL == vec)
	{
		return NULL;
	}
	vec->items = (void **)malloc(capacity * sizeof(void *));
	if(NULL == vec->items)
	{
		return NULL;
	}
	vec->capacity = capacity;
	vec->last = 0;
	return vec;
}
void VectorDestroy(Vector_t *vector)
{
	assert(NULL != vector);
	vector->items = NULL;
	free(vector);
	vector = NULL;
}
void *VectorGetElement(const Vector_t *vector, size_t index)
{
	assert(NULL != vector);
	return vector->items[index];
}
void VectorSetElement(Vector_t *vector, void *element, size_t index)
{
	assert(NULL != vector);
	assert(indx < vector->last);
	vector->items[index] = element;
}
size_t VectorSize(const Vector_t *vector)
{
	assert(NULL != vector);
	return vector->last ;
}
size_t VectorCapacity(const Vector_t *vector)
{
	assert(NULL != vector);
	return vector->capacity;
}
int VectorPushBack(Vector_t *vector, void *element)
{
	size_t new_capacity = 0;
	assert(NULL != vector);
	if(vector->last >= vector->capacity)
	{
		new_capacity = vector->capacity * GROWTH_FACTOR;

		if(0 != VectorReserve(vector , new_capacity))
		{
			return -1;
		}
		vector->capacity = new_capacity;
	}
	vector->items[vector->last++] = element;
	return 0;

}
void VectorPopBack(Vector_t *vector)
{
	assert(NULL != vector);
	--vector->last;
}
int VectorReserve(Vector_t *vector, size_t new_capacity)
{
	assert(NULL != vector);
	vector->items = (void **)realloc( vector->items , new_capacity * sizeof(void *));
	if(NULL == vector->items)
	{
		return -1;
	}
	vector->capacity = new_capacity;
	return 0;
}
int VectorShrinkToFit(Vector_t *vector)
{
	assert(NULL != vector);
	if(0 != VectorReserve(vector, vector->last))
	{
		return -1;
	}
	return 0;
	
}






