#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

int list[10];
int k;

//퀵정렬
int partition(int list[], int left, int right, int k)
{
	int i;
	int j = -1;	//피벗 인덱스
	int temp;

	//각 high, low, pivot을 원하는 갯수만큼 생성
	int *pivot = (int *)malloc(sizeof(int)*(k));
	int *low = (int *)malloc(sizeof(int)*(k));
	int *high = (int *)malloc(sizeof(int)*(k));

	printf("\nleft : %d  right : %d \n", left, right);

	if (right - left < k)	//k가 더크면 루프를 그만큼 적게 돌게 만듬
		k = right - left;

	//do while문 생각하면서 짜기
	//각각 대입
	for (i = 0;i < k;i++)
	{
		low[i] = left+i;
		high[i] = right + 1;
		pivot[++j] = list[left+i];
	}


	for (int i = 0; i < k;i++)
	{
		printf("%d %d %d \n", pivot[i], low[i], high[i]);
	}


	for (i = 0;i < k;i++)
	{
		do
		{
			do
			{
				low[i]++;
			} while (low[i] <= high[i] && list[low[i]] < pivot[i]);
			do
			{
				high[i]--;
			} while (high[i] <= right && list[high[i]] > pivot[i]);

			if (low[i] < high[i])
				SWAP(list[low[i]], list[high[i]], temp);
		} while (low[i] < high[i]);

		SWAP(list[left+i], list[high[i]], temp);	//각각 1칸씩 옆에껄로 바꿈	
	}

	return high[0];	//첫번째 요소 리턴
}
void quick_sort(int list[], int left, int right, int k)
{
	if (left < right)
	{
		int q = partition(list, left, right, k);
		quick_sort(list, left, q - 1, k);
		quick_sort(list, q + 1, right, k);
	}
}


void main()
{
	int i, n;
	n = 10;

	/*
	srand((int)time(NULL));

	for (i = 0; i < n; i++)
		list[i] = rand() % 10;

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	printf("몇개의 피벗을 사용하시겠습니까? >>");
	scanf("%d", &k);
	*/
	int list[10] = { 2,4,2,4,47,4,5,12,23,10 };
	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	quick_sort(list, 0, n - 1, 5);

	for (i = 0; i < n; i++)
		printf("%d  ", list[i]);
	printf("\n");
}