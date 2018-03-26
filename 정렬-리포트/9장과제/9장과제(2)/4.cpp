#define _CRT_SECURE_NO_WARNINGS
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t) )

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int list[10];
int sorted[10];

//�պ�����
void merge(int list[], int left, int mid, int right)
{
	int i, j, k, l;

	i = left;
	j = mid + 1;
	k = left;

	while (i <= mid && j <= right)
	{
		if (list[i] <= list[j])
			sorted[k++] = list[i++];
		else
			sorted[k++] = list[j++];
	}

	if (i > mid)
		for (l = j;l <= right;l++)
			sorted[k++] = list[l];
	else
		for (l = i;l <= mid; l++)
			sorted[k++] = list[l];

	for (l = left;l <= right;l++)
		list[l] = sorted[l];
}

void kmerge_sort(int list[], int left, int right, int k)
{
	int gap, cnt, i;
	int mid1, mid2;

	if (left < right)
	{
		cnt = 0;
		for (i = left; i <= right; i++)
			cnt++;
		gap = cnt / k;
		printf("cnt : %d\n", cnt);

		if (gap == 1 && k!= 2)
		{
			mid1 = mid2 = left+1;
			mid2 += gap;
		}
		else if (gap == 0 && k!= 2)
		{
			mid1 = left;
			mid2 = right;
		}
		else if (k == 2)
		{
			mid2 = mid1 = (left + right) / k;
			mid2 += gap;
		}
		else
		{
			mid2 = mid1 = (left + right) / k;
			mid2 += gap;
		}


		printf("left : %d, right : %d\n", left, right);
		printf("mid1 : %d,  mid2 : %d,  gap : %d\n" ,mid1 , mid2, gap);

		//ù��° �������� �Լ�
		kmerge_sort(list, left, mid1, k);

		//��� ���� ���� �Լ��� gap+k�� right���� �۾ƾ���! ������ x
		while(mid2 < right)
		{
			if (gap == 0)
				break;
			kmerge_sort(list, mid1+1, mid2, k);
			mid1 = mid2;
			mid2 += gap;
			printf("mid1 : %d,  mid2 : %d,  gap : %d\n", mid1, mid2, gap);
		}

		//������ �������� �Լ�
		kmerge_sort(list, mid1 + 1, right, k);	

		//�պ�
		merge(list, left, mid1, right);

	}
}

int main()
{
	int i, n, k;
	n = 10;
	srand((int)time(NULL));

	for (i = 0; i < n; i++)
		list[i] = rand() % 10;

	for (i = 0; i < n; i++)
		printf("%d ", list[i]);
	printf("\n");

	printf("��� �����ðڽ��ϱ�? >>");
	scanf("%d", &k);

	kmerge_sort(list, 0, n - 1, k);

	for (i = 0; i < n; i++)
		printf("%d  ", list[i]);
	printf("\n");

	//k = 3�̻��ϰ�� 80%�� ���ĵ�...
	//n = 10�����϶��� ����
}