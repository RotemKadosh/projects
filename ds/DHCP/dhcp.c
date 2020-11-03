#include "dhcp.h"
#include <stdlib.h> /*malloc free*/
#include <assert.h> /*assert*/
#include <stdio.h>/*sprintf*/
#include <string.h>/*strlen*/
#include <math.h>/*pow*/

#define ALL_1S (0Xffffffff)
#define ALL_0S (0x00000000)

#define NUM_OF_BIT_FOR_COMP(num_of_bit_for_network) (sizeof(int)*8 - num_of_bit_for_network)
#define TRUE (1)
#define FALSE (0)
typedef enum relatives
{
    ZERO,
    ONE,
    NUM_OF_RELATIVES
} relatives;
struct Dhcp
{
    Dhcp_node_ty *root;
    size_t num_of_bits_for_network;
    unsigned int sub_net;
};
struct Dhcp_node
{
    Dhcp_node_ty *relatives[NUM_OF_RELATIVES];
    int is_full;
};

/*-----------------declerations ------------------------*/

static void DeleteAllNodes(Dhcp_node_ty *root);
static DHCP_status createInitalPaths(Dhcp_ty *dhcp);
static Dhcp_node_ty *CreateDhcpNode();

static DHCP_status AllocateRequestedIp(Dhcp_node_ty *sub_root, 
                                ip_ty *allocated_ip, ip_ty path, int num_of_bits);

static DHCP_status SmallestIpAvailable(Dhcp_node_ty *sub_root, ip_ty *allocated_ip,
                                 unsigned int num_of_bit_for_comp);
static int IsRequestedInSubnet(Dhcp_ty *dhcp, ip_ty ip );



/*-------------------------service-----------------------*/
static void DeleteAllNodes(Dhcp_node_ty *root)
{
    if(root == NULL)
    {
        return;
    }
    DeleteAllNodes(root->relatives[ZERO]);
    DeleteAllNodes(root->relatives[ONE]);
    free(root);
    root = NULL;
}

static DHCP_status createInitalPaths(Dhcp_ty *dhcp)
{
    ip_ty broadcast = (dhcp->sub_net) | (ALL_1S >> dhcp->num_of_bits_for_network) ;
    ip_ty brod_ret = 0;
    ip_ty net = dhcp->sub_net;
    ip_ty net_ret = 0;
    int ansb = 0;
    int ansn = 0;
    
    ansb = DhcpAllocateIp(dhcp, &brod_ret, broadcast);
    ansn = DhcpAllocateIp(dhcp, &net_ret, net);
    if(ansb != SUCCESS || ansn != SUCCESS)
    {
        DhcpDestroy(dhcp);
        dhcp = NULL;
        return MALLOC_FAILURE;
    }
    return ansb;
  
    
}

static Dhcp_node_ty *CreateDhcpNode()
{
    Dhcp_node_ty *node = malloc(sizeof(Dhcp_node_ty));
    if(NULL != node)
    {
        node->is_full = 0;
        node->relatives[ZERO]= NULL;
        node->relatives[ONE]= NULL;
    }
    return node;
}

static DHCP_status AllocateRequestedIp(Dhcp_node_ty *sub_root, ip_ty *allocated_ip, ip_ty path, int num_of_bits)
{
    int side = 0;
    int status = SUCCESS;
    ip_ty mask = (ONE << (num_of_bits - 1));
    mask = (path & mask); 
    side = mask >> (num_of_bits - 1);
    
    if(0 == num_of_bits )
    {
        *allocated_ip = *allocated_ip | mask;
        sub_root->is_full = TRUE;
        return SUCCESS;
    }
    if(NULL == sub_root->relatives[side])
    {
        sub_root->relatives[side] = CreateDhcpNode();
        if(sub_root->relatives[side] == NULL)
        {
            return MALLOC_FAILURE;
        }
    }
    if(sub_root->relatives[side]->is_full)
    {
        return DOUBLE_FREE;
    }
    else
    {
        *allocated_ip = *allocated_ip | mask; 
        status = AllocateRequestedIp(sub_root->relatives[side], allocated_ip,
                                                path,num_of_bits - 1);
        if(status != SUCCESS)
        {
            return status;
        }
    }
    if(sub_root->relatives[side]->is_full && sub_root->relatives[!side] != NULL && 
                                         sub_root->relatives[!side]->is_full)
    {
        sub_root->is_full = TRUE;
    }
    return status;
}

