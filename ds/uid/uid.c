#include <unistd.h> /*getpid*/
#include <limits.h> /*SHRT_MAX*/
#include <stdatomic.h>/*fetch_and_add*/
#include "uid.h"

#define TIME_FAIL ((time_t)-1)
#define MAX_PID SHRT_MAX
 /*reviewed by daher*/

static pid_t UIDGetPid(UID_t uid);
static void UIDSetPid(UID_t *uid, pid_t pid);

static time_t UIDGetTime(UID_t uid);
static void UIDSetTime(UID_t *uid, time_t timestamp);

static size_t UIDGetCounter(UID_t uid);
static void UIDSetCounter(UID_t *uid, size_t counter);

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


static pid_t UIDGetPid(UID_t uid)
{
	return uid.pid;
}
static void UIDSetPid(UID_t *uid, pid_t pid)
{
	uid->pid = pid;
}
static time_t UIDGetTime(UID_t uid)
{
	return uid.time_stamp;
}
static void UIDSetTime(UID_t *uid, time_t timestamp)
{
	uid->time_stamp = timestamp;
}
static size_t UIDGetCounter(UID_t uid)
{
	return uid.counter;
}
static void UIDSetCounter(UID_t *uid, size_t counter)
{
	uid->counter = counter;
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