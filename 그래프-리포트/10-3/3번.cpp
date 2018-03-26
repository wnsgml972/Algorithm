#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#define MAX_VERTICES 7
#define INF 1000

int weight[MAX_VERTICES][MAX_VERTICES] =
{
	{ 0,7,INF,INF,3,10,INF },	//0 : 1, 4, 5
	{ 7,0,4,10,2,6,INF},		//1 : 0, 2, 3, 4, 5
	{ INF,4,0,2,INF,INF,INF },	//2 : 1, 3
	{ INF,10,2,0,11,9,4 },		//3 : 1, 2, 4, 5, 6
	{ 3,2,INF,11,0,INF,5 },		//4 : 0, 1, 3, 6
	{ 10,6,INF,9,INF,0,INF },	//5 : 0, 1, 3
	{ INF,INF,INF,4,5,INF,0 }	//6 : 3, 4
};
//449p �׸� 10-36

int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];   //�ִܰŸ� �������� ��ġ�� ������ ����

//�ʱ�ȭ
void path_init(int path[][MAX_VERTICES])
{
	int i, j;

	for (i = 0;i<MAX_VERTICES;i++)
		for (j = 0;j<MAX_VERTICES;j++)
			path[i][j] = INF;	
}

void floyd(int n)
{
	int i, j, k;
	
	path_init(path);	//��θ� �ʱ�ȭ ������
	for (i = 0; i < n; i++)
		for (j = 0;j < n; j++)
			A[i][j] = weight[i][j];
	
	for (k = 0;k < n;k++)	//k�� �鸮�� ���
		for (i = 0;i < n;i++)
			for (j = 0;j < n;j++)
				if (A[i][k] + A[k][j] < A[i][j])
				{
					path[i][j] = k;	//i���� j�� ���µ��� k�� �鸰�ٸ� �� k���� ����
					A[i][j] = A[i][k] + A[k][j];
				}
}

// ��θ� �����س��� path����� �̿��ؼ� start���� end������ �߰� �̵� ��θ� ���
void print_path(int s, int e) 
{
	if (path[s][e] != INF)	//��ΰ� ���ٸ� �Ѿ
	{
		print_path(s, path[s][e]);		//ù��°���� �ٷ� ����ĭ���� ���� �κ� ��� ��ȯ�� ���ٺ��� �� �κ��� �ٷ� ���� ��θ� ���� �������� INF���� �ɸ�
		printf(" %d -->", path[s][e]);
		print_path(path[s][e], e);		//2��°���� ���������� ���ºα��� ��ȯ�� ���� ������ �������
	}
}

void print_distance(int start, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i == start)	//���� ���� ����
			continue;
		printf("%d���� --> %d����\n", start, i);
		printf("%d --> ", start);
		print_path(start, i);
		printf(" %d\n", i);
		printf("Total distance : %d\n\n", A[start][i]);
	}
}

void main()
{
	int start = 0;	//���� ����

	printf("------------- Floyd �˰��� �ִܰ�� ���-------------\n\n");
	printf("���� ������ �����Ͻÿ� >> ");
	scanf("%d", &start);
	if (start < 0 || start >= MAX_VERTICES)
	{
		printf("�߸� �����ϼ̽��ϴ�.\n");
		return;
	}
	printf("\n");

	floyd(MAX_VERTICES);
	print_distance(start, MAX_VERTICES);
}