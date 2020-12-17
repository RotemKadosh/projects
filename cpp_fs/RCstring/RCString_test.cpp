
#include "RCString_adv.hpp"
#include "../../ds/utils/test.h"
#include <cstring> //strcmp
#include <iostream>//cout cin
using namespace ilrd;
test_status_t LengthToCstrTest()
{
    RCString s1("hello");
    RCString s2("");
    RCString s3("     name ");
    RCString s4("hello my name");
    RCString s5;
    
    REQUIRE(0 == strcmp(s1.ToCStr(), "hello"));
    REQUIRE(5 == s1.Length());

    
    REQUIRE(0 == strcmp(s2.ToCStr(), ""));
    REQUIRE(0 == s2.Length());

    
    REQUIRE(0 == strcmp(s3.ToCStr(), "     name "));
    REQUIRE(10 == s3.Length());

    
    REQUIRE(0 == strcmp(s4.ToCStr(), "hello my name"));
    REQUIRE(13 == s4.Length());

    
    REQUIRE(0 == strcmp(s5.ToCStr(), ""));
    REQUIRE(0 == s5.Length());

    return PASSED;
}

test_status_t PlusConcatTest()
{
    RCString rc1 = "hello ";
    RCString rc2 = "my name is";
    RCString rc3 = "";

    const char *cmp = "hello my name is";
    RCString rc4 = rc1 + rc2;
    REQUIRE(0 == strcmp(rc4.ToCStr(), cmp));
    REQUIRE(0 == strcmp(cmp, rc1.Concat(rc2).ToCStr()));

    const char *cmp1 = "my name is";
    RCString rc5 = rc2 + rc3;
    REQUIRE(0 == strcmp(rc5.ToCStr(), cmp1));
    REQUIRE(0 == strcmp(cmp1, rc2.Concat(rc3).ToCStr()));

    RCString rc6 = "hello ";
    const char *cmp2 = "hello hello ";
    RCString rc7 = rc6 + rc6;
    REQUIRE(0 == strcmp(rc7.ToCStr(), cmp2));
    REQUIRE(0 == strcmp(cmp2, rc6.Concat(rc6).ToCStr()));

    return PASSED;

}

test_status_t AssignCopyIsSharedTest()
{
    RCString s1("hello");
    REQUIRE(false == s1.IsShared());
    RCString s2(s1);
    REQUIRE(true == s1.IsShared());
    REQUIRE(0 == strcmp(s1.ToCStr(), s2.ToCStr()));
    
    RCString s3("");
    RCString s4(s3);
    REQUIRE(0 == strcmp(s3.ToCStr(), s4.ToCStr()));
    
    RCString s5("   ");
    RCString s6(s5);
    REQUIRE(0 == strcmp(s5.ToCStr(), s6.ToCStr()));
    
    RCString s7("* &@may* *");
    RCString s8(s7);
    REQUIRE(0 == strcmp(s7.ToCStr(), s8.ToCStr()));

    REQUIRE(1 == s2.IsShared());
    
    s1 = s8;
    REQUIRE(0 == strcmp(s1.ToCStr(), s8.ToCStr()));
    REQUIRE(0 == s2.IsShared());
    s5 = s3;
    REQUIRE(0 == strcmp(s5.ToCStr(), s3.ToCStr()));
    s2 = s7;
    REQUIRE(0 == strcmp(s2.ToCStr(), s7.ToCStr()));


    return PASSED;
}

test_status_t IOTest()
{

    RCString s1("hello");
    RCString s2("&&@@##");
    RCString s3("");    
    std::cout << s1 <<'\n';
    std::cout << s2 <<'\n';
    std::cout << s3 <<'\n';
    std::cout << "insert new string\n";
    std::cin >> s1;
    std::cout << s1 <<'\n';
    return PASSED;
}

test_status_t OpTest()
{
    RCString s1("hello");
    RCString s2("HELLO");
    
    RCString s3("my");
    RCString s4("123");
    
    RCString s5("name");
    RCString s6("s5");
    
    RCString s7("rotem");
    RCString s8("rotem");

    REQUIRE(s1 > s2);
    REQUIRE(s3 > s4);
    REQUIRE(s7 == s8);
    REQUIRE(s7 == "rotem");
    REQUIRE(s1 > "HELLO");
    REQUIRE(s3 > "123");
    REQUIRE("123" < s3);
    REQUIRE("abc" < s6);
    REQUIRE("" < s3);
    return PASSED;
  
}

test_status_t ProxyTest()
{
    const RCString rc1 = "rotem";
    REQUIRE('m' == rc1[4]);
    REQUIRE('e' == rc1[3]);
    RCString rc2 = rc1;

    char t = rc2[2];

    REQUIRE('t' == t);

    REQUIRE(true == rc1.IsShared());
    REQUIRE(true == rc2.IsShared());
    rc2[3] = 'a';
    rc2[0] = rc2[1] = rc2[2] = rc2[3] ;

    REQUIRE(0 == strcmp("aaaam", rc2.ToCStr()));
    REQUIRE(0 == strcmp("rotem", rc1.ToCStr()));

    REQUIRE(false == rc1.IsShared());
    REQUIRE(false == rc2.IsShared());
    
    
    return PASSED;

}

int main()
{
    RUNTEST(PlusConcatTest);
    RUNTEST(LengthToCstrTest);
    
    RUNTEST(AssignCopyIsSharedTest);
    RUNTEST(IOTest);
    RUNTEST(OpTest);
    RUNTEST(ProxyTest);

    return 0;
}



