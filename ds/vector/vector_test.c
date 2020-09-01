#include "../utils/test.h" /*REQUIER, RUNTEST*/
#include "vector.h"


static test_status_t TestVectorCreate();
static test_status_t TestVectorPushBack();
static test_status_t TestVectorPopBack();
static test_status_t TestVectorGetElement();
static test_status_t TestVectorSetElement();
static test_status_t TestVectorReserve();
static test_status_t TestVectorShrinkToFit();

int main(int argc, char const *argv[])
{
	
	RUNTEST(TestVectorCreate);
	RUNTEST(TestVectorPushBack);
	RUNTEST(TestVectorPopBack);
	RUNTEST(TestVectorGetElement);
	RUNTEST(TestVectorSetElement);
	RUNTEST(TestVectorReserve);
	RUNTEST(TestVectorShrinkToFit);

	(void) argc;
	(void) argv;

	return 0;
}


static test_status_t TestVectorCreate()
{
	Vector_t *vec = VectorCreate(20);
	REQUIRE(NULL != vec);
	VectorDestroy(vec);
	vec = VectorCreate(1);
	REQUIRE(NULL != vec);
	VectorDestroy(vec);
	vec = VectorCreate(15000);
	REQUIRE(NULL != vec);
	VectorDestroy(vec);
	return PASSED;
}
static test_status_t TestVectorPushBack()
{
	Vector_t *vec = VectorCreate(1);
	REQUIRE(0 ==  VectorPushBack(vec, (void *)8));
	REQUIRE(0 ==  VectorPushBack(vec, (void *)7));
	REQUIRE(0 ==  VectorPushBack(vec, (void *)6));
	REQUIRE(0 ==  VectorPushBack(vec, (void *)'H'));
	VectorDestroy(vec);
	return PASSED;
}
static test_status_t TestVectorPopBack()
{
	Vector_t *vec = VectorCreate(1);
	VectorPushBack(vec, (void *)8);
	VectorPushBack(vec, (void *)7);
	VectorPushBack(vec, (void *)6);
	VectorPushBack(vec, (void *)'H');
	
	REQUIRE(4 ==  VectorSize(vec));
	VectorPopBack(vec);
	REQUIRE(3 ==  VectorSize(vec));
	VectorPopBack(vec);
	REQUIRE(2 ==  VectorSize(vec));
	VectorPopBack(vec);
	REQUIRE(1 ==  VectorSize(vec));
	VectorPopBack(vec);
	REQUIRE(0 ==  VectorSize(vec));
	VectorDestroy(vec);
	return PASSED;
}
static test_status_t TestVectorSetElement()
{
	Vector_t *vec = VectorCreate(1);
	VectorPushBack(vec, (void *)8);
	VectorPushBack(vec, (void *)7);
	VectorPushBack(vec, (void *)6);
	
	VectorSetElement(vec,(void *)7, 0);
	VectorSetElement(vec,(void *)7, 1);
	VectorSetElement(vec,(void *)7, 2);
	VectorSetElement(vec,(void *)7, 3);
	
	REQUIRE((void *)7 ==  VectorGetElement(vec, 0));
	REQUIRE((void *)7 ==  VectorGetElement(vec, 1));
	REQUIRE((void *)7 ==  VectorGetElement(vec, 2));
	REQUIRE((void *)7 ==  VectorGetElement(vec, 3));

	VectorDestroy(vec);
	return PASSED;
}
static test_status_t TestVectorGetElement()
{
	Vector_t *vec = VectorCreate(1);
	VectorPushBack(vec, (void *)8);
	VectorPushBack(vec, (void *)7);
	VectorPushBack(vec, (void *)6);
	VectorPushBack(vec, (void *)'H');
	
	REQUIRE((void *)8 ==  VectorGetElement(vec, 0));
	REQUIRE((void *)7 ==  VectorGetElement(vec, 1));
	REQUIRE((void *)6 ==  VectorGetElement(vec, 2));
	REQUIRE((void *)'H' ==  VectorGetElement(vec, 3));

	VectorDestroy(vec);
	return PASSED;
}
static test_status_t TestVectorReserve()
{
	Vector_t *vec = VectorCreate(20);
	REQUIRE(0 == VectorReserve(vec, 24));
	REQUIRE(0 == VectorReserve(vec, 26));
	REQUIRE(0 == VectorReserve(vec, 28));
	REQUIRE(0 == VectorReserve(vec, 20));
	VectorDestroy(vec);
	return PASSED;
}

static test_status_t TestVectorShrinkToFit()
{
	Vector_t *vec = VectorCreate(20);
	VectorPushBack(vec, (void *)8);
	VectorPushBack(vec, (void *)7);
	VectorPushBack(vec, (void *)6);
	VectorPushBack(vec, (void *)'H');
	REQUIRE(0 == VectorShrinkToFit(vec));
	REQUIRE(4 == VectorCapacity(vec));
	VectorDestroy(vec);
	return PASSED;
}