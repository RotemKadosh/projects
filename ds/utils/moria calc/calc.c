#include <math.h> /*pow*/
#include <string.h>/*strlen*/
#include <assert.h>/*assert*/
#include <stdlib.h>/*malloc,free*/

#include "../parser/parser.h"
#include "../../../stack/stack.h"

typedef enum  
{
    SUCCESS = 0,
    MATH_ERROR,
    SYNTAX_ERROR,
    MALLOC_ERROR,
    NUM_OF_STATUS
}calc_status;

enum calc_states
{
    WFN = 0,
    WFO,
    OPENP,
    CLOSEP,
    HERROR,
    NUM_OF_STATES
};

enum calc_operators
{
    PLUS = 0,
    MINUS,
    MULTIPLY,
    DIVIDE,
    POW,
    PAR,
    NUM_OF_OP
};

typedef struct calculature
{
    const char *expression;
    stack_t *nums_stack;
    stack_t *op_stack;
}Calc_t;

typedef double (*Opreation_func)(const double num1, const double num2);
typedef calc_status (*Handler_func)(Calc_t *calc, char **position);

typedef struct state
{
    Handler_func func;
    int next_state;
}State_t;


static const int opLUTOriority[NUM_OF_OP][NUM_OF_OP] = {{1, 1, 0, 0, 0},
                                                        {1, 1, 0, 0, 0},
                                                        {1, 1, 1, 1, 0},
                                                        {1, 1, 1, 1, 0},
                                                        {1, 1, 1, 1, 1},
                                                        {0, 0, 0, 0, 0}};


/*----------------------------SERVICE FUNCTIONS DECLERATIONS------------------------*/

static calc_status CalcInit(Calc_t **calc, const char *exp, State_t lut[NUM_OF_STATES][NUM_OF_STATUS]);
static void LUTInit(State_t lut[NUM_OF_STATES][NUM_OF_STATUS]);
static void CalcDestroy(Calc_t *calc);

static calc_status DoCalculation(Calc_t *calc, char op);
static int GetOpNumber(char op);
static int IsPriority(char top_op, char cur_op);
static int IsOperation(char op);
static int IsOpenP(char ch);
static int IsCloseP(char ch);
static int GetPar(char p);
static int IsParenthesis(char op);
static void *ReversePar(char *open_phr);

static char GetDummy();
static int CheckDivideByZero(Calc_t *calc);

static calc_status HandlerWFN(Calc_t *calc, char **position);
static calc_status HandlerWFO(Calc_t *calc, char **position);
static calc_status HandlerOpenP(Calc_t *calc, char **position);
static calc_status HandlerCloseP(Calc_t *calc, char **position);
static calc_status HandlerFinalState(Calc_t *calc, char **position);
static calc_status HandlerError(Calc_t *calc, char **position);

static double Plus(const double num1, double num2);
static double Minus(const double num1, const double num2);
static double Multiply(const double num1, const double num2);
static double Divide(const double num1, const double num2);
static double Pow(const double num1, const double num2);

static Opreation_func op_func[NUM_OF_OP] = {Plus, Minus, Multiply, Divide, Pow};

/*----------------------------------------------------------*/

double Calculate(const char *math_exp, int *exit_status)
{
    int current_stat = 0;
    void *res = NULL;
    void *op = NULL;
    char *position = (char *)math_exp;

    static State_t handlerLUT[NUM_OF_STATES][NUM_OF_STATUS] = {NULL};
    Calc_t *calc = NULL;

    assert(NULL != math_exp);

    *exit_status = CalcInit(&calc, math_exp, handlerLUT);
 
    while (SUCCESS == *exit_status && '\0' != *position)
    {
        if (IsParenthesis(*position))
        {
            current_stat = GetPar(*position);
        }
        
        *exit_status = handlerLUT[current_stat][*exit_status].func(calc, &position);
        current_stat = handlerLUT[current_stat][*exit_status].next_state;
    }

    op = StackPeek(calc->op_stack);
    if (GetDummy() != *(char *)&op)
    {
        *exit_status = DoCalculation(calc, *(char *)&op);
    }
    
    res = StackPeek(calc->nums_stack);
    CalcDestroy(calc);

    if (SUCCESS != *exit_status)
    {
        return *exit_status;
    }

    return *(double *)&res;
}

