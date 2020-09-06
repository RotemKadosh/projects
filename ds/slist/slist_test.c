#include "../utils/test.h" /* Require, RUNTEST */
#include "slist.h"




static test_status_t TestSlistCreate();
static test_status_t TestSlistInsert();
static test_status_t TestSlistRemove();
static test_status_t TestSlistIsSameIter();
static test_status_t TestSlistCount();
static test_status_t TestSlistFind();
static test_status_t TestSlistGetAndSetData();
static test_status_t TestSlistForEach();
static test_status_t TestSlistAppend();

int main()
{
	RUNTEST(TestSlistCreate);
	RUNTEST(TestSlistInsert);
	RUNTEST(TestSlistRemove);
	RUNTEST(TestSlistIsSameIter);
	RUNTEST(TestSlistCount);
	RUNTEST(TestSlistFind);
	RUNTEST(TestSlistGetAndSetData);
	RUNTEST(TestSlistForEach);
	RUNTEST(TestSlistAppend);
	return 0;
}

static test_status_t TestSlistCreate()
{
	Slist_t *slist = SlistCreate();
	REQUIRE(NULL != slist);
	SlistDestroy(slist);
	return PASSED;
}
static test_status_t TestSlistInsert()
{
	Slist_t *slist = SlistCreate();
	Slist_iter_t where = SlistBegin(slist);
	REQUIRE(where == SlistInsert(where,(void *)8));
	REQUIRE(where == SlistInsert(where,(void *)8));
	REQUIRE(where == SlistInsert(where,(void *)'c'));
	REQUIRE(where == SlistInsert(where,(void *)8));
	REQUIRE(where == SlistInsert(where,(void *)'f'));
	SlistDestroy(slist);
	return PASSED;
}
static test_status_t TestSlistRemove()
{
	Slist_t *slist = SlistCreate();
	Slist_iter_t where = SlistBegin(slist);
	where = SlistInsert(where,(void *)8);
	where = SlistInsert(where,(void *)8);
	where = SlistInsert(where,(void *)8);
	where = SlistInsert(where,(void *)10);


	REQUIRE(4 == SlistCount(slist));
	where = SlistRemove(where);
	REQUIRE(3 == SlistCount(slist));
	where = SlistRemove(where);
	REQUIRE(2 == SlistCount(slist));
	where = SlistRemove(where);
	REQUIRE(1 == SlistCount(slist));
	SlistDestroy(slist);
	return PASSED;
}
static test_status_t TestSlistIsSameIter()
{
	Slist_t *slist = SlistCreate();
	Slist_iter_t head = SlistBegin(slist);
	Slist_iter_t tail = SlistEnd(slist);
	Slist_iter_t where = NULL;
	REQUIRE(SlistIsSameIter(head, tail));
	
	where = SlistInsert(tail,(void *)8);
	head = SlistBegin(slist);
	tail = SlistEnd(slist);
	REQUIRE(!SlistIsSameIter(head, tail));
	
	SlistRemove(where);
	head = SlistBegin(slist);
	tail = SlistEnd(slist);
	REQUIRE(SlistIsSameIter(head, tail));
	
	where = SlistInsert(head,(void *)8);
	head = SlistBegin(slist);
	tail = SlistEnd(slist);
	REQUIRE(!SlistIsSameIter(head, tail));
	
	SlistRemove(where);
	head = SlistBegin(slist);
	tail = SlistEnd(slist);
	
	REQUIRE(SlistIsSameIter(head, tail));
	SlistDestroy(slist);
	return PASSED;
}
static test_status_t TestSlistCount()
{
	Slist_t *slist = SlistCreate();
	Slist_iter_t where = SlistBegin(slist);
	where = SlistInsert(where,(void *)8);
	where = SlistInsert(where,(void *)8);
	where = SlistInsert(where,(void *)8);
	where = SlistInsert(where,(void *)8);
	REQUIRE(4 == SlistCount(slist));
	where = SlistRemove(where);
	REQUIRE(3 == SlistCount(slist));
	where = SlistRemove(where);
	REQUIRE(2 == SlistCount(slist));
	where = SlistRemove(where);
	REQUIRE(1 == SlistCount(slist));
	where = SlistRemove(where);
	REQUIRE(0 == SlistCount(slist));
	SlistDestroy(slist);
	return PASSED;
}
int MatchInt(const void *data, const void *data_to_compare)
{

	return data == data_to_compare;
}
static test_status_t TestSlistFind()
{
  Slist_iter_t runner = NULL;
  Slist_iter_t to_comp = NULL;
  Slist_t *list = SlistCreate();
  REQUIRE(NULL != list);
  runner = SlistInsert(SlistBegin(list), (void *)5);
  SlistInsert(SlistEnd(list), (void *)'h');
  SlistInsert(SlistEnd(list), (void *)2);
  SlistInsert(SlistEnd(list), (void *)'v');
  to_comp = SlistFind(SlistBegin(list), SlistEnd(list), (void *)5, MatchInt);
  REQUIRE(1 == SlistIsSameIter(runner ,to_comp));
  runner = SlistNext(runner);
  to_comp = SlistFind(SlistBegin(list), SlistEnd(list), (void *)'h', MatchInt);
  REQUIRE(1 == SlistIsSameIter(runner ,to_comp));
  SlistDestroy(list);
  return PASSED;
}
static test_status_t TestSlistGetAndSetData()
{
  Slist_iter_t runner = NULL;
  Slist_t *list = SlistCreate();
  runner = SlistInsert(SlistBegin(list), (void *)5);
  REQUIRE((void *)5 == SlistGetData(runner));
  SlistSetData(runner, (void *)8);
  REQUIRE((void *)8 == SlistGetData(runner));
  SlistDestroy(list);
  return PASSED;
}

int PrintIntList(void *data, void *param)
{
	static int count = 0;
	(void)param;
	printf("elemnet number:%d value is: %d\n",(int)(size_t)count, (int)(size_t)data);
	count++;
	return 0;
}
static test_status_t TestSlistForEach()
{
	void *param = 0;
	Slist_t *slist = SlistCreate();
	SlistInsert(SlistBegin(slist),(void *)8);
	SlistInsert(SlistBegin(slist),(void *)8);
	SlistInsert(SlistBegin(slist),(void *)8);
	SlistInsert(SlistBegin(slist),(void *)8);
	SlistForEach(SlistBegin(slist), SlistEnd(slist) , PrintIntList, param);
	SlistDestroy(slist);
	return PASSED;
}
static test_status_t TestSlistAppend()
{
	size_t size_before = 0;
	Slist_t *last = NULL;
	Slist_t *first = SlistCreate();
	SlistInsert(SlistBegin(first),(void *)8);
	SlistInsert(SlistBegin(first),(void *)8);
	SlistInsert(SlistBegin(first),(void *)8);
	SlistInsert(SlistBegin(first),(void *)8);
	last = SlistCreate();
	SlistInsert(SlistBegin(last),(void *)7);
	SlistInsert(SlistBegin(last),(void *)7);
	SlistInsert(SlistBegin(last),(void *)7);
	SlistInsert(SlistBegin(last),(void *)7);
	size_before = SlistCount(first) + SlistCount(last);
	SlistAppened(first, last);
	REQUIRE(size_before == SlistCount(first));
	SlistDestroy(first);

	return PASSED;
}