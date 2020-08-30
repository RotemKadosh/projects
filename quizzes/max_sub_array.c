#include <stdio.h>/*printf*/


int MaxSubArray(int arr[], int size, int *start, int *end)
{
	static int i = 1;
	int max_sum = 0, cur_sum = 0, tmp_start = 0, tmp_end = 0;
	for (tmp_end = 0; tmp_end < size; tmp_end++)
	{
		cur_sum += arr[tmp_end];

		if (cur_sum >= max_sum)
		{
			max_sum = cur_sum;
			*end = tmp_end;
			*start = tmp_start;
		}
		if (cur_sum < 0)
		{
			cur_sum = 0;
			tmp_start = tmp_end + 1;
		}
	}
	printf("arr%d start = %d, end = %d, sum = %d\n", i++, *start, *end, max_sum);
	return max_sum;
}



void TestMaxSubArray()
{
	int arr1[] = {-1, -1, -1, 0, -3, -6};
	int arr2[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	int arr3[] = {-2, -1, 100, -6};
	int start = 0, end = 0;
	int sum1 = 0, sum2 = 0, sum3 = 0;
	int test1 = 0, test2 = 0, test3 = 0;
	
	sum1 = MaxSubArray(arr1 , sizeof(arr1)/sizeof(arr1[0]), &start, &end);
	if (0 == start && 4 == end && 6 == sum1)
	{
		test1 = 1;
		start = 0;
		end = 0;
	}
	sum2 = MaxSubArray(arr2 , sizeof(arr2)/sizeof(arr2[0]), &start, &end);
	if (3 == start && 6 == end && 8 == sum2)
	{
		test2 = 1;
		start = 0;
		end = 0;
	}

	sum3 = MaxSubArray(arr3 , sizeof(arr3)/sizeof(arr3[0]), &start, &end);
	if (2 == start && 2 == end && 100 == sum3)
	{
		test3 = 1;
		start = 0;
		end = 0;
	}

	if (test1 && test2 && test3)
	{
		printf("MaxSubArray pass\n");
	}
	else
	{
		printf("MaxSubArray faild, test1: %d, test2: %d, test3: %d\n", test1, test2, test3);
	}
}	
int main()
{
	TestMaxSubArray();
	return 0;
}