/*-----------------SERVICE FUNCTIONS DEFINTIONS-----------------*/

static calc_status CalcInit(Calc_t **calc, const char *exp, State_t lut[NUM_OF_STATES][NUM_OF_STATUS])
{
    assert(NULL != exp);

    *calc = (Calc_t *)malloc(sizeof(Calc_t));
    if (NULL == *calc)
    {
        return MALLOC_ERROR;
    }

    (*calc)->nums_stack = StackCreate(strlen(exp));
    if (NULL == (*calc)->nums_stack)
    {
        free(*calc);
        return MALLOC_ERROR;
    }

    (*calc)->op_stack = StackCreate(strlen(exp));
    if (NULL == (*calc)->op_stack)
    {
        free(*calc);
        StackDestroy((*calc)->nums_stack);
        return MALLOC_ERROR;
    }

    (*calc)->expression = exp;
    StackPush((*calc)->op_stack, (void *)64);

    LUTInit(lut);

    return SUCCESS;
}

static void LUTInit(State_t lut[NUM_OF_STATES][NUM_OF_STATUS])
{
    int i = 0;
    int j = 0;
    
    assert(NULL != lut);

    for (i = 0; i < NUM_OF_STATES; ++i)
    {
        for (j = 0; j < NUM_OF_STATUS; ++j)
        {
            lut[i][j].func = HandlerError;
        }
    }
 
    lut[0][0].func = HandlerWFN;
    lut[0][0].next_state = WFO;

    lut[1][0].func = HandlerWFO;
    lut[1][0].next_state = WFN;

    lut[2][0].func = HandlerOpenP;
    lut[2][0].next_state = WFN;
    
    lut[3][0].func = HandlerCloseP;
    lut[3][0].next_state = WFO;
}

static void CalcDestroy(Calc_t *calc)
{
	assert(NULL != calc);

	StackDestroy(calc->nums_stack);
    StackDestroy(calc->op_stack);
    free(calc);
}

/*---------------------------HANDELERS FUNCTIONS--------------------------*/

static calc_status HandlerWFN(Calc_t *calc, char **position)
{
    void *num = 0;
    char *current_pos = *position;
    int status = SUCCESS;

    assert(NULL != calc);
    assert(NULL != *position);

    if ('\0' == *(*position))
    {
        return HandlerFinalState(calc, position);
    }

    *(double *)&num = ParserGetNum(position);
    if (*position == current_pos && SUCCESS != status)
    {
        return SYNTAX_ERROR;
    }
    StackPush(calc->nums_stack, num);

    return SUCCESS;
}

static calc_status HandlerWFO(Calc_t *calc, char **position)
{
    void  *op = '\0';
    void *current_op = {0};
    int status = 0;

    assert(NULL != calc);
    assert(NULL != *position);

    *(char *)&op = ParserGetOp(position);
    current_op = StackPeek(calc->op_stack);

    if (!IsOperation(*(char *)&op) || SUCCESS != status)
    {
        return SYNTAX_ERROR;
    }

    if ('\0' != *(char *)&op && GetDummy() != *(char *)&current_op && IsPriority(*(char *)&current_op, *(char *)&op))
    {
        DoCalculation(calc, *(char *)&current_op);
    }

    StackPush(calc->op_stack, op);

    return SUCCESS;
}

static calc_status HandlerOpenP(Calc_t *calc, char **position)
{
    void *close_phr = NULL;

    assert(NULL != calc);
    assert(NULL != position);

    while (IsOpenP(*(*position)) )
    {
        close_phr = ReversePar(*position);
        StackPush(calc->op_stack, close_phr);
        ++(*position);
    }

    return SUCCESS;
}

static calc_status HandlerCloseP(Calc_t *calc, char **position)
{
    void *curr_top = NULL;

    assert(NULL != calc);
    assert(NULL != position);

    curr_top = StackPeek(calc->op_stack);

    while (!IsCloseP(*(char *)&curr_top) && GetDummy() != *(char *)&curr_top)
    {
        DoCalculation(calc, *(char *)&curr_top);
        curr_top = StackPeek(calc->op_stack);
    }

    if (!IsCloseP(*(char *)&curr_top))
    {
        return SYNTAX_ERROR;
    }

    while (IsCloseP(*(char *)&curr_top) && IsCloseP(*(*position)))
    {
        if ((*(*position) != *(char *)&curr_top) && !IsOperation(*(*position)))
        {
                return SYNTAX_ERROR;
        }
        StackPop(calc->op_stack);
        ++(*position);     
    }

    return SUCCESS;
}

