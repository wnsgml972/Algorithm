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

	a = ((double)(e - s)) / (max - min);		//y = ax + b ���� a�κ�
	b = -min * a;	// b �κ�

	//�� �ؽ̰�  ���� �������� ��
	int	*B = new int[e - s + 1];

	//�� �ؽ̰��� ���� �迭�� ���� �ε���
	int	*start = new int[e - s + 1];

	//�� �ؽ̰��� ���� �浹 Ƚ��
	int *count = new int[e - s + 1];

	//y���� �迭�� ����
	int *Y = new int[e - s + 1];

	//�� �迭 �ʱ�ȭ
	for (int i = s;i <= e;i++)
	{
		B[i] = 0;
		start[i] = 0;
		count[i] = 0;
	}

	int k = -1;
	//ī��Ʈ �迭 ����
	for (int i = s; i <= e; i++)
	{
		y = (int)(a * A[i] + b);	//y = ax + b
		Y[++k] = y;
		count[y]++;
	}

	int v = 0;
	k = -1;
	//ī��Ʈ �迭�� ���� ��ŸƮ �迭 ����
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

	//���� �ȵ� �迭 B[] ����
	k = -1;
	while(k != e)
	{
		i = Y[++k];
		for (int j = start[i]; j < start[i] + count[i]; j++)	//start���� start+count������ ���� ��
		{
			if (B[j] == 0)	//�׶��׶� ���� 0�ϰ�츸 �ְ� �극��ũ �����ֹǷ�  ���� ����!
			{
				B[j] = A[k];
				break;
			}
		}
	}

	
	//�ؽ����� ������ �迭 B�� �κ��� ���� ������
	//��ȯ���� ���Ƽ� �Լ� ������ ��� ���� �ͺ��� �̰� �� ���� ����̶� �Ǵ��Ͽ� �ѹ� ¥�ý��ϴ�.
	int oldS = -1;
	int oldE = -1;
	for (int i = s; i <= e; i++)
	{
		if (oldS == start[i])	//���� �õ�S �ε����� start[i]�� ���ٸ� �迭�� ������ �ʿ� �����Ƿ� continue
			continue;
		if (i != s && (count[i] == 1 || count[i] == 0))	//�� ó���� �����ϰ� count[i] == 1 �̳� 0 �ϰ�쵵 �迭�� ������ �ʿ� �����Ƿ� continue
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

	printf("----------------   �迭 A ���  ----------------\n");
	for (i = 0;i < MAX_SIZR;i++)
		printf("%d  ", A[i]);
	printf("\n");

	
	printf("----------------   hash sort ��  ----------------\n");
	sort_Hash(A, 0, MAX_SIZR-1);
	for (i = 0;i < MAX_SIZR;i++)
		printf("%d  ", A[i]);
	printf("\n");
}

//A�� ���� sort_Hash�� ȣ���Ͽ� ������ �Ǿ����� Ȯ���Ͻÿ�.
//3. sort_hash����. txt�� �ϼ��Ͻÿ