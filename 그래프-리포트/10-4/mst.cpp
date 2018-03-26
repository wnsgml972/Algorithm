#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "mst.h"

//탐욕적인 알고리즘(그때 그때 최선의 방법을 선택하는 알고리즘)  -> 최소 dist값을 갖는 정점을 반환함
GraphType *mst_greedy(GraphType *g)
{
	int	edges = 0;		//간선들의 수
	int	n, *selected;	//정점의 개수, selected
	int	minU;			//정점 u
	int start;			//start 인덱스

	n = g->n;
	selected = new int[n];

	for (int i = 0;i<n;i++)
		selected[i] = FALSE;	//selected를 다 0으로 초기화

	printf("------------- Greedy 알고리즘 경로 출력-------------\n\n");
	printf("시작 정점을 선택하시오 >> ");
	scanf("%d", &start);
	if (start < 0 || start >= n)
	{
		printf("잘못 선택하셨습니다.\n");
		exit(0);
	}
	printf("\n");

	selected[start] = TRUE; //시작은 1
	minU = start;	//start부터 시작

	GraphType *t = new GraphType;
	graph_init(t, n);

	while (edges < n - 1)
	{
		int	minV = -1;	//정점 v
		int	minE = 0;	//가중치
	
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
			printf("(%d, %d), 가중치 : %d\n", minU, minV, minE);	//함수가 도는 상황을 보여줌
		if (minV == -1)	//만약 어느 노드도 가지못하고 끝나면 break
			break;

		selected[minV] = TRUE;
		edges++;
		insert_edge(t, minU, minV, minE);
		minU = minV;	//마지막 장소에서 다시 시작하게 만듬
	}

	delete[] selected;

	return t;
}

//prim 알고리즘
GraphType *mst_prim(GraphType *g)
{
	int	edges = 0;		//간선들의 수
	int	n, *selected;	//정점의 개수, selected
	int *selected_vertex;//선택된 정점의 배열
	int	minU;			//정점 u
	int start;			//start 인덱스
	int cnt = 0;		//선택된 정점의 갯수
	
	n = g->n;
	selected = new int[n];
	selected_vertex = new int[n];

	for (int i = 0;i<n;i++)
		selected[i] = FALSE;	//selected를 다 0으로 초기화

	printf("------------- prim 알고리즘 경로 출력-------------\n\n");
	printf("시작 정점을 선택하시오 >> ");
	scanf("%d", &start);
	if (start < 0 || start >= n)
	{
		printf("잘못 선택하셨습니다.\n");
		exit(0);
	}
	printf("\n");

	selected[start] = TRUE; //시작은 1
	minU = start;	//start부터 시작

	GraphType *t = new GraphType;
	graph_init(t, n);

	int resultV;
	int resultE;

	while (edges < n - 1)
	{
		cnt++;	//한번돌때마다 선택된 정점은 늘어남
		selected_vertex[cnt - 1] = minU; //계속 마지막 자리에 선택된 정점 삽입

		resultV = 0;	//제일 작은 가중치를 가진 정점
		resultE = 0;	//제일 작은 가중치

		for (int i = 0; i < cnt; i++)
		{
			int	minV = -1;	//정점 v
			int	minE = 0;	//가중치

			GraphNode *node = g->adj_list[selected_vertex[i]];	//선택된 정점을 모두 돔

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

			if (i == 0)		//일단 첫 시작시 초기화
			{
				resultV = minV;
				resultE = minE;
			}

			if (i != 0 && resultV == -1)	//만약 첫 초기화 이후 start정점에서 아무런 값도 얻지 못했을 시 이후 초기화
			{
				resultV = minV;
				resultE = minE;
			}

			if (resultE > minE && minV != -1)	//가장 최소 가중치 값을 구함 (맨끝에 아무노드도 없을 경우도 계산)
			{
				resultV = minV;
				resultE = minE;
			}
		}

		selected[resultV] = TRUE;
		edges++;
		insert_edge(t, minU, resultV, resultE);
		minU = resultV;	//선택된 정점을 대입
	}

	//마지막 함수 빠져나오면서 추가 못한 부분을 추가
	cnt++;
	selected_vertex[cnt - 1] = minU;

	//순서대로 정점을 보여줌
	for (int i = 0; i < cnt; i++)
		printf("%d번째 : %d\n", i + 1, selected_vertex[i]);

	delete[] selected;

	return t;	//마지막으로 최소 신장트리를 가진 그래프 반환
}