static calc_status HandlerError(Calc_t *calc, char **position)
{
    assert(NULL != calc);
    assert(NULL != position);

    if (!IsOperation(*(*position)))
    {
        return SYNTAX_ERROR;
    }

    if (CheckDivideByZero(calc))
    {
        return MATH_ERROR;
    }

    return SUCCESS;
}

static calc_status HandlerFinalState(Calc_t *calc, char **position)
{
    void *top_op = NULL;

    assert(NULL != calc);
    assert(NULL != position);

    top_op = StackPeek(calc->op_stack);

    if ('\0' == *(*position) && GetDummy() == *(char*)top_op)
    {
        return SUCCESS;
    }
    return SYNTAX_ERROR;

}

/*--------------------------------------------------------------------------------*/

static calc_status DoCalculation(Calc_t *calc, char op)
{
    void  *res = 0;
    double num1 = 0;
    double num2 = 0;
    void *curr_op = 0;

    assert(NULL != calc);

    curr_op = StackPeek(calc->op_stack);
    res = StackPeek(calc->nums_stack);

    while (GetDummy() != *(char *)&curr_op && !IsCloseP(*(char *)&curr_op))
    {
        if (CheckDivideByZero(calc))
        {
            return MATH_ERROR;
        }

        num1 = *(double *)&res;
        StackPop(calc->nums_stack);
        res = StackPeek(calc->nums_stack);
        num2 = *(double *)&res;

        StackPop(calc->nums_stack);
        StackPop(calc->op_stack);

        *(double *)&res = op_func[GetOpNumber(op)](num2, num1);
        StackPush(calc->nums_stack, res);
        curr_op = StackPeek(calc->op_stack);
        op = *(char *)&curr_op;
    }

    return SUCCESS;
}

static int IsOperation(char op)
{
    return (op == '+' || op == '-' || op == '*' || op == '/' || op == '^' || IsCloseP(op));
}

static int IsParenthesis(char op)
{
    return (IsOpenP(op) || IsCloseP(op));
}

static int IsPriority(char top_op, char cur_op)
{
    int first_op = GetOpNumber(top_op);
    int sec_op = GetOpNumber(cur_op);

    return opLUTOriority[first_op][sec_op];
}

static int GetOpNumber(char op)
{
    switch (op)
    {
    case '+':
        return PLUS;
        break;
    case '-':
        return MINUS;
        break;
    case '*':
        return MULTIPLY;
        break;
    case '/':
        return DIVIDE;
        break;
    case '^':
        return POW;
        break;
    default:
        return PAR;
        break;
    }
}

static void *ReversePar(char *open_phr)
{
    char close_phr = '\0';

    assert(NULL != open_phr);

    switch (*open_phr)
    {
    case '(':
        close_phr = ')';
        break;

    case '{':
        close_phr = '}';
        break;

    case '[':
        close_phr = ']';
        break;

    default:
        break;
    }

    return (void*)close_phr;
}

static int IsOpenP(char ch)
{
    return (ch == '[' || ch == '(' || ch == '{');
}

static int IsCloseP(char ch)
{
    return (ch == ']' || ch == ')' || ch == '}');
}

static char GetDummy()
{
    return '@';
}

static int GetPar(char p)
{
    if (IsOpenP(p))
    {
        return OPENP;
    }
    
    return CLOSEP;
}

static int CheckDivideByZero(Calc_t *calc)
{
    void *cur_op = 0;
    void *top_num = 0;

    assert(NULL != calc);

    cur_op = StackPeek(calc->op_stack);
    top_num = StackPeek(calc->nums_stack);

    return ('/' == *(char *)&cur_op && 0 == *(double *)&top_num);
}


/*-------------------------------CALC OP----------------------------*/

static double Plus(double num1, double num2)
{
    return (num1 + num2);
}

static double Minus(double num1, double num2)
{
    return (num1 - num2);
}

static double Multiply(double num1, double num2)
{
    return (num1 * num2);
}

static double Divide(double num1, double num2)
{
    return (num1 / num2);
}

static double Pow(double num1, double num2)
{
    return pow(num1, num2);
}

