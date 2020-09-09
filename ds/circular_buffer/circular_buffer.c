#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc , free*/
#include <assert.h> /*assert*/
#include <string.h> /*memcpy*/
#include "circular_buffer.h"

#define MIN(x,y) x > y ? y : x
#define EXTRA_SPACE (1)


static size_t IdxUpdate(const size_t idx, const size_t steps, const size_t capacity);

typedef struct CBuffer
{
	size_t capacity;
	size_t write;
	size_t read;
	char bytes_array[1];
} CBuffer;


CBuffer_t *CBufferCreate(size_t capacity)
{
	CBuffer *cbuf = NULL;

	assert(capacity > 0);

	cbuf = (CBuffer *)malloc(sizeof(CBuffer) + (sizeof(char) * capacity) - (sizeof(size_t) - sizeof(char)));
	if(NULL == cbuf)
	{
		return NULL;
	}

	cbuf->write = 0;
	cbuf->read = 0;
	cbuf->capacity = capacity;

	return cbuf;
}
void CBufferDestroy(CBuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	free(cbuffer);
	cbuffer = NULL;
}
size_t CBufferSize(const CBuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	if(cbuffer->write >= cbuffer->read)
	{
		return (cbuffer->write - cbuffer->read);
	}
	else
	{
		return cbuffer->capacity + EXTRA_SPACE - (cbuffer->read - cbuffer->write) ;
	}
}
int CBufferIsEmpty(const CBuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	return (cbuffer->write == cbuffer->read); 
}
size_t CBufferFreeSpace(const CBuffer_t *cbuffer)
{
	assert(NULL != cbuffer);
	return (cbuffer->capacity - CBufferSize(cbuffer));
}
static size_t IdxUpdate(const size_t idx, const size_t steps, const size_t capacity)
{
	return (idx + steps) % (capacity + EXTRA_SPACE);
} 

ssize_t CBufferWrite(CBuffer_t *cbuffer, const void *input, size_t count_bytes)
{	
	size_t write = 0;
	size_t capacity = 0;
	size_t bytes_to_write = 0;
	size_t bytes_until_end = 0;

	assert(NULL != cbuffer);
	assert(NULL != input);

	write = cbuffer->write;
	capacity = cbuffer->capacity;
	bytes_to_write = MIN(CBufferFreeSpace(cbuffer), count_bytes);
	bytes_until_end = capacity + EXTRA_SPACE - write;

	bytes_until_end = MIN(bytes_to_write, bytes_until_end);
	memcpy(cbuffer->bytes_array + write, input, bytes_until_end);

	bytes_to_write -= bytes_until_end;
	write = IdxUpdate(write,  bytes_until_end , capacity);

	memcpy(cbuffer->bytes_array + write, input, bytes_to_write);
	cbuffer->write = IdxUpdate(write,  bytes_to_write , capacity);

	return bytes_to_write + bytes_until_end;
}

ssize_t CBufferRead(CBuffer_t *cbuffer, void *output, size_t count_bytes)
{
	size_t read = 0;
	size_t capacity = 0;
	size_t bytes_to_read = 0;
	size_t bytes_until_end = 0;

	assert(NULL != cbuffer);
	assert(NULL != output);

	read = cbuffer->read;
	capacity = cbuffer->capacity;

	bytes_to_read = MIN(CBufferSize(cbuffer), count_bytes);
	bytes_until_end = capacity + EXTRA_SPACE - read;

	bytes_until_end = MIN(bytes_to_read, bytes_until_end);
	memcpy(output, cbuffer->bytes_array + read, bytes_until_end);

	bytes_to_read -= bytes_until_end;
	read = IdxUpdate(read,  bytes_until_end , capacity);

	memcpy(output, cbuffer->bytes_array + read, bytes_to_read);
	cbuffer->read = IdxUpdate(read, bytes_to_read, capacity);

	return bytes_to_read + bytes_until_end;
}



