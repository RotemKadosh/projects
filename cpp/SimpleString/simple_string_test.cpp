#include "simple_string.hpp"
#include "../../ds/utils/test.h"
#include <cstring> //strcmp
#include <iostream>//cout cin
test_status_t StringLiteralTest();
test_status_t StringOtherTest();
test_status_t StringAssignTest();
test_status_t StringLengthTest();
test_status_t StringAdvanceTest();
test_status_t StringIOTest();

test_status_t StringLiteralTest()
{
    ilrd::String s1("hello");
    REQUIRE(0 == strcmp(s1.CStr(), "hello"));
    ilrd::String s2("my");
    REQUIRE(0 == strcmp(s2.CStr(), "my"));
    ilrd::String s3("name");
    REQUIRE(0 == strcmp(s3.CStr(), "name"));
    ilrd::String s4("is");
    REQUIRE(0 == strcmp(s4.CStr(), "is"));
    ilrd::String s5("rotem");
    REQUIRE(0 == strcmp(s5.CStr(), "rotem"));
    return PASSED;
}

test_status_t StringOtherTest()
{
    ilrd::String s1("hello");
    ilrd::String s2(s1);
    REQUIRE(0 == strcmp(s2.CStr(), s1.CStr()));
    ilrd::String s3("my");
    ilrd::String s4(s3);
    REQUIRE(0 == strcmp(s3.CStr(), s4.CStr()));
     ilrd::String s5("name");
    ilrd::String s6(s5);
    REQUIRE(0 == strcmp(s5.CStr(), s6.CStr()));

    ilrd::String s7("is");
    ilrd::String s8(s7);
    REQUIRE(0 == strcmp(s7.CStr(), s8.CStr()));

    ilrd::String s9("rotem");
    ilrd::String s10(s9);
    REQUIRE(0 == strcmp(s9.CStr(), s10.CStr()));

    return PASSED;

}

test_status_t StringAssignTest()
{
    ilrd::String s1("hello");
    ilrd::String s2(s1);
    
    ilrd::String s3("my");
    ilrd::String s4(s3);
    
    ilrd::String s5("name");
    ilrd::String s6(s5);
    
    ilrd::String s7("is");
    ilrd::String s8(s7);
    
    ilrd::String s9("rotem");
    ilrd::String s10(s9);

    s1 = s10;
    s2 = s9;
    s3 = s8;
    s4 = s7;
    s5 = s6;

    REQUIRE(0 == strcmp(s1.CStr(), s10.CStr()));
    REQUIRE(0 == strcmp(s2.CStr(), s9.CStr()));
    REQUIRE(0 == strcmp(s3.CStr(), s8.CStr()));
    REQUIRE(0 == strcmp(s4.CStr(), s7.CStr()));
    REQUIRE(0 == strcmp(s5.CStr(), s6.CStr()));

    return PASSED;
}

test_status_t StringLengthTest()
{
    ilrd::String s1("hello");
    ilrd::String s2(s1);
    
    ilrd::String s3("my");
    ilrd::String s4(s3);
    
    ilrd::String s5("name");
    ilrd::String s6(s5);
    
    ilrd::String s7("is");
    ilrd::String s8(s7);
    
    ilrd::String s9("rotem");
    ilrd::String s10(s9);

    REQUIRE(5 == s1.Length());
    REQUIRE(5 == s2.Length());
    REQUIRE(2 == s3.Length());
    REQUIRE(2 == s4.Length());
    REQUIRE(4 == s5.Length());
    REQUIRE(4 == s6.Length());
    REQUIRE(2 == s7.Length());
    REQUIRE(2 == s8.Length());
    REQUIRE(5 == s9.Length());
    REQUIRE(5 == s10.Length());
    return PASSED;
}

test_status_t StringAdvanceTest()
{
    ilrd::String s1("hello");
    ilrd::String s2("HELLO");
    
    ilrd::String s3("my");
    ilrd::String s4("123");
    
    ilrd::String s5("name");
    ilrd::String s6("s5");
    
    ilrd::String s7("is");
    ilrd::String s8("IS");
    
    ilrd::String s9("rotem");
    ilrd::String s10("rotem");

    REQUIRE(s1 > s2);
    REQUIRE(s3 > s4);
    REQUIRE("is" == s7);
    REQUIRE(s9 == s10);
    REQUIRE(s9 == "rotem");
    REQUIRE(s1 > "HELLO");
    REQUIRE(s3 > "123");
    REQUIRE("123" < s3);
    return PASSED;
  
}

test_status_t StringIOTest()
{

    ilrd::String s1("rotem");
    ilrd::String s2("is me");

    std::cout << s1 ;
    std::cout << s2 << std::endl;
    std::cin >> s1;
    std::cout << s1;
   return PASSED;
}

int main()
{
    RUNTEST(StringLiteralTest);
    RUNTEST(StringOtherTest);
    RUNTEST(StringAssignTest);
    RUNTEST(StringLengthTest);
    RUNTEST(StringAdvanceTest);
    RUNTEST(StringIOTest);
    return 0;
}



