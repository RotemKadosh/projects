#include <stdio.h> /*printf*/

int StockProfit(int *prices, int size, int *buy, int *sell)
{
	int i = 0, min_buy= 0 , max_sell = 0;
	*sell = 0;
	*buy = 0;
	for (i = 1; i < size; ++i)
	{
		
		if(prices[i] < prices[min_buy]  )
		{
			min_buy = i;
			max_sell = i;
		} 
		if (prices[i] > prices[max_sell])
		{
			max_sell = i;
		}
		
	}

	*sell = max_sell;
	*buy = min_buy;
	return prices[max_sell] - prices [min_buy];
}
/*------------------------------GeeksforGeeks Solution-----------------------------*/
typedef struct interval { 
    int buy; 
    int sell; 
} interval_t;

void stockBuySell(int price[], int size) 
{ 
	static int c = 1;
	int count = 0;
	int i = 0; 
    interval_t sol[15];
    while (i < size - 1) 
    { 
        while ((i < size - 1) && (price[i + 1] <= price[i])) 
        {
            i++; 
        }
        if (i == size - 1) 
        {
            break; 
        }
        sol[count].buy = i++; 
        while ((i < size) && (price[i] >= price[i - 1])) 
        {
            i++; 
        }
        sol[count].sell = i - 1; 
        count++; 
    } 
    printf("for arr%d\n ", c);
            ++c; 
    if (count == 0) 
    {
        printf("There is no day when buying the stock will make profitn\n"); 
    }
    else { 
        for (i = 0; i < count; i++) 
		{
            printf("Buy on day: %d\t Sell on day: %d\n", sol[i].buy, sol[i].sell);
        }
    } 
  
    return; 
} 

/*------------------------------------------------------------*/
int main()
{
	int arr1 [] = {9 , 100, 0, 1, 2};
	int arr2 [] = {0 , 1, 0, 5, 0, 9};
	int arr3 [] = {9 , 0, 0, 1, 2};
	int sell = 0, buy = 0;
	int test1 = 0, test2 = 0, test3 = 0 ;
	int *sell_ptr = &sell;
	int *buy_ptr = &buy;

	
	test1 = ((9 == StockProfit(arr1, 5, buy_ptr, sell_ptr)) && 1 == *sell_ptr && 0 == *buy_ptr);
	test2 = ((9 == StockProfit(arr2, 6, buy_ptr, sell_ptr)) && 5 == *sell_ptr && 0 == *buy_ptr);
	test3 = ((2 == StockProfit(arr3, 5, buy_ptr, sell_ptr)) && 5 == *sell_ptr && 2 == *buy_ptr);

	if (test1 && test2 && test3)
	{
		printf("StockProfit passed\n");
	}
	else
	{
		printf("StockProfit failed. test1: %d, test2: %d, test3: %d \n", test1, test2, test3);
	}

	stockBuySell(arr1, 5);
	stockBuySell(arr2, 6);
	stockBuySell(arr3, 5);
	return 0;

}


