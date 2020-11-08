#include "kt.h"
#include <stdio.h>



/*--------------------------define & typedef-----------------------*/
#define FAIL (0)
#define TRUE (1)
#define FALSE (0)
#define SUCCESS (1)

typedef size_t(*move_func)(size_t pos);



/*-----------------------declerations-------------------------------*/

static size_t U2R1(size_t pos);
static size_t U2L1(size_t pos);
static size_t L2U1(size_t pos);
static size_t L2D1(size_t pos);
static size_t D2L1(size_t pos);
static size_t D2R1(size_t pos);
static size_t R2D1(size_t pos);
static size_t R2U1(size_t pos);
static void InitPossibleMoves(unsigned char possible_moves_lut[]);
static int IsLegitMove(size_t pos, size_t new_pos, int move);
static size_t ChooseMove(size_t pos, bit_array_t board);
static void ReInitPosMoves(size_t pos);


/*--------------------LUTS------------------------*/
unsigned char possible_moves_lut[64] = {0};
static move_func moves[8] = {   
                                U2L1,
                                U2R1,
                                R2U1,
                                R2D1,
                                D2R1,
                                D2L1,
                                L2D1,
                                L2U1 
                            };

/*-------------solve functions----------------------*/
int KTSolve(size_t pos, bit_array_t board, size_t *solution)
{
    size_t current_step = 0;
    int move = 0;
    int status = FAIL;
    InitPossibleMoves(possible_moves_lut);
    current_step = BitsArrCountOn(board);
    if(64 == current_step)
    {
        return SUCCESS;
    }
    if(1 == BitsArrGetVal(board, pos))
    {
        return FAIL;
    }

    *solution = pos;
    board = BitsArrSetBit(board, pos, 1);
    for(move = 0; move < 8 && status == FAIL; ++move)
    {
        if(1 == BitsArrGetVal(possible_moves_lut[pos],move))
        {
            status = KTSolve(moves[move](pos), board, solution + 1);
        }
    }
    if(FAIL == status)
    {
        board = BitsArrSetBit(board, pos, 0);
        *solution = 0;
    }
    return status;
}

int KTHeuristicSolve(size_t pos, bit_array_t board, size_t *solution)
{
    size_t current_step = 0;
    int move = 0;
    int status = FAIL;
    InitPossibleMoves(possible_moves_lut);
    current_step = BitsArrCountOn(board);
  
    if(64 == current_step  )
    {
        return SUCCESS;
    }
    if(1 == BitsArrGetVal(board, pos))
    {
        return FAIL;
    }

    *solution = pos;
    board = BitsArrSetBit(board, pos, 1);

    while(0 < BitsArrCountOn(possible_moves_lut[pos]) && FAIL == status)
    {
       move = ChooseMove(pos, board);
       status = KTHeuristicSolve(moves[move](pos), board, solution + 1);
    }
    if(FAIL == status)
    {
        board = BitsArrSetOff(board, pos);
        *solution = 0;
        ReInitPosMoves(pos);
    }
    
    return status;
}
/*-----------------------service functions------------------*/

static size_t ChooseMove(size_t pos, bit_array_t board)
{
    int move = 0;
    int onward_move = 0;
    int count = 0;
    int min_moves = 8;
    int min_idx = 0;
    int next = 0;
    int next_next = 0;
    for(move = 0; move < 8 ; move ++)
    {
        count = 0;
        if(1 == BitsArrGetVal(possible_moves_lut[pos], move))
        {
            next = moves[move](pos);
            for(onward_move = 0; onward_move < 8; ++onward_move)
            {
                
                if(1 == BitsArrGetVal(possible_moves_lut[next], onward_move))
                {
                    next_next = moves[onward_move](next); 
                    if(0 == BitsArrGetVal(board, next_next))
                    {
                        ++count;
                    }
                }
            }
            if(count < min_moves)
            {
                min_moves = count;
                min_idx = move;
            }
        }
    }
    possible_moves_lut[pos] = BitsArrSetOff(possible_moves_lut[pos], min_idx);
    return min_idx;
}

static void InitPossibleMoves(unsigned char possible_moves_lut[])
{   
    static int initialized = FALSE;
    int pos = 0;
    int move = 0;
    unsigned char possible_moves = 0;
    if(initialized == FALSE)
    {
        initialized = TRUE;
        for(pos = 0; pos < 64; ++pos)
        {
            possible_moves = 0;
            for(move = 0; move < 8; ++move)
            {
                if(IsLegitMove(pos ,moves[move](pos), move))
                {
                    possible_moves = BitsArrSetBit((bit_array_t)possible_moves, move, 1);
                }
            }
            possible_moves_lut[pos] = possible_moves;
        }
    }  
}

static void ReInitPosMoves(size_t pos)
{
    int move = 0;
    unsigned char possible_moves = 0;
    for(move = 0; move < 8; ++move)
    {
        if(IsLegitMove(pos ,moves[move](pos), move))
        {
            possible_moves = BitsArrSetOn((bit_array_t)possible_moves, move);
        }
    }
    possible_moves_lut[pos] = possible_moves;
}

static int IsLegitMove(size_t pos, size_t new_pos, int move)
{

    size_t pos_col = pos % 8;
    size_t n_pos_col = new_pos % 8;
    int ans = 0;
    if(64 > new_pos)
    {
        switch (move)
        {
            case 0:
            case 5:
                /* U2L1, D2L1 */
                ans = (pos_col - 1 == n_pos_col);
                break;
            case 7:
            case 6:
                /* L2U1, L2D1 */
                ans = (pos_col - 2 == n_pos_col);
                break;
            case 2:
            case 3:
                /* R2U1, R2D1 */
                ans = (pos_col + 2 == n_pos_col);
                break;
            default:
                /* U2L1, D2L1 */
                ans = (pos_col + 1 == n_pos_col);
                break;
        }
    }
    
    return ans;
}

/*----------------- moves functions-----------------------*/
size_t U2L1(size_t pos)
{
    return pos - 17;
}

size_t U2R1(size_t pos)
{
    return pos - 15; 
}

size_t L2U1(size_t pos)
{
    return pos - 10;
}

size_t L2D1(size_t pos)
{
    return pos + 6;
}

size_t D2L1(size_t pos)
{
    return pos + 15;
}

size_t D2R1(size_t pos)
{
    return pos + 17;
}

size_t R2D1(size_t pos)
{
    return pos + 10;
}

size_t R2U1(size_t pos)
{
    return pos - 6;
}


