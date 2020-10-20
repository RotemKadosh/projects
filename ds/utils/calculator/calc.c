#include <stdlib.h>                 /*malloc free*/
#include <math.h>                   /*pow*/
#include <string.h>                 /*strlen*/
#include <assert.h>                 /*assert*/
#include "stack.h"                  /*stack_t, create ,pop,peek*/
#include "calc.h"
#include "parser.h"                 /*GetNum, GetOp*/
#define ASCII_SIZE (128)
#define TRUE (1)
#define FALSE (0)

typedef enum state
{
    WAIT_FOR_NUM = 0, 
    WAIT_FOR_OP,    
    ERROR,
    RESAULT,
    NUMBER_OF_STATE
}state_ty; 

typedef enum associtive
{
    LEFT = 0, 
    RIGHT
    
}associative; 


typedef struct calc calculator_ty;

typedef double(*OperationFunc_ty)(double num1, double num2, int *exit_status);

typedef state_ty(*StageHendlerFunc_ty)(calculator_ty *calc, const char **math_exp, int *exit_status);

typedef void(*assoc_hendler_ty)(calculator_ty *calc, int *exit_status);

struct calc
{
    stack_t *numbers;
    stack_t *operations;
    StageHendlerFunc_ty states_lut[NUMBER_OF_STATE];
    OperationFunc_ty operations_lut[ASCII_SIZE];
    assoc_hendler_ty Assoc_lut[ASCII_SIZE];
};



/*-------------------------------------declerations-------------------------*/

             /*-----operation funcs---------*/
static double Add(double num1, double num2, int *exit_status);
static double Substract(double num1, double num2, int *exit_status);
static double Divide(double num1, double num2, int *exit_status);
static double Multiply(double num1, double num2, int *exit_status);
static double Power(double base, double power, int *exit_status);
             /*-----init funcs---------*/
static calculator_ty *InitCalc(const char *math_exp, int *exit_status);
static int InitStacks(calculator_ty *calc, size_t capacity);
static void InitStatesLut(calculator_ty *calc);
static void InitOpLut(calculator_ty *calc);
static void InitAssocLut(calculator_ty *calc);
             /*-----hedlers funcs---------*/
static state_ty WaitForNumHendler(calculator_ty *calc, const char **math_exp, int *exit_status);
static state_ty WaitForOpHendler(calculator_ty *calc, const char **math_exp, int *exit_status);
static state_ty ErrorHendler(calculator_ty *calc, const char **math_exp, int *exit_status);
static double ResaultHendler(calculator_ty *calc, int *exit_status);
void RightAssocHendler(calculator_ty *calc,  int *exit_status);
void LeftAssocHendler(calculator_ty *calc,  int *exit_status);
void ParanthesesHendler(calculator_ty *calc,char op, int *exit_status);
             /*-----service funcs---------*/
static void CalculateSoFar(calculator_ty *calc, char op, int *exit_status);
static void MoveElementFromStackToStack(stack_t *old, stack_t *new);
static double TakeNumFromStack(stack_t *stack);
static void PushDoubleToStack(const double num, stack_t *stack);
static int IsSmallerPriority(const char op1,const char op2);
static int GetPriority(const char op);
static void DestroyCalc(calculator_ty *calc);
static void MoveOpFromStackToStack(stack_t *old, stack_t *new);
static int GetAssoc(char op);
static char TakeOpFromStack(stack_t *stack);
static void PushOpToStack(const char op, stack_t *stack);
static char PeekOpFromStack(stack_t *stack);
static int IsCloseParantheses(char op);
static char GetMatchParantheses(char par);
/*--------------------------Definitions---------------------------*/

/*----------------operation func ---------------------*/

static double Add(double num1, double num2, int *exit_status)
{
    (void)exit_status;
    return num1 + num2;
}

static double Substract(double num1, double num2, int *exit_status)
{
    (void)exit_status;
    return num1 - num2;
}

static double Divide(double num1, double num2, int *exit_status)
{
    if(num2 == 0)
    {
        *exit_status = MATH_ERROR;
        return 0;
    }
    return num1 / num2;
}

