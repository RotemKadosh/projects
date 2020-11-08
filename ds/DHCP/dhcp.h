#ifndef __Dhcp_H__
#define __Dhcp_H__

#include <stddef.h> /* size_t */

typedef struct Dhcp Dhcp_ty;
typedef struct Dhcp_node Dhcp_node_ty;
typedef unsigned int ip_ty;

/* -------------------FOR C FILE----------------------- */

/*---------------------------------------------------*/
typedef enum DHCP_status
{
    SUCCESS,
    DOUBLE_FREE,
    FREE_FAILURE,
    MALLOC_FAILURE
}DHCP_status;

/*DESCRIPTION: 
*create new Dhcp
*   @param
*       sub_net - string represents the network ip
*       sub_net_mask - number represents the occupied bits by network ip
*   @return
* pointer to the new Dhcp or NULL if failed
*          O(1)/O(m)-> m = number of bits reserved to computer/
*/
Dhcp_ty *DhcpCreate(ip_ty sub_net, size_t num_of_bits_for_network);

/*DESCRIPTION: 
*delete given Dhcp -free all allocated memory
*   @param
*       Dhcp - pointer to the Dhcp to delete
*   @return          
*/
void DhcpDestroy(Dhcp_ty *Dhcp);

/*DESCRIPTION: 
*allocates new ip for the device.
* may allocate specific requested ip,
* if taken will find the smallest ip address
* if requested ip not specified ('0') or already occupied or not part of *network address - the user will get the smallest ip address
*   @param
*       DHCP - pointer to the DHCP
*       requested_ip - the requested ip 
*       allocated_ip - the ip that been allocated
*   @return 
*       SUCCESS - for success allocate.
*       DOUBLE_FREE - if the ip allready free
*       MALLOC_FAILURE - failed to allocate new ip     
*/
DHCP_status DhcpAllocateIp(Dhcp_ty *dhcp, ip_ty *allocated_ip, ip_ty requested_ip);

/*DESCRIPTION: 
* converts ip to string
*undifiend behavior if not enough space in str_ip
*   @param
*       str_ip - pointer to alocated string
*       ip - ip to convert
*   @return
*       pointer to str with converted ip
*/
char *IPToString(char *str_ip, ip_ty ip);

/*DESCRIPTION: 
* converts string to ip
*undifiend behavior if ip is invalid
*   @param
*       ip - pointer to alocated string
*       
*   @return
*       ip_ty - converted ip
*/
ip_ty StringToIp(char *ip);

/*DESCRIPTION: 
* free given ip from dhcp, 
*
*   @param
*       Dhcp - pointer to Dhcp
*       ip - ip to free
*   @return
*   SUCCESS - for success free.
*   DOUBLE_FREE - if the ip allready free
*   FREE_FAILURE - if not exists or reserved
*/
DHCP_status DhcpRFreeIp(Dhcp_ty *Dhcp, ip_ty ip);

/*DESCRIPTION: 
* return the number of free ips in the dhcp the not located yet
*@param
*Dhcp - pointer to Dhcp
*@return
* the number of free ips
*/
size_t DhcpCountFree(const Dhcp_ty *Dhcp);

#endif /*__Dhcp_H__*/