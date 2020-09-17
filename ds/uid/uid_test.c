
#include "../utils/test.h" /*REQUIRE RUNTEST*/
#include <unistd.h> /*getpid*/
#include <stdio.h>
#include "uid.h"

#define TRUE (1)
#define FALSE (0)

int UIDtest(void);

int main()
{
	RUNTEST(UIDtest);
	return 0;
}

int UIDtest(void)
{
	UID_t bad_uid = UIDGetBadUid();
	UID_t uid = UIDCreate();
	UID_t uid2 = UIDCreate();
	UID_t uid3 = UIDCreate();

	REQUIRE(time(NULL) == UIDGetTime uid.time_stamp);
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