static double Multiply(double num1, double num2, int *exit_status)
{
    (void)exit_status;
    return num1 * num2;
}

static double Power(double base, double power, int *exit_status)
{
    if(base <= 0 && (power - (int)power > 0) )
    {
        *exit_status = MATH_ERROR;
        return 0;
    }
    return pow(base, power);
}

/*-----------------Init funcs--------------------------*/

static calculator_ty *InitCalc(const char *math_exp, int *exit_status)
{
    size_t exp_len = strlen(math_exp);
    calculator_ty *calc = malloc(sizeof(calculator_ty));
    if(calc == NULL)
    {
        *exit_status = MALLOC_ERROR;
        return NULL;
    }
    if(SUCCESS != InitStacks(calc, exp_len))
    {
        free(calc);
        *exit_status = MALLOC_ERROR;
        calc = NULL;
        return NULL;
    }
    InitStatesLut(calc);
    InitOpLut(calc);
    InitAssocLut(calc);
    return calc;

}

static int InitStacks(calculator_ty *calc, size_t capacity)
{
    
    char dummy_op = '#';
    calc->numbers = StackCreate(capacity);
    if(calc->numbers == NULL)
    {
        return MALLOC_ERROR;
    }
    calc->operations = StackCreate(capacity);
    
    if(calc->operations == NULL)
    {
        StackDestroy(calc->numbers);
        return MALLOC_ERROR;
    }

    PushOpToStack(dummy_op, calc->operations);


    return SUCCESS;

}

static void InitStatesLut(calculator_ty *calc)
{
    assert(NULL != calc);
    calc->states_lut[WAIT_FOR_NUM] = WaitForNumHendler;
    calc->states_lut[WAIT_FOR_OP] = WaitForOpHendler;
    calc->states_lut[ERROR] = ErrorHendler;
}

static void InitOpLut(calculator_ty *calc)
{
    assert(NULL != calc);
    calc->operations_lut['+'] = Add;
    calc->operations_lut['-'] = Substract;
    calc->operations_lut['*'] = Multiply;
    calc->operations_lut['/'] = Divide;
    calc->operations_lut['^'] = Power;

}

static void InitAssocLut(calculator_ty *calc)
{
    assert(NULL != calc);

    calc->Assoc_lut['+'] = LeftAssocHendler;
    calc->Assoc_lut['-'] = LeftAssocHendler;
    calc->Assoc_lut['*'] = LeftAssocHendler;
    calc->Assoc_lut['/'] = LeftAssocHendler;
    calc->Assoc_lut['^'] = RightAssocHendler;
}

/*----------------------hendlers-----------------=----*/

state_ty WaitForNumHendler(calculator_ty *calc, const char **math_exp, int *exit_status)
{
    double num = 0;
    state_ty change_to_state= WAIT_FOR_OP;
    char parantheses = '0';
    const char *ptr_end = *math_exp;

    assert(calc != NULL);
    assert(math_exp != NULL);
    assert(exit_status != NULL);

    num = GetNum(*math_exp, &ptr_end, &parantheses);
    if(num == 0)
    {
        if(parantheses != '0')
        {
            PushOpToStack(parantheses, calc->operations);
            change_to_state = WAIT_FOR_NUM;
        }
        else if(*math_exp != ptr_end)
        {
            PushDoubleToStack(num, calc->numbers);
        }
        else 
        {
            *exit_status = SYNTAX_ERROR;
            change_to_state = ERROR;
        }
    }
    else 
    {
        PushDoubleToStack(num, calc->numbers);
    }
    *math_exp = ptr_end;
    return change_to_state;
}

