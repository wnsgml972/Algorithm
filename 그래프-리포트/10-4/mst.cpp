#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "mst.h"

//Ž������ �˰���(�׶� �׶� �ּ��� ����� �����ϴ� �˰���)  -> �ּ� dist���� ���� ������ ��ȯ��
GraphType *mst_greedy(GraphType *g)
{
	int	edges = 0;		//�������� ��
	int	n, *selected;	//������ ����, selected
	int	minU;			//���� u
	int start;			//start �ε���

	n = g->n;
	selected = new int[n];

	for (int i = 0;i<n;i++)
		selected[i] = FALSE;	//selected�� �� 0���� �ʱ�ȭ

	printf("------------- Greedy �˰��� ��� ���-------------\n\n");
	printf("���� ������ �����Ͻÿ� >> ");
	scanf("%d", &start);
	if (start < 0 || start >= n)
	{
		printf("�߸� �����ϼ̽��ϴ�.\n");
		exit(0);
	}
	printf("\n");

	selected[start] = TRUE; //������ 1
	minU = start;	//start���� ����

	GraphType *t = new GraphType;
	graph_init(t, n);

	while (edges < n - 1)
	{
		int	minV = -1;	//���� v
		int	minE = 0;	//����ġ
	
		GraphNode *node = g->adj_list[minU];

		while (node != NULL)
		{
			if (selected[node->vertex] == FALSE)
			{
				if ((node->weight < minE) || (minV < 0))
				{
					minE = node->weight;
					minV = node->vertex;
				}
			}
			node = node->link;
		}

		if(minV != -1)
			printf("(%d, %d), ����ġ : %d\n", minU, minV, minE);	//�Լ��� ���� ��Ȳ�� ������
		if (minV == -1)	//���� ��� ��嵵 �������ϰ� ������ break
			break;

		selected[minV] = TRUE;
		edges++;
		insert_edge(t, minU, minV, minE);
		minU = minV;	//������ ��ҿ��� �ٽ� �����ϰ� ����
	}

	delete[] selected;

	return t;
}

//prim �˰���
GraphType *mst_prim(GraphType *g)
{
	int	edges = 0;		//�������� ��
	int	n, *selected;	//������ ����, selected
	int *selected_vertex;//���õ� ������ �迭
	int	minU;			//���� u
	int start;			//start �ε���
	int cnt = 0;		//���õ� ������ ����
	
	n = g->n;
	selected = new int[n];
	selected_vertex = new int[n];

	for (int i = 0;i<n;i++)
		selected[i] = FALSE;	//selected�� �� 0���� �ʱ�ȭ

	printf("------------- prim �˰��� ��� ���-------------\n\n");
	printf("���� ������ �����Ͻÿ� >> ");
	scanf("%d", &start);
	if (start < 0 || start >= n)
	{
		printf("�߸� �����ϼ̽��ϴ�.\n");
		exit(0);
	}
	printf("\n");

	selected[start] = TRUE; //������ 1
	minU = start;	//start���� ����

	GraphType *t = new GraphType;
	graph_init(t, n);

	int resultV;
	int resultE;

	while (edges < n - 1)
	{
		cnt++;	//�ѹ��������� ���õ� ������ �þ
		selected_vertex[cnt - 1] = minU; //��� ������ �ڸ��� ���õ� ���� ����

		resultV = 0;	//���� ���� ����ġ�� ���� ����
		resultE = 0;	//���� ���� ����ġ

		for (int i = 0; i < cnt; i++)
		{
			int	minV = -1;	//���� v
			int	minE = 0;	//����ġ

			GraphNode *node = g->adj_list[selected_vertex[i]];	//���õ� ������ ��� ��

			while (node != NULL)
			{
				if (selected[node->vertex] == FALSE)
				{
					if ((node->weight < minE) || (minV < 0))
					{
						minE = node->weight;
						minV = node->vertex;
					}
				}
				node = node->link;
			}

			if (i == 0)		//�ϴ� ù ���۽� �ʱ�ȭ
			{
				resultV = minV;
				resultE = minE;
			}

			if (i != 0 && resultV == -1)	//���� ù �ʱ�ȭ ���� start�������� �ƹ��� ���� ���� ������ �� ���� �ʱ�ȭ
			{
				resultV = minV;
				resultE = minE;
			}

			if (resultE > minE && minV != -1)	//���� �ּ� ����ġ ���� ���� (�ǳ��� �ƹ���嵵 ���� ��쵵 ���)
			{
				resultV = minV;
				resultE = minE;
			}
		}

		selected[resultV] = TRUE;
		edges++;
		insert_edge(t, minU, resultV, resultE);
		minU = resultV;	//���õ� ������ ����
	}

	//������ �Լ� ���������鼭 �߰� ���� �κ��� �߰�
	cnt++;
	selected_vertex[cnt - 1] = minU;

	//������� ������ ������
	for (int i = 0; i < cnt; i++)
		printf("%d��° : %d\n", i + 1, selected_vertex[i]);

	delete[] selected;

	return t;	//���������� �ּ� ����Ʈ���� ���� �׷��� ��ȯ
}