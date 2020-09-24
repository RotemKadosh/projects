#ifndef __UID_H__
#define __UID_H__

#include <stddef.h> /* size_t */
#include <time.h> /*time_t*/

typedef struct uid
{
	size_t pid;
	time_t time_stamp;
	size_t counter;

}Uid_t;

/*DESCRIPTION: 
*creates Uid instance with given Pid and appropriate time stamp and counter;
*
*		@param
*		pid - the process id of the process who calls this function
*
*@return
*return Uid on success, BadUid - on failuer;
*/
Uid_t UidCreate(size_t pid);

/*DESCRIPTION: 
*compare if two Uids are the same;
*
*		@param
*		one - uid to compare
*		two - uid to compare
*
*@return
*return 1 if the uids are the same, 0 if not.
*/
int UidIsSame(Uid_t one, Uid_t two);

/*DESCRIPTION: 
*create an instance of Bad Uid;
*
*		@param
*		
*		
*@return
*return Uid with values of bad uid;
*/
Uid_t UidGetBadUid();


#endif /* __NAME_H__*/