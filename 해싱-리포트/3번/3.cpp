#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZR 30

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void insertion_sort(int list[], int s, int e)
{
	int i, j;
	int item;

	for (i = s+1; i <= e;i++) 
	{
		item = list[i];
		for (j = i - 1;j >= s &&list[j]>item; j--)
			list[j + 1] = list[j];
		list[j + 1] = item;
	}
}

void sort_Hash(int A[], int s, int e)
{
	// find min, max
	int	i;
	double	a, b, min, max;
	int y;

	min = max = A[s];
	for (i = s + 1; i <= e; i++) 
	{
		if (A[i] < min)	
			min = A[i];
		if (A[i] > max)
			max = A[i];
	}

	a = ((double)(e - s)) / (max - min);		//y = ax + b 에서 a부분
	b = -min * a;	// b 부분

	//각 해싱값  대한 데이터의 수
	int	*B = new int[e - s + 1];

	//각 해싱값에 대한 배열의 시작 인덱스
	int	*start = new int[e - s + 1];

	//각 해싱값에 대한 충돌 횟수
	int *count = new int[e - s + 1];

	//y값을 배열로 만듬
	int *Y = new int[e - s + 1];

	//각 배열 초기화
	for (int i = s;i <= e;i++)
	{
		B[i] = 0;
		start[i] = 0;
		count[i] = 0;
	}

	int k = -1;
	//카운트 배열 만듬
	for (int i = s; i <= e; i++)
	{
		y = (int)(a * A[i] + b);	//y = ax + b
		Y[++k] = y;
		count[y]++;
	}

	int v = 0;
	k = -1;
	//카운트 배열에 대한 스타트 배열 만듬
	for (int i = s; i <= e; i++)
	{
		start[++k] = v;
		v += count[i];
	}

	/*
	for (int i = s; i <= e; i++)
	{
		printf("%d  ", count[i]);
	}
	printf("\n");

	for (int i = s; i <= e; i++)
	{
		printf("%d  ", start[i]);
	}
	printf("\n");

	for (int i = s; i <= e; i++)
	{
		printf("%d  ", Y[i]);
	}
	printf("\n");
	*/

	//정렬 안된 배열 B[] 생성
	k = -1;
	while(k != e)
	{
		i = Y[++k];
		for (int j = start[i]; j < start[i] + count[i]; j++)	//start부터 start+count까지만 돌면 됨
		{
			if (B[j] == 0)	//그때그때 값이 0일경우만 넣고 브레이크 시켜주므로  낭비 없음!
			{
				B[j] = A[k];
				break;
			}
		}
	}

	
	//해싱으로 나눠진 배열 B를 부분을 나눠 정렬함
	//순환으로 돌아서 함수 여러번 계속 들어가는 것보다 이게 더 좋은 방법이라 판단하여 한번 짜봤습니다.
	int oldS = -1;
	int oldE = -1;
	for (int i = s; i <= e; i++)
	{
		if (oldS == start[i])	//만약 올드S 인덱스가 start[i]랑 같다면 배열을 정렬할 필요 없으므로 continue
			continue;
		if (i != s && (count[i] == 1 || count[i] == 0))	//맨 처음을 제외하고 count[i] == 1 이나 0 일경우도 배열을 정렬할 필요 없으므로 continue
			continue;

		oldS = start[i];
		oldE = start[i] + count[i];

		insertion_sort(B, oldS, oldE - 1);
	}
	

	for (int i = s; i <= e; i++)
		A[i] = B[i];
}

void main()
{
	int A[MAX_SIZR];
	int i;
	srand((int)time(NULL));
	for (i = 0;i<MAX_SIZR;i++)
		A[i] = rand() % 100 + 1;

	printf("----------------   배열 A 출력  ----------------\n");
	for (i = 0;i < MAX_SIZR;i++)
		printf("%d  ", A[i]);
	printf("\n");

	
	printf("----------------   hash sort 후  ----------------\n");
	sort_Hash(A, 0, MAX_SIZR-1);
	for (i = 0;i < MAX_SIZR;i++)
		printf("%d  ", A[i]);
	printf("\n");
}

//A를 찍어보고 sort_Hash를 호출하여 정렬이 되었는지 확인하시오.
//3. sort_hash과제. txt를 완성하시오