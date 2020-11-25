#include <unistd.h> /*getpid*/
#include <limits.h> /*SHRT_MAX*/
#include <stdatomic.h>/*fetch_and_add*/
#include "uid.h"

#define TIME_FAIL ((time_t)-1)
#define MAX_PID SHRT_MAX
 /*reviewed by daher*/


static time_t UIDGetTime(UID_t uid);



static int UIDIsEqualTimes(UID_t uid_one, UID_t uid_two);

UID_t UIDCreate(void)
{
	static size_t counter = 1;
	UID_t uid = {0};
	time_t stamp = time(NULL);
	if(TIME_FAIL ==  stamp)
	{
		return UIDGetBadUid();
	}
	uid.time_stamp = stamp;
	uid.pid = getpid();
	uid.counter = atomic_fetch_add(&counter, 1);
	return uid;
}



static time_t UIDGetTime(UID_t uid)
{
	return uid.time_stamp;
}


static int UIDIsEqualTimes(UID_t uid_one, UID_t uid_two)
{
	return (UIDGetTime(uid_one) == UIDGetTime(uid_two));
}

int UIDIsSame(UID_t one, UID_t two)
{
	return ((one.pid == two.pid) && UIDIsEqualTimes(one, two) && (one.counter == two.counter));
}

UID_t UIDGetBadUid(void)
{
	UID_t uid = {0};
	return uid;
}

/*
static int UIDIsBadUid(UID_t uid)
{
	return (0 == UIDGetCounter(uid) && 0 == UIDGetTime(uid) && 0 == UIDGetPid(uid));
}
*/