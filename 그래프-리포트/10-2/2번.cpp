#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <limits.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 8
#define INF 1000

int weight[MAX_VERTICES][MAX_VERTICES] =
{
	{ 0,7,5,INF,INF,2,INF,INF },	//0 : 1 ,2 ,5
	{ 7,0,INF,6,2,INF,INF,1 },		//1 : 0, 4, 7, 3
	{ 5,INF,0,2,INF,5,INF,INF },	//2 : 0, 5, 3
	{ INF,6,2,0,INF,INF,2,8 },		//3 : 1, 2, 6, 7
	{ INF,2,INF,INF,0,2,INF,4 },	//4 : 1, 5, 7
	{ 2,INF,5,INF,2,0,4,INF },		//5 : 0, 2, 4, 6
	{ INF,INF,INF,2,INF,4,0,4 }		//6 : 3, 5, 7
};
//452p quiz (1)

int distance[MAX_VERTICES];
int found[MAX_VERTICES];

int path[MAX_VERTICES][MAX_VERTICES];   //�ִܰŸ� �������� ��ġ�� ������ ����
int check[MAX_VERTICES];				//�� �������� ���� ������ ǥ��, �� ������ ����� ��ŭ �þ ex) 1->2->3->4 �̸� check[1] = 4

//�ʱ�ȭ
void path_init(int path[][MAX_VERTICES])
{
	int i, j;

	for (i = 0;i<MAX_VERTICES;i++)
		for (j = 0;j<MAX_VERTICES;j++)
			path[i][j] = INF;
}


int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0;i<n;i++)
		if (distance[i]<min && !found[i]) 
		{
			min = distance[i];
			minpos = i;
		}

	return minpos;
}

void shortest_path(int start, int n)
{
	int i, j, u, w;

	//���� �ʱ�ȭ
	path_init(path);	//�ϴ� �� ��������(INF)���� �ʱ�ȭ
	for (i = 0;i<n;i++)
	{
		distance[i] = weight[start][i];
		found[i] = FALSE;
		check[i] = 1;
		path[i][0] = start;	//ó�� ������ �� start���� ������
	}

	found[start] = TRUE;
	distance[start] = 0;

	for (i = 0;i<n - 1;i++) 
	{
		u = choose(distance, n, found);	//�ִܰ�� u�� ����
		found[u] = TRUE;	//ã���ŷ� �ٲ�

		//���� �Ÿ����� �� �ִܰ�ΰ� �ִ��� �˻��ؼ� �ٲ���
		for (w = 0;w < n;w++) 
			if (!found[w])
				if (distance[u] + weight[u][w] < distance[w])
				{
					if (i == 0) //ó������ ������ ������ ����
					{
						path[w][check[w]] = u; //���ŵ� ��θ� ��� �迭�� ����
						check[w]++;
					}
					else
					{
						for (j = 0; j < (check[u] + 1); j++) //����� ��ŭ �ݺ�
						{
							path[w][j] = path[u][j]; //��θ� ���� �׶� �׶� �Է��س� �ִܰ�θ� �̿��ؼ� �ٸ� �ִܰ�θ� ������
							path[w][j + 1] = u; //���κп� �ڱ��ڽ��� ����
							check[w]++;
						}
					}
					distance[w] = distance[u] + weight[u][w];
				}
	}
}

void print_distance(int start, int n)
{
	int i, j;
	printf("\n");
	for (i = 0;i < n;i++)
	{
		if (i == start)	//���� ������ ����
			continue;
		printf("%d���� --> %d����\n", start, i);
		for (j = 0; j<MAX_VERTICES; j++)
			if (path[i][j] != INF)
				printf("%d -> ", path[i][j]);  //����� ��θ� ����Ѵ�

		printf("%d\n", i);
		printf("Total distance : %d\n\n", distance[i]);
	}
}

void main()
{
	int start = 0;	//���� ����
	
	printf("------------- Dijstra �˰��� �ִܰ�� ���-------------\n\n");
	printf("���� ������ �����Ͻÿ� >> ");
	scanf("%d", &start);
	if (start < 0 || start >= MAX_VERTICES)
	{
		printf("�߸� �����ϼ̽��ϴ�.\n");
		return;
	}
	
	shortest_path(start, MAX_VERTICES);
	print_distance(start, MAX_VERTICES);
}
