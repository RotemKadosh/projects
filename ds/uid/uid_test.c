
#include "../utils/test.h" /*REQUIRE RUNTEST*/
#include <unistd.h> /*getpid*/
#include <stdio.h>
#include <pthread.h>
#include "uid.h"

#define TRUE (1)
#define FALSE (0)

int UIDtest(void);
int UIDThreadTest(void);

int main()
{
	RUNTEST(UIDThreadTest);
	return 0;
}

int UIDtest(void)
{
	UID_t bad_uid = UIDGetBadUid();
	UID_t uid = UIDCreate();
	UID_t uid2 = UIDCreate();
	UID_t uid3 = UIDCreate();

	REQUIRE(time(NULL) == uid.time_stamp);
	REQUIRE(1 == uid.counter);
	REQUIRE(getpid() == uid.pid);
	
	REQUIRE(2 == uid2.counter);
	REQUIRE(3 == uid3.counter);

	REQUIRE(0 == bad_uid.pid);
	REQUIRE(0 == bad_uid.time_stamp);
	REQUIRE(0 == bad_uid.counter);

	REQUIRE(TRUE == UIDIsSame(uid, uid));
	REQUIRE(FALSE == UIDIsSame(uid, bad_uid));

	return PASSED;
}

void *CreateUid(void *arg)
{
	*(UID_t *)arg = UIDCreate();
	return NULL;
}

int UIDThreadTest()
{
	pthread_t tid[12];
	UID_t uids[12];
    size_t i = 0;

	for(i = 0;i<12;i++)
	{
		pthread_create(&tid[i],0,CreateUid, uids + i);
	}
	for(i = 0; i < 12 ;i++)
	{
		pthread_join(tid[i], NULL);
	}
	for(i = 0; i < 12 ;i++)
	{
		printf("uid %ld: %ld\n",i, uids[i].counter);
	}
	return PASSED;
}