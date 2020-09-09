#include "../utils/test.h" /* Require, RUNTEST */
#include "circular_buffer.h"

#define TRUE (1)
#define FALSE (0)

static test_status_t TestCBCreate();
static test_status_t TestCBufferIsEmpty();
static test_status_t TestCBufferSize();
static test_status_t TestCBufferWrite();
static test_status_t TestCBufferRead();
static test_status_t TestCBufferFreeSpace();

int main()
{
	RUNTEST(TestCBCreate);
	RUNTEST(TestCBufferIsEmpty);
	RUNTEST(TestCBufferSize);
	RUNTEST(TestCBufferWrite);
	RUNTEST(TestCBufferRead);
	RUNTEST(TestCBufferFreeSpace);
	return 0;
}

static test_status_t TestCBCreate()
{
	CBuffer_t *cbuf = CBufferCreate(10);
	REQUIRE(NULL != cbuf);
	CBufferDestroy(cbuf);
	return PASSED;
}
static test_status_t TestCBufferSize()
{
	CBuffer_t *cbuf = CBufferCreate(10);

	char chars[] = "hello";
	char chars_new[10] = {0};

	REQUIRE(0 == CBufferSize(cbuf));

	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(3 == CBufferSize(cbuf));

	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(6 == CBufferSize(cbuf));

	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(9 == CBufferSize(cbuf));

	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(10 == CBufferSize(cbuf));

	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(7 == CBufferSize(cbuf));
	

	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(4 == CBufferSize(cbuf));
	

	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(1 == CBufferSize(cbuf));
	

	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(0 == CBufferSize(cbuf));


	CBufferDestroy(cbuf);
	return PASSED;
}
static test_status_t TestCBufferIsEmpty()
{	
	char chars[] = "hellohell";
	char chars_new[10] = {0};
	CBuffer_t *cbuf = CBufferCreate(10);
	REQUIRE(TRUE == CBufferIsEmpty(cbuf));
	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(FALSE == CBufferIsEmpty(cbuf));
	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(TRUE == CBufferIsEmpty(cbuf));
	CBufferWrite(cbuf, (void *)chars, 10);
	REQUIRE(FALSE == CBufferIsEmpty(cbuf));

	CBufferDestroy(cbuf);
	return PASSED;
}
static test_status_t TestCBufferFreeSpace()
{
	CBuffer_t *cbuf = CBufferCreate(10);
	char chars[] = "hello";
	char chars_new[10] = {0};
	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(7 == CBufferFreeSpace(cbuf));
	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(4 == CBufferFreeSpace(cbuf));
	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(1 == CBufferFreeSpace(cbuf));
	CBufferWrite(cbuf, (void *)chars, 3);
	REQUIRE(0 == CBufferFreeSpace(cbuf));
	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(3 == CBufferFreeSpace(cbuf));
	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(6 == CBufferFreeSpace(cbuf));
	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(9 == CBufferFreeSpace(cbuf));
	CBufferRead(cbuf, (void *)chars_new, 3);
	REQUIRE(10 == CBufferFreeSpace(cbuf));
	CBufferDestroy(cbuf);
	return PASSED;
}
static test_status_t TestCBufferWrite()
{
	CBuffer_t *cbuf = CBufferCreate(10);
	char chars[] = "hello";
	REQUIRE(3 ==CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(3 == CBufferSize(cbuf));

	REQUIRE(3 ==CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(6 == CBufferSize(cbuf));

	REQUIRE(3 ==CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(9 == CBufferSize(cbuf));

	REQUIRE(1 ==CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(10 == CBufferSize(cbuf));

	CBufferDestroy(cbuf);
	return PASSED;
}
static test_status_t TestCBufferRead()
{
	CBuffer_t *cbuf = CBufferCreate(10);
	char chars[] = "hello";
	char chars_new[10] = {0};

	REQUIRE(3 == CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(3 == CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(3 == CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(1 == CBufferWrite(cbuf, (void *)chars, 3));
	REQUIRE(10 == CBufferSize(cbuf));

	REQUIRE(3 == CBufferRead(cbuf, (void *)chars_new, 3));
	REQUIRE(7 == CBufferSize(cbuf));
	REQUIRE(chars_new [0] == 'h' && chars_new [1] == 'e' && chars_new [2] == 'l');

	REQUIRE(3 == CBufferRead(cbuf, (void *)chars_new, 3));;
	REQUIRE(4 == CBufferSize(cbuf));
	REQUIRE(chars_new [0] == 'h' && chars_new [1] == 'e' && chars_new [2] == 'l');

	REQUIRE(3 == CBufferRead(cbuf, (void *)chars_new, 3));
	REQUIRE(1 == CBufferSize(cbuf));
	REQUIRE(chars_new [0] == 'h' && chars_new [1] == 'e' && chars_new [2] == 'l');

	REQUIRE(1 == CBufferRead(cbuf, (void *)chars_new, 3));
	REQUIRE(0 == CBufferSize(cbuf));
	REQUIRE(chars_new [0] == 'h' && chars_new [1] == 'e' && chars_new [2] == 'l');

	CBufferDestroy(cbuf);
	return PASSED;
}