state_ty WaitForOpHendler(calculator_ty *calc, const char **math_exp, int *exit_status)
{
    char op ='0';
    char peek ='0';
    const char *ptr_end = *math_exp;
    state_ty change_to_state= WAIT_FOR_NUM;
    assert(calc != NULL);
    assert(math_exp != NULL);
    assert(exit_status != NULL);
    op = GetOp(*math_exp, &ptr_end);
    
    peek = PeekOpFromStack(calc->operations);
    if('#' == op)
    {
        *exit_status = SYNTAX_ERROR;
        change_to_state = ERROR;
    }
    else if(IsSmallerPriority(op, peek))
    {
        CalculateSoFar(calc, op, exit_status);
    }
    else if(IsCloseParantheses(op))
    {
        ParanthesesHendler(calc, op, exit_status);
        change_to_state = WAIT_FOR_OP;
        *math_exp = ptr_end;
        return change_to_state;
    }
    if(op == '\0')
    {
        change_to_state = RESAULT;
        return change_to_state;
    }
    *math_exp = ptr_end;
    PushOpToStack(op, calc->operations);
    if(*exit_status != SUCCESS)
    {
        change_to_state = ERROR;
    }
    return change_to_state;
}

state_ty ErrorHendler(calculator_ty *calc, const char **math_exp, int *exit_status)
{
    assert(calc != NULL);
    assert(math_exp != NULL);
    assert(exit_status != NULL);
    DestroyCalc(calc);
    return RESAULT;
}

double ResaultHendler(calculator_ty *calc, int *exit_status)
{
    double result = 0;
    
    assert(NULL != calc);
    assert(NULL != exit_status);
    if (SUCCESS == *exit_status)
    {
        result  = TakeNumFromStack(calc->numbers);
        if(StackSize(calc->operations) != 1)
        {
            *exit_status = SYNTAX_ERROR;
        }
        DestroyCalc(calc);
    }
    return result;
}

void LeftAssocHendler(calculator_ty *calc,  int *exit_status)
{
    double num1 = 0;
    double num2 = 0;
    double ans = 0;
    char current_op = '0';
    stack_t *new_op = NULL;
    stack_t *new_num = StackCreate(StackSize(calc->numbers));
    if(NULL == new_num)
    {
        *exit_status = MALLOC_ERROR;
        return;
    }
    new_op = StackCreate(StackSize(calc->operations));
    if(NULL == new_op)
    {
        StackDestroy(new_num);
        *exit_status = MALLOC_ERROR;
        return;
    } 

    current_op =PeekOpFromStack(calc->operations);
    MoveOpFromStackToStack(calc->operations, new_op);
    MoveElementFromStackToStack(calc->numbers, new_num);
    MoveElementFromStackToStack(calc->numbers, new_num);

    while(GetPriority(current_op) == GetPriority(PeekOpFromStack(calc->operations)))
    {
        /*move all element and op to new stacks*/
        MoveOpFromStackToStack(calc->operations, new_op);
        MoveElementFromStackToStack(calc->numbers, new_num);
    }
    while(StackSize(new_num) > 1 && SUCCESS == *exit_status)
    {
        /*calc from new stacks*/
        current_op = TakeOpFromStack(new_op);
        num1 = TakeNumFromStack(new_num);
        num2 = TakeNumFromStack(new_num);
        ans = calc->operations_lut[(int)current_op](num1, num2, exit_status);
        PushDoubleToStack(ans, new_num);
    }
    MoveElementFromStackToStack(new_num, calc->numbers);
    StackDestroy(new_op);
    StackDestroy(new_num);

}

void RightAssocHendler(calculator_ty *calc,  int *exit_status)
{
    double num1 = 0;
    double num2 = 0;
    double ans = 0;
    char op = PeekOpFromStack(calc->operations);
    while(GetAssoc(op) == RIGHT && SUCCESS == *exit_status && StackSize(calc->numbers) > 1)
    {
        StackPop(calc->operations);
        num1 = TakeNumFromStack(calc->numbers); 
        num2 = TakeNumFromStack(calc->numbers);
        ans = calc->operations_lut[(int)op](num2, num1, exit_status);
        PushDoubleToStack(ans, calc->numbers);
        op = PeekOpFromStack(calc->operations);
    }
}