static DHCP_status SmallestIpAvailable(Dhcp_node_ty *sub_root, ip_ty *allocated_ip,
                                             unsigned int num_of_bit)
{
    int status = SUCCESS;
    if(NULL == sub_root->relatives[ZERO])
    {
        sub_root->relatives[ZERO] = CreateDhcpNode();
        if(sub_root->relatives[ZERO] == NULL)
        {
            return MALLOC_FAILURE;
        }
    }
    if(!sub_root->relatives[ZERO]->is_full)
    {
        if(num_of_bit == 1)
        {
            sub_root->relatives[ZERO]->is_full = TRUE;
        }
        else
        {
            status = SmallestIpAvailable(sub_root->relatives[ZERO], allocated_ip, num_of_bit - 1);
            if(status != SUCCESS)
            {
                return MALLOC_FAILURE;
            }
        }
    }
    else
    {
        if(NULL == sub_root->relatives[ONE])
        {
            sub_root->relatives[ONE] = CreateDhcpNode();
            if(sub_root->relatives[ONE] == NULL)
            {
                return MALLOC_FAILURE;
            } 
        }
        if(!sub_root->relatives[ONE]->is_full)
        {
            *allocated_ip = *allocated_ip | (ONE << (num_of_bit -1));
            if(num_of_bit == 1)
            {
                sub_root->relatives[ONE]->is_full = TRUE;
            }
            else
            {
                status = SmallestIpAvailable(sub_root->relatives[ONE], allocated_ip, num_of_bit - 1);
                if(status != SUCCESS)
                {
                    return MALLOC_FAILURE;
                }
            }
        }
        else
        {
            return MALLOC_FAILURE;
        }  
    }

    if(sub_root->relatives[ZERO]->is_full && sub_root->relatives[ONE] != NULL && sub_root->relatives[ONE]->is_full)
    {
        sub_root->is_full = TRUE;
    }
    return status;
}

static int IsRequestedInSubnet(Dhcp_ty *dhcp, ip_ty ip )
{
    ip_ty o = (ip >> NUM_OF_BIT_FOR_COMP(dhcp->num_of_bits_for_network));
    ip_ty t = (dhcp->sub_net >> NUM_OF_BIT_FOR_COMP(dhcp->num_of_bits_for_network));
    if( o == t)
    {
        return TRUE;
    }
    return FALSE;
}

static int FreeRequestedIp(Dhcp_node_ty *sub_root, ip_ty ip, unsigned int num_of_bits)
{
    int side = 0;
    int status = SUCCESS;
    ip_ty mask = (ONE << (num_of_bits - 1));
    mask = (ip & mask); 
    side = mask >> (num_of_bits - 1);
    if(0 == num_of_bits )
    {
        if(sub_root->is_full)
        {   
            sub_root->is_full = FALSE;
            status = SUCCESS;
        }
        else
        {
            status = DOUBLE_FREE;
        }
        return status;
    }
    if(NULL == sub_root->relatives[side])
    {
        status = DOUBLE_FREE;
        return status;
    }
    else
    {
        status = FreeRequestedIp(sub_root->relatives[side], ip, num_of_bits -1);
    }

    if(!sub_root->relatives[side]->is_full || (sub_root->relatives[!side] != NULL && !sub_root->relatives[!side]->is_full))
    {
        sub_root->is_full = FALSE;
    }
    return status;
    
}

static size_t CountFullIp(Dhcp_node_ty *sub_root)
{
    if(sub_root == NULL)
    {
        return 0;
    }
    if(sub_root->relatives[ZERO] == NULL && sub_root->relatives[ONE] == NULL && sub_root->is_full)
    {
      return 1;  
    }
    return CountFullIp(sub_root->relatives[ZERO]) + CountFullIp(sub_root->relatives[ONE]);
}

/*-----------------------API----------------------------*/

void DhcpDestroy(Dhcp_ty *dhcp)
{
    DeleteAllNodes(dhcp->root);
    dhcp->root = NULL;
    free(dhcp);
    dhcp = NULL;
}

