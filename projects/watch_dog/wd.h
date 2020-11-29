#ifndef __WD_H__
#define __WD_H__


/* DESCRIPTION: 
 * a program to insure reviving of the calling program in case of crash.
 * the SIGUSR1 and SIGUSR2 signals are been used by this program and should be 
 * reserved for it.
 *  
 */


/* DESCRIPTION: 
 * the function start the process that watch over the calling process
 * to stop the WD process and free all it resources a call to StopWd function
 * should be made
 *		@param
 *		argv - the arguments that the caller process should receave on rebooting,
 *             caanot be NULL; in very least should hold the name of the calling 
 *             executable file name
 *
 * @return
 * on success return 0,
 * if crating the user side thread fails return -1;
 */

int StartWd(char**argv);


/* DESCRIPTION: 
 * stop the wd process, free all resources taken by watch dog
 *		@param
 * 
 *
 * @return
 * 
 */
void StopWd(void);


#endif