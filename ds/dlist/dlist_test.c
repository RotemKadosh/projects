#include "../utils/test.h"
#include "dlist.h"

#define TRUE (1)
#define FALSE (0)

static test_status_t DlistCreateTest();
static test_status_t DlistIsEmptyTest();
static test_status_t DlistSizeTest();
static test_status_t DlistInsertTest();
static test_status_t DlistRemoveTest();
static test_status_t DlistPushFrontTest();
static test_status_t DlistPushBackTest();
static test_status_t DlistPopFrontTest();
static test_status_t DlistPopBackTest();
static test_status_t DlistBeginTest();
static test_status_t DlistEndTest();
static test_status_t DlistIsSameIterTest();
static test_status_t DlistNextTest();
static test_status_t DlistPrevTest();
static test_status_t DlistGetDataTest();
static test_status_t DlistSetDataTest();
static test_status_t DlistFindTest();
static test_status_t DlistMultiFindTest();
static test_status_t DlistForEachTest();
static test_status_t DlistSpliceTest();

int UpDataByPram(void *data, void *param);
int MatchInt(const void *data, const void *data_to_compare);

int main()
{
	RUNTEST(DlistCreateTest);
	RUNTEST(DlistIsEmptyTest);
	RUNTEST(DlistSizeTest);
	RUNTEST(DlistInsertTest);
	RUNTEST(DlistRemoveTest);
	RUNTEST(DlistPushFrontTest);
	RUNTEST(DlistPushBackTest);
	RUNTEST(DlistPopFrontTest);
	RUNTEST(DlistPopBackTest);
	RUNTEST(DlistBeginTest);
	RUNTEST(DlistEndTest);
	RUNTEST(DlistIsSameIterTest);
	RUNTEST(DlistNextTest);
	RUNTEST(DlistPrevTest);
	RUNTEST(DlistGetDataTest);
	RUNTEST(DlistSetDataTest);
	RUNTEST(DlistFindTest);
	RUNTEST(DlistMultiFindTest);
	RUNTEST(DlistForEachTest);
	RUNTEST(DlistSpliceTest);
	return 0; 
}
int UpDataByPram(void *data, void *param)
{
	*(int *)data += *(int *)param;
	return 0;
}
int MatchInt(const void *data, const void *data_to_compare)
{

	return *(int *)data == *(int *)data_to_compare;
}