Dhcp_ty *DhcpCreate(ip_ty sub_net, size_t num_of_bits_for_network)
{
    Dhcp_ty *dhcp = NULL;
    int ans = SUCCESS;
  
    assert(0 != num_of_bits_for_network);

    dhcp = malloc(sizeof(dhcp));
    if(NULL != dhcp)
    {   
        dhcp->num_of_bits_for_network = num_of_bits_for_network;
        dhcp->sub_net = sub_net;
        dhcp->root = CreateDhcpNode();
        if(dhcp->root != NULL)
        {
            ans = createInitalPaths(dhcp);
            if(ans != SUCCESS)
            {
                free(dhcp);
                dhcp = NULL;
            }
        }
    }
    return dhcp;
}

char *IPToString(char *str_ip, ip_ty ip)
{
    char *str_ip_start = str_ip;
    int mask = 0Xff;

    /*right to left*/
    int byte1 = ip & mask;
    int byte2 = ((ip & (mask << 8) )>> 8);
    int byte3 = ((ip & (mask << 16)) >> 16);
    int byte4 = ((ip & (mask << 24)) >> 24);

    sprintf(str_ip, "%d.", byte4);
    str_ip += strlen(str_ip);
    sprintf(str_ip, "%d.", byte3);
    str_ip += strlen(str_ip);
    sprintf(str_ip, "%d.", byte2); 
    str_ip += strlen(str_ip);
    sprintf(str_ip, "%d", byte1); 
    str_ip += strlen(str_ip); 

    return str_ip_start; 
}

ip_ty StringToIp(char *ip)
{
    
    char *delim = ".";
    char *token = strtok(ip, delim);
    ip_ty ans_final = 0;
    int ans = atoi(token);
    ans_final ^= (ans << 24);

    token = strtok(NULL, delim);
    ans = atoi(token);
    ans_final ^= (ans << 16);

    token = strtok(NULL, delim);
    ans = atoi(token);
    ans_final ^= (ans << 8);

    token = strtok(NULL, delim);
    ans = atoi(token);
    ans_final ^= (ans );
    
    return ans_final;
    
}

DHCP_status DhcpAllocateIp(Dhcp_ty *dhcp, ip_ty *allocated_ip, ip_ty requested_ip)
{
    int status = SUCCESS;
    *allocated_ip = dhcp->sub_net;

    if(requested_ip != 0)
    {
        if(IsRequestedInSubnet(dhcp, requested_ip))
        {
            status = AllocateRequestedIp(dhcp->root, allocated_ip, requested_ip, NUM_OF_BIT_FOR_COMP(dhcp->num_of_bits_for_network));
            if(status == SUCCESS)
            {
                return status;
            }
        }

    }
    *allocated_ip = dhcp->sub_net;
    status = SmallestIpAvailable(dhcp->root,allocated_ip ,NUM_OF_BIT_FOR_COMP(dhcp->num_of_bits_for_network));
    return status;
}

DHCP_status DhcpRFreeIp(Dhcp_ty *Dhcp, ip_ty ip)
{
    int status = 0;
    status = FreeRequestedIp(Dhcp->root, ip, NUM_OF_BIT_FOR_COMP(Dhcp->num_of_bits_for_network));
    return status;
}

size_t DhcpCountFree(const Dhcp_ty *Dhcp)
{
    assert(NULL != Dhcp);
    return pow(2,NUM_OF_BIT_FOR_COMP(Dhcp->num_of_bits_for_network)) - CountFullIp(Dhcp->root); 
}























/*
CreatDhcp:

    create root node
    create right node * subnet times
    create left node * subnet times
    return pointer
*/


/*
allocateIp:
    if has preffered ip:
        if preffered is open:    
            return preffered
   
    return give smallest ip available
*/
/*
{
    char *char_runner = preffered;
    trie_node_ty *node_runner = dhcp->root;
    if(runner != NULL)
    {
        while('\0' != *runner)
        {
            if(FULL != node_runner->full)
            {

            }
        }
    }
}

*/


/*
free ip (1001...):
    start in root .
    if path == '\0':
        delete root
        return;
    else:
        free ip in direction by addres
        if node has no childrens:
            delete node

*/
/*
countFree:
        2^subnetMask -size of tree + the nodes that leads to 1 or zero
*/








































