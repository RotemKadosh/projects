#include "test.h"
#include "calc.h"

#define FALSE (0)
#define TRUE (1)

static test_status_t TestAdd(void);
static test_status_t TestSub(void);
static test_status_t TestMult(void);
static test_status_t TestDivide(void);
static test_status_t TestPow(void);
static test_status_t TestParantheses(void);
static test_status_t TestComplex(void);


int main(void)
{
    RUNTEST(TestAdd);
    RUNTEST(TestSub);
    RUNTEST(TestMult);
    RUNTEST(TestDivide);
    RUNTEST(TestPow);
    RUNTEST(TestParantheses);
    RUNTEST(TestComplex);


    return 0;
}


static test_status_t TestAdd(void)
{
    int exit_status = SUCCESS;
    REQUIRE(5 == Calculate("3+2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0 == Calculate("-2+2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("7.5+5.3", &exit_status) - 12.8);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(13 == Calculate("3+10", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(16 == Calculate("3+2+5+6", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("7.5+7.7", &exit_status) - 15.2);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(4 == Calculate("3+1", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(3 == Calculate("3+0", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(9 == Calculate("9", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    Calculate("5+",&exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("5.0.2",&exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("5+3.01.1",&exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    
    return PASSED;
}

static test_status_t TestSub(void)
{
    int exit_status = SUCCESS;
    REQUIRE(1 == Calculate("3-2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(-4 == Calculate("-2-2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(3 == Calculate("5-2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(-7 == Calculate("3-10", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(2 == Calculate("15-2-5-6", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(10 == Calculate("17-2-4-1", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(2 == Calculate("3-1", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.000001 > Calculate("7.5-5.3", &exit_status) - 2.2);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(9 == Calculate("9", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    Calculate("3-0.0.0", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);

    return PASSED;
}

static test_status_t TestMult(void)
{
    int exit_status = SUCCESS;
    REQUIRE(6 == Calculate("3*2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(-4 == Calculate("-2*2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(10 == Calculate("5*2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(30 == Calculate("3*10", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(900 == Calculate("15*2*5*6", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(-136 == Calculate("-17*2*4*1", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(3 == Calculate("3*1", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0 == Calculate("3*0", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(9 == Calculate("9", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    Calculate("3*0.01.1", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("5.0.2", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    return PASSED;
}

static test_status_t TestDivide(void)
{
    int exit_status = SUCCESS;
    REQUIRE(0.00001 > Calculate("3/2", &exit_status) - 1.5);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(-1 == Calculate("-2/2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(2.5 == Calculate("5/2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.3 == Calculate("3/10", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(1.5 == Calculate("15/2/5", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(-2.125 == Calculate("-17/2/4/1", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(3 == Calculate("3/1", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    Calculate("3/0", &exit_status);
    REQUIRE(exit_status == MATH_ERROR);
    exit_status = SUCCESS;
    Calculate("9/", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    return PASSED;
}

static test_status_t TestPow(void)
{
    int exit_status = SUCCESS;
    REQUIRE(0.00001 > Calculate("3^2", &exit_status) - 9);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("4^0.5", &exit_status) - 2);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5^0", &exit_status) - 1);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("0^10", &exit_status) - 0);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5^3", &exit_status) - 125);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5^01", &exit_status) - 5);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("4^3^2", &exit_status) - 262144);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("1^12", &exit_status) - 1);
    REQUIRE(exit_status == SUCCESS);
    Calculate("9^", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("^9", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("0^(-2)", &exit_status);
    REQUIRE(exit_status == MATH_ERROR);
    return PASSED;
}

static test_status_t TestParantheses(void)
{
    int exit_status = SUCCESS;
    REQUIRE(9 == Calculate("10-(3-2)", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(8 == Calculate("-5+(7+6)", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(2 == Calculate("7+(-5)", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(7 == Calculate("3+(1+1)^2", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(6 == Calculate("(6)", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(-5 == Calculate("(-5)", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(35 == Calculate("(4+3)*5", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(294 == Calculate("{4+(3+6)*5}*6", &exit_status));
    REQUIRE(exit_status == SUCCESS);
    Calculate("5+(5-7]", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("(9", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("{67{", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("{67)", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    exit_status = SUCCESS;
    Calculate("6+6}+67)", &exit_status);
    REQUIRE(exit_status == SYNTAX_ERROR);
    return PASSED;

}

static test_status_t TestComplex(void)
{
     int exit_status = SUCCESS;
    REQUIRE(0.00001 > Calculate("3^2+2+5-1", &exit_status) - 15);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("4^0.5-10+20+100/2", &exit_status) - 62);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5*0+100-36.6/9", &exit_status) - 95.9333333);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("0^10-189+49/7-8*5", &exit_status) - (-222));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5^3+15/3", &exit_status) - 130);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5^1+65-30*6/3", &exit_status) - 10);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("1^12", &exit_status) - 1);
    REQUIRE(0.00001 > Calculate("3^2+(2+{5+8}*5)-1", &exit_status) - 75);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("4^0.5-{10+20}+[100-2]/2", &exit_status) - 21);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5*0+(100^4)-36.6/9", &exit_status) - 99999995.933333333);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("0^10-(189+(49/(7-8)))*5", &exit_status) - (-700));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("(5^3+15/3)", &exit_status) - 130);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("5^{(1+6)*2}-3*[6/3]", &exit_status) - 6103515619);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("(1)^12", &exit_status) - 1);
    REQUIRE(0.00001 > Calculate("(3^2+2)+5-1", &exit_status) - 15);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("4^0.5-(10+20)^2+100/2", &exit_status) - (-848));
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("[5*0]+[100-36]*0.6/9", &exit_status) - 4.266666667);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("10-1-1-1-4", &exit_status) - 3);
    REQUIRE(exit_status == SUCCESS);
    REQUIRE(0.00001 > Calculate("-18*{[(9+49)/7]-{8*5}}", &exit_status) - 570.8571429);
    REQUIRE(exit_status == SUCCESS);
    return PASSED;
}