static test_status_t DlistCreateTest()
{
	Dlist_t *list = DlistCreate();
	REQUIRE(NULL != list);
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistIsEmptyTest()
{
	Dlist_t *list = DlistCreate();
	REQUIRE(TRUE == DlistIsEmpty(list));
	DlistInsert(list, DlistBegin(list), (void *)14);
	REQUIRE(FALSE == DlistIsEmpty(list));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistInsertTest()
{
	Dlist_t *list = DlistCreate();
	Dlist_iter_t where = DlistBegin(list);
	Dlist_iter_t inserted = DlistInsert(list, where,(void *)8);
	REQUIRE(8 == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)8);
	REQUIRE(8 == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)'c');
	REQUIRE('c' == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)'g');
	REQUIRE('g' == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)100);
	REQUIRE(100 == (int)(size_t)DlistGetData(inserted));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistBeginTest()
{
	Dlist_t *list = DlistCreate();
	DlistInsert(list, DlistBegin(list), (void *)8);
	REQUIRE((void *)8 == DlistGetData(DlistBegin(list)));
	DlistInsert(list, DlistBegin(list), (void *)9);
	REQUIRE((void *)9 == DlistGetData(DlistBegin(list)));
	DlistInsert(list, DlistBegin(list), (void *)'c');
	REQUIRE((void *)'c' == DlistGetData(DlistBegin(list)));
	DlistInsert(list, DlistBegin(list), (void *)'8');
	REQUIRE((void *)'8' == DlistGetData(DlistBegin(list)));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistEndTest()
{
	Dlist_t *list = DlistCreate();
	DlistInsert(list, DlistEnd(list), (void *)8);
	REQUIRE((void *)list == DlistGetData(DlistEnd(list)));
	DlistInsert(list, DlistEnd(list), (void *)9);
	REQUIRE((void *)list == DlistGetData(DlistEnd(list)));
	DlistInsert(list, DlistEnd(list), (void *)'c');
	REQUIRE((void *)list == DlistGetData(DlistEnd(list)));
	DlistInsert(list, DlistEnd(list), (void *)'8');
	REQUIRE((void *)list == DlistGetData(DlistEnd(list)));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistNextTest()
{
	Dlist_t *list = DlistCreate();
	Dlist_iter_t inserted = NULL;
	inserted = DlistInsert(list, DlistEnd(list), (void *)9);
	inserted = DlistInsert(list, DlistEnd(list), (void *)9);
	REQUIRE(inserted == DlistNext(DlistBegin(list)));
	inserted = DlistInsert(list, DlistBegin(list), (void *)9);
	REQUIRE(DlistNext(inserted) == DlistNext(DlistBegin(list)));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistPrevTest()
{
	Dlist_t *list = DlistCreate();
	Dlist_iter_t inserted = NULL;
	Dlist_iter_t prev = NULL;
	inserted = DlistInsert(list, DlistEnd(list), (void *)1);
	inserted = DlistInsert(list, DlistEnd(list), (void *)2);
	inserted = DlistInsert(list, DlistEnd(list), (void *)3);
	inserted = DlistInsert(list, DlistEnd(list), (void *)4);
	prev = DlistPrev(inserted);
	REQUIRE((void *)3 == DlistGetData(prev));
	prev = DlistPrev(prev);
	REQUIRE((void *)2 == DlistGetData(prev));
	prev = DlistPrev(prev);
	REQUIRE((void *)1 == DlistGetData(prev));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistIsSameIterTest()
{
	Dlist_t *list = DlistCreate();
	REQUIRE(TRUE == DlistIsSameIter(DlistBegin(list),DlistEnd(list)));
	DlistInsert(list, DlistBegin(list), (void *)'v');
	REQUIRE(FALSE == DlistIsSameIter(DlistBegin(list),DlistEnd(list)));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistGetDataTest()
{
	Dlist_t *list = DlistCreate();
	Dlist_iter_t where = DlistBegin(list);
	Dlist_iter_t inserted = DlistInsert(list, where,(void *)8);
	REQUIRE(8 == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)8);
	REQUIRE(8 == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)'c');
	REQUIRE('c' == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)'g');
	REQUIRE('g' == (int)(size_t)DlistGetData(inserted));
	inserted = DlistInsert(list, where,(void *)100);
	REQUIRE(100 == (int)(size_t)DlistGetData(inserted));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistSetDataTest()
{
	Dlist_t *list = DlistCreate();
	Dlist_iter_t where = DlistBegin(list);
	Dlist_iter_t inserted = DlistInsert(list, where,(void *)8);
	DlistSetData(inserted, (void *)'c');
	REQUIRE((void *)'c' == DlistGetData(inserted));
	DlistSetData(inserted, (void *)'d');
	REQUIRE((void *)'d' == DlistGetData(inserted));
	DlistSetData(inserted, (void *)25);
	REQUIRE((void *)25 == DlistGetData(inserted));
	DlistSetData(inserted, (void *)1);
	REQUIRE((void *)1 == DlistGetData(inserted));
	DlistSetData(inserted, (void *)'c');
	REQUIRE((void *)'c' == DlistGetData(inserted));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistRemoveTest()
{
	Dlist_t *list = DlistCreate();
	Dlist_iter_t where = DlistInsert(list, DlistBegin(list), (void *)14);
	REQUIRE(FALSE == DlistIsEmpty(list));
	DlistRemove(list, where);
	REQUIRE(TRUE == DlistIsEmpty(list));
	where = DlistInsert(list, DlistBegin(list), (void *)14);
	REQUIRE(FALSE == DlistIsEmpty(list));
	DlistRemove(list, where);
	REQUIRE(TRUE == DlistIsEmpty(list));
	DlistDestroy(list);
	return PASSED;	
}
static test_status_t DlistPushFrontTest()
{
	Dlist_t *list = DlistCreate();
	DlistPushFront(list, (void *)8);
	REQUIRE((void *)8 == DlistGetData(DlistBegin(list)));
	DlistPushFront(list, (void *)9);
	REQUIRE((void *)9 == DlistGetData(DlistBegin(list)));
	DlistPushFront(list, (void *)10);
	REQUIRE((void *)10 == DlistGetData(DlistBegin(list)));
	DlistPushFront(list, (void *)6);
	REQUIRE((void *)6 == DlistGetData(DlistBegin(list)));
	DlistPushFront(list, (void *)'c');
	REQUIRE((void *)'c' == DlistGetData(DlistBegin(list)));
	DlistPushFront(list, (void *)'h');
	REQUIRE((void *)'h' == DlistGetData(DlistBegin(list)));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistPushBackTest()
{
	Dlist_t *list = DlistCreate();
	DlistPushBack(list, (void *)8);
	REQUIRE((void *)8 == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPushBack(list, (void *)9);
	REQUIRE((void *)9 == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPushBack(list, (void *)10);
	REQUIRE((void *)10 == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPushBack(list, (void *)6);
	REQUIRE((void *)6 == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPushBack(list, (void *)'c');
	REQUIRE((void *)'c' == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPushBack(list, (void *)'h');
	REQUIRE((void *)'h' == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistPopFrontTest()
{
	Dlist_t *list = DlistCreate();
	DlistPushFront(list, (void *)8);
	DlistPushFront(list, (void *)9);
	DlistPushFront(list, (void *)10);
	DlistPushFront(list, (void *)6);
	DlistPushFront(list, (void *)'c');
	DlistPushFront(list, (void *)'h');
	REQUIRE((void *)'h' == DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE((void *)'c' == DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE((void *)6 == DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE((void *)10 == DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE((void *)9 == DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE((void *)8 == DlistGetData(DlistBegin(list)));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistPopBackTest()
{
	Dlist_t *list = DlistCreate();
	DlistPushBack(list, (void *)8);
	DlistPushBack(list, (void *)9);
	DlistPushBack(list, (void *)10);
	DlistPushBack(list, (void *)6);
	DlistPushBack(list, (void *)'c');
	DlistPushBack(list, (void *)'h');
	REQUIRE((void *)'h' == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPopBack(list);
	REQUIRE((void *)'c' == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPopBack(list);
	REQUIRE((void *)6 == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPopBack(list);
	REQUIRE((void *)10 == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistPopBack(list);
	REQUIRE((void *)9 == DlistGetData(DlistPrev(DlistEnd(list))));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistSizeTest()
{
	Dlist_t *list = DlistCreate();
	DlistPushBack(list, (void *)8);
	REQUIRE(1 == DlistSize(list));
	DlistPushBack(list, (void *)9);
	REQUIRE(2 == DlistSize(list));
	DlistPushBack(list, (void *)10);
	REQUIRE(3 == DlistSize(list));
	DlistPushBack(list, (void *)6);
	REQUIRE(4 == DlistSize(list));
	DlistPushBack(list, (void *)'c');
	REQUIRE(5 == DlistSize(list));
	DlistPushBack(list, (void *)'h');
	REQUIRE(6 == DlistSize(list));
	
	DlistPopBack(list);
	REQUIRE(5 == DlistSize(list));
	DlistPopBack(list);
	REQUIRE(4 == DlistSize(list));
	DlistPopBack(list);
	REQUIRE(3 == DlistSize(list));
	DlistPopBack(list);
	REQUIRE(2 == DlistSize(list));
	DlistPopBack(list);
	REQUIRE(1 == DlistSize(list));
	DlistPopBack(list);
	REQUIRE(0 == DlistSize(list));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistForEachTest()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	int to_add = 10;
	Dlist_t *list = DlistCreate();
	DlistPushFront(list,(void *)&a);
	DlistPushFront(list,(void *)&b);
	DlistPushFront(list,(void *)&c);
	DlistPushFront(list,(void *)&d);
	DlistForEach(DlistBegin(list), DlistEnd(list), UpDataByPram, (void *)&to_add);
	REQUIRE(14 == *(int *)DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE(13 == *(int *)DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE(12 == *(int *)DlistGetData(DlistBegin(list)));
	DlistPopFront(list);
	REQUIRE(11 == *(int *)DlistGetData(DlistBegin(list)));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistFindTest()
{
	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;
	Dlist_t *list = DlistCreate();
	DlistPushFront(list,(void *)&a);
	DlistPushFront(list,(void *)&b);
	DlistPushFront(list,(void *)&c);
	DlistPushFront(list,(void *)&d);
	REQUIRE(d == *(int *)DlistGetData(DlistFind(DlistBegin(list), DlistEnd(list), MatchInt, &d )));
	REQUIRE(c == *(int *)DlistGetData(DlistFind(DlistBegin(list), DlistEnd(list), MatchInt, &c )));
	REQUIRE(b == *(int *)DlistGetData(DlistFind(DlistBegin(list), DlistEnd(list), MatchInt, &b )));
	DlistDestroy(list);
	return PASSED;
}
static test_status_t DlistMultiFindTest()
{
	int a = 1;
	int b = 2;
	int d = 4;
	Dlist_t *dest = DlistCreate();
	Dlist_t *list = DlistCreate();
	DlistPushFront(list,(void *)&a);
	DlistPushFront(list,(void *)&b);
	DlistPushFront(list,(void *)&a);
	DlistPushFront(list,(void *)&d);
	DlistMultiFind(dest, DlistBegin(list), DlistEnd(list), MatchInt, &a);
	REQUIRE(2 == DlistSize(dest));
	DlistPushFront(list,(void *)&a);
	DlistPushFront(list,(void *)&a);
	DlistMultiFind(dest, DlistBegin(list), DlistEnd(list), MatchInt, &a);
	REQUIRE(6 == DlistSize(dest));
	DlistDestroy(list);
	DlistDestroy(dest);
	return PASSED;
}
static test_status_t DlistSpliceTest()
{

	int a = 1;
	int b = 2;
	int d = 4;
	Dlist_iter_t where = NULL;
	Dlist_iter_t from = NULL;
	Dlist_iter_t to = NULL;


	Dlist_t *dest = DlistCreate();
	Dlist_t *src = DlistCreate();

	to = DlistPushFront(src,(void *)&a);
	DlistPushFront(src,(void *)&b);
	from =DlistPushFront(src,(void *)&a);
	DlistPushFront(src,(void *)&d);

	DlistPushFront(dest,(void *)&d);
	where = DlistPushFront(dest,(void *)&d);
	DlistPushFront(dest,(void *)&d);
	DlistPushFront(dest,(void *)&d);

	DlistSplice(where, from, to);
	REQUIRE(2 == DlistSize(src));
	REQUIRE(6 == DlistSize(dest));
	DlistDestroy(src);
	DlistDestroy(dest);
	return PASSED;
}


