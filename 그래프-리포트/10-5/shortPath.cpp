#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "shortPath.h"

//��� ��� �Լ�
void printPath(int start, int n , int *distance, int *pred)
{
	int i, j;

	for (i = 0;i<n;i++)
		if (i != start)
		{
			printf("\nDistance of %d = %d \n", i, distance[i]);
			printf("Path = %d ", i);
			
			j = i;
			do
			{
				j = pred[j];
				printf("<- %d ", j);
			} while (j != start);	//��ȯ�ϴ°�ó�� ��� ���� �ٲ���
			printf("\n");
		}
}

//Dijstra �˰���
void short_path_Dijstra(GraphType *g)
{
	int start, n, i;
	int *distance, *pred, *selected;	//�Ÿ�, �������� ���� ����, ����
	int edges, mindistance, nextnode;

	n = g->n;

	distance = new int[n];
	pred = new int[n];
	selected = new int[n];

	printf("------------- Dijstra �˰��� ��� ���-------------\n\n");
	printf("���� ������ �����Ͻÿ� >> ");
	scanf("%d", &start);
	if (start < 0 || start >= n)
	{
		printf("�߸� �����ϼ̽��ϴ�.\n");
		exit(0);
	}
	printf("\n");
	
	//�ʱ�ȭ�κ�
	for (i = 0;i<n;i++)
	{
		distance[i] = INF;
		pred[i] = start;
		selected[i] = 0;
	}

	distance[start] = 0;
	edges = 0;

	GraphNode *p;

	while (edges < n - 1)
	{
		mindistance = INF;

		// �������� ���� ���� �Ÿ��� ���� �ε��� ��!
		for (i = 0;i<n;i++)
			if (distance[i] < mindistance && !selected[i])	//���õ��� �����鼭 ���� �Ÿ��� �������� ã��
			{
				mindistance = distance[i];	//�Ÿ� �ʱ�ȭ
				nextnode = i;
			}
		

		selected[nextnode] = 1;	//������ 1�� �ٲ�

		//nextnode�� �̿��� �� ���� ���� �ִ��� �˻�!
		for (p = g->adj_list[nextnode];p != NULL;p = p->link)	//nextnode �ε��� ���� ������ ��� ������ ��
			if (!selected[p->vertex])	//���õ��� ���� ���߿�
				if (mindistance + p->weight < distance[p->vertex])	//�� ���� �Ÿ��� �ִ��� �˻�
				{
					distance[p->vertex] = mindistance + p->weight;	//�ٲ���
					pred[p->vertex] = nextnode;						//�ٲ���
				}
		edges++;	//���� �߰�
	}

	//��ο� ���� �Ÿ� ���!
	printPath(start, n, distance, pred);
}