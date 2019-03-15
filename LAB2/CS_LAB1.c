#include <stdio.h>
#include <time.h>
int main()
{
	int x, y, a;
	double b;
	clock_t start, end;
	printf("请输入整数运算次数（亿次）\n");
	scanf("%d",&x);      
	printf("请输入浮点运算次数（亿次）\n");
	scanf("%d",&y);       
	start = clock();
	for (int i = 0; i<x*100000000; i++)               
	{
		a = 123456 * 123456;
		a = a/1000000;
	}
	end = clock();
	printf("整数运行时间为%f\n", (double)(end - start) / CLK_TCK);
	start = clock();
	for (int i = 0; i<y*100000000; i++)             
	{
		b = 123.458 * 123.456;
	}
	end = clock();
	printf("浮点数运行时间%f\n", (double)(end - start) / CLK_TCK);
	scanf("%d",&y);
	return 0;
}