void ParanthesesHendler(calculator_ty *calc, char op, int *exit_status)
{
    char match_par = GetMatchParantheses(op);
    char current_op = PeekOpFromStack(calc->operations);
    if(current_op != match_par)
    {
        CalculateSoFar(calc, match_par, exit_status);
    }
    current_op = TakeOpFromStack(calc->operations);
    if(current_op != match_par)
    {
        *exit_status = SYNTAX_ERROR;
    }

}


/*-------------------service funcs---------------------*/

static void MoveOpFromStackToStack(stack_t *old, stack_t *new)
{
    char op = TakeOpFromStack(old);
    PushOpToStack(op, new);
}

static void CalculateSoFar(calculator_ty *calc, char op, int *exit_status)
{
    char current_op = PeekOpFromStack(calc->operations);
    while(IsSmallerPriority(op, current_op) && 1 < StackSize(calc->numbers) && SUCCESS == *exit_status)
    {
       calc->Assoc_lut[(int)current_op](calc,exit_status);
       current_op = PeekOpFromStack(calc->operations);
    }
}

static int GetAssoc(char op)
{
    int assoc = LEFT;
    if (op == '^')
    {
        assoc = RIGHT;
    }
    return assoc;
}

static void MoveElementFromStackToStack(stack_t *old, stack_t *new)
{
    double num = TakeNumFromStack(old);
    PushDoubleToStack(num, new);
        
}

static double TakeNumFromStack(stack_t *stack)
{
    double *num_ptr = NULL;
    double num = 0;
    num_ptr = StackPeek(stack);
    num = *(double *)&num_ptr;
    StackPop(stack);
    return num;
}

static void PushDoubleToStack(const double num, stack_t *stack)
{
    void *num_as_pvoid = NULL;
    *(double *)&num_as_pvoid = num; 
    StackPush(stack, num_as_pvoid);
}

static char TakeOpFromStack(stack_t *stack)
{
    char *op_ptr = NULL;
    char op = 0;
    op_ptr = StackPeek(stack);
    op = *(char *)&op_ptr;
    StackPop(stack);
    return op;
}

static char PeekOpFromStack(stack_t *stack)
{
    char *op_ptr = NULL;
    char op = 0;
    op_ptr = StackPeek(stack);
    op = *(char *)&op_ptr;
    return op;
}

static void PushOpToStack(const char op, stack_t *stack)
{
    void *op_as_pvoid = NULL;
    *(char *)&op_as_pvoid = op; 
    StackPush(stack, op_as_pvoid);
}

static int IsSmallerPriority(const char op1,const char op2)
{
    return (GetPriority(op1) < GetPriority(op2));
}

static int GetPriority(const char op)
{
    int priority = 0;
    switch (op)
    {
    case '\0':
    case '(':
    case '{':
    case '[':
        priority = 0;
        break;
    case '+':
    case '-':
        priority = 1;
        break;
    case '*':
    case '/':
        priority = 2; 
        break; 
    case '^':
        priority = 3;
        break;
    default:
        priority = 4;
        break;   
    }
    return priority;
}

static void DestroyCalc(calculator_ty *calc)
{
    StackDestroy(calc->numbers);
    StackDestroy(calc->operations);
    free(calc);
    calc = NULL;
}

static int IsCloseParantheses(char ch)
{
    int res = FALSE;
    if(ch == ')' || ch ==']' || ch == '}')
    {
        res = TRUE;
    }
    return res;
}

static char GetMatchParantheses(char par)
{
    char res = ' ';
    switch (par)
    {
    case ')':
        res = '(';
        break;
    case ']':
        res = '[';
        break;
    default:
        res = '{';
        break;
    }
    return res;
}
/*-----------------main func------------------------*/

double Calculate(const char *math_exp, int *exit_status)
{
    state_ty state = WAIT_FOR_NUM;
    calculator_ty *calc = InitCalc(math_exp, exit_status);
    if(NULL == calc)
    {
        state = RESAULT;
    }
    while(state != RESAULT)
    {
        state = calc->states_lut[state](calc, &math_exp, exit_status);
    }
    return ResaultHendler(calc, exit_status);
}
