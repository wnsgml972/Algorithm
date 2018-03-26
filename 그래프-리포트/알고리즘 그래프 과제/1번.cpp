#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 8
#define INF 1000L

int weight[MAX_VERTICES][MAX_VERTICES] =
{
	{ 0,10,INF,6,INF,INF,INF,1 },	//0 : 1, 3, 7
	{ 10,0,4,INF,INF,2,INF,INF },	//1 : 0, 5, 2
	{ INF,4,0,11,INF,7,INF,INF },	//2 : 1, 5, 3
	{ 6,INF,11,0,INF,INF,INF,3 },	//3 : 0, 7, 2
	{ INF,INF,INF,INF,0,5,INF,8 },	//4 : 5, 7
	{ INF,2,7,INF,5,0,9,INF },		//5 : 1, 2, 4, 6
	{ INF,INF,INF,INF,INF,9,0,12 },	//6 : 5, 7
	{ 1,INF,INF,3,8,INF,12,0 }		//7 : 0, 3, 4, 6
};
// 437P QUIZ �׸�


int selected[MAX_VERTICES];	//������ 1 �ʱ�ȭ 0
int dist[MAX_VERTICES];		//�� �������� �� �� �ִ� �ּ� ����ġ like �Ÿ� (distance)

//dist�� selected�� �ʱ�ȭ ��Ŵ
void init(int s, int n)
{
	int u;

	for (u = 0;u<n;u++)
		dist[u] = INF;

	dist[s] = 0;	//ù ���� ������ 0���� ����

	for (u = 0;u<n;u++)
		selected[u] = FALSE;	//�� FALSE�� �ʱ�ȭ
}

//�ּ� ����ġ�� ã���ִ� �Լ�
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0;i<n;i++)
		if (!selected[i])	//selected�� ���� �Ȼ������� �˻� -> selected�� ���� 0�̸�	   -> �װ��߿� dist�� ã��
		{
			v = i;
			break;
		}

	for (i = 0;i<n;i++)
		if (!selected[i] && (dist[i]<dist[v]))
		{
			v = i;
		}
	return v;
}

//�ٲ���� �Ÿ��� ��ó�� �ִ� ���� ������ ã��
int adjacent_vertex(int v, int n)
{
	int i;	

	for (i = 0; i < n; i++)
		if (weight[v][i] == dist[v])
			break;
	return i;
}

void print_MST(int u, int n)
{
	printf("(%d, %d)\n", u, adjacent_vertex(u, MAX_VERTICES));
}

void prim(int s, int n)
{
	int i, u, v;

	init(s, n);	//�ʱ�ȭ

	for (i = 0;i < n;i++)
	{
		u = get_min_vertex(n);	//�ּ� ����ġ�� ã���ִ� �Լ�
		selected[u] = TRUE;		//������ 1

		if (dist[u] == INF)	//���� ���� ���̸� ����
			return;

		for (v = 0; v < n; v++)
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])  //�ϳ� ������ dist ������Ʈ �ϴ� �κ�, ������ �� ����ġ�� �� �����ŷ� �ʱ�ȭ �ɼ� �ִµ� �� �κ��̴�.
					dist[v] = weight[u][v];

		if(i != 0)	//�� ó�� ������ ����
			print_MST(u, MAX_VERTICES);		//����Ʈ�� ��� �Լ�
	}
}

void main()
{
	int start = 0;	//���� ����

	printf("------------- prim �˰��� ����Ʈ�� ���-------------\n\n");
	printf("���� ������ �����Ͻÿ� >> ");
	scanf("%d", &start);
	if (start < 0 || start >= MAX_VERTICES)
	{
		printf("�߸� �����ϼ̽��ϴ�.\n");
		return;
	}

	prim(start, MAX_VERTICES);
}


/*
���� Ʈ�� ��� ����ϱ� ����!
ex) (1, 0)  (2, 3)  (3, 4)
-> ������ ����Ǵ� ����


*/