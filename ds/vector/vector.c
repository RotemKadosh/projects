#include <stdlib.h> /*malloc, free*/
#include <assert.h> /*assert*/
#include "vector.h"

#define GROWTH_FACTOR (2)
#define FAIL (-1)
#define SUCCESS (0)

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
		free(vec);
		return NULL;
	}

	vec->capacity = capacity;
	vec->last = 0;
	return vec;
}
void VectorDestroy(Vector_t *vector)
{
	assert(NULL != vector);

	free(vector->items);
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
	if (vector->last >= vector->capacity)
	{
		new_capacity = vector->capacity * GROWTH_FACTOR;

		if (SUCCESS != VectorReserve(vector , new_capacity))
		{
			return FAIL;
		}
	}
	vector->items[vector->last++] = element;
	return SUCCESS;

}
void VectorPopBack(Vector_t *vector)
{
	assert(NULL != vector);
	--vector->last;
}
int VectorReserve(Vector_t *vector, size_t new_capacity)
{
	void ** real = NULL;
	assert(NULL != vector);
	real = (void **)realloc( vector->items , new_capacity * sizeof(void *));
	if(NULL == real)
	{
		return FAIL;
	}
	vector->items = real;
	vector->capacity = new_capacity;
	return SUCCESS;
}
int VectorShrinkToFit(Vector_t *vector)
{
	assert(NULL != vector);
	if(SUCCESS != VectorReserve(vector, vector->last))
	{
		return FAIL;
	}
	return SUCCESS;
	
}






