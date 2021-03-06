#include "../utils/test.h"
#include "dhcp.h"
#include <string.h>


static test_status_t CreateDestroyTest(void);
static test_status_t IpToStrTest(void);
static test_status_t StringToIpTest(void);
static test_status_t AllocateFreeTest(void);

int main()
{
    
    RUNTEST(IpToStrTest);
    RUNTEST(StringToIpTest);
    RUNTEST(CreateDestroyTest);
    RUNTEST(AllocateFreeTest);
    return 0;
}

static test_status_t AllocateFreeTest(void)
{
    int status = 0;
    char buffer[13] = "196.0.63.0";
    char buffer_req[13] = "196.0.63.4";

    char buffer1[13] = "196.0.63.1";
    char buffer2[13] = "196.0.63.2";
    char buffer3[13] = "196.0.63.3";
    char buffer5[13] = "196.0.63.5";
    char buffer6[13] = "196.0.63.6";

    ip_ty subnet = StringToIp(buffer);
    ip_ty requested = StringToIp(buffer_req);

    ip_ty ans = 0;
    ip_ty ans2 = 0;

    int number_of_bit_net = 29;

    Dhcp_ty *dhpc = DhcpCreate(subnet, number_of_bit_net);
    REQUIRE(DhcpCountFree(dhpc) == 6);

    /*"196.0.63.4"*/
    status = DhcpAllocateIp(dhpc, &ans, requested);
    REQUIRE(requested == ans);
    REQUIRE(status == SUCCESS);
    REQUIRE(DhcpCountFree(dhpc) == 5);

    /*"196.0.63.1"*/
    ans = 0;
    ans2 = StringToIp(buffer1);
    status = DhcpAllocateIp(dhpc, &ans, 0);
    REQUIRE(ans == ans2);
    REQUIRE(status == SUCCESS);
    REQUIRE(DhcpCountFree(dhpc) == 4);

    status = DhcpRFreeIp(dhpc, ans);
    REQUIRE(status == SUCCESS);
    REQUIRE(DhcpCountFree(dhpc) == 5);


    status = DhcpRFreeIp(dhpc, ans);
    REQUIRE(status == DOUBLE_FREE);
    REQUIRE(DhcpCountFree(dhpc) == 5);



    
    /*"196.0.63.1"*/
    ans2 = 0;
    status = DhcpAllocateIp(dhpc, &ans2, 0);
    REQUIRE(status == SUCCESS);
    REQUIRE(ans == ans2);
    REQUIRE(DhcpCountFree(dhpc) == 4);
    
    /*"196.0.63.2"*/
    ans = 0;
    ans2 = StringToIp(buffer2);
    status = DhcpAllocateIp(dhpc, &ans, 0);
    REQUIRE(ans == ans2);
    REQUIRE(status == SUCCESS);
    REQUIRE(DhcpCountFree(dhpc) == 3);

    /*"196.0.63.3"*/
    ans = 0;
    ans2 = StringToIp(buffer3);
    status = DhcpAllocateIp(dhpc, &ans, requested);
    REQUIRE(ans == ans2);
    REQUIRE(status == SUCCESS);
    REQUIRE(DhcpCountFree(dhpc) == 2);

    /*"196.0.63.5"*/
    ans = 0;
    ans2 = StringToIp(buffer5);
    status = DhcpAllocateIp(dhpc, &ans, 0);
    REQUIRE(ans == ans2);
    REQUIRE(status == SUCCESS);
    REQUIRE(DhcpCountFree(dhpc) == 1);

    /*"196.0.63.6"*/
    ans = 0;
    ans2 = StringToIp(buffer6);
    status = DhcpAllocateIp(dhpc, &ans, 0);
    REQUIRE(status == SUCCESS);
    REQUIRE(ans == ans2);
    REQUIRE(DhcpCountFree(dhpc) == 0);


    /*"196.0.63.7"*/
    ans = 0;
    status = DhcpAllocateIp(dhpc, &ans, 0);
    REQUIRE(status == MALLOC_FAILURE);
    REQUIRE( 0 == DhcpCountFree(dhpc));

    ans = ans2;
    status = DhcpRFreeIp(dhpc, ans);
    REQUIRE(status == SUCCESS);
    REQUIRE(DhcpCountFree(dhpc) == 1);

    DhcpDestroy(dhpc);
    return PASSED;
}



static test_status_t CreateDestroyTest(void)
{
    Dhcp_ty *dhcp = DhcpCreate(3288350719,24);
    REQUIRE(NULL != dhcp);
    DhcpDestroy(dhcp);
    return PASSED;
}


static test_status_t IpToStrTest(void)
{
    char buffer[20] = {0};
    unsigned int ip = 3288350719;
    printf("%s\n", IPToString(&buffer[0], ip));
    REQUIRE(0 == strcmp(&buffer[0], "196.0.63.255"));

    return PASSED;
}

static test_status_t StringToIpTest(void)
{
    char buffer[13] = "196.0.63.255";
    unsigned int ip = StringToIp(buffer);
    
    REQUIRE(3288350719 == ip);
    return PASSED;
}

