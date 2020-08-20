#include <stdio.h> /*printf*/

int StockProfit(int *prices, int size, int *buy, int *sell)
{
	int profit = 0, i = 0, temp_profit = 0, min_buy= 0 , max_sell = 0;
	*sell = 0;
	*buy = 0;
	for (i = 1; i < size; ++i)
	{
		
		if(prices[i] < prices[min_buy] &&  )
		{
			min_buy = i;
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
int main()
{
	int arr1 [] = {9 , 100, 0, 1, 2};
	int arr2 [] = {0 , 1, 0, 5, 0, 9};
	int arr3 [] = {9 , 0, 0, 1, 2};
	int sell = 0, buy = 0;
	int test1 = 0, test2 = 0, test3 = 0 ;
	int *sell_ptr = &sell;
	int *buy_ptr = &buy;

	test1 = ((91 == StockProfit(arr1, 5, buy_ptr, sell_ptr)) && 1 == *sell_ptr && 0 == *buy_ptr);
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
}


