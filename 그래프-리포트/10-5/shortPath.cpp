#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "shortPath.h"

//경로 출력 함수
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
			} while (j != start);	//순환하는것처럼 계속 가며 바꿔줌
			printf("\n");
		}
}

//Dijstra 알고리즘
void short_path_Dijstra(GraphType *g)
{
	int start, n, i;
	int *distance, *pred, *selected;	//거리, 경로출력을 위한 변수, 선택
	int edges, mindistance, nextnode;

	n = g->n;

	distance = new int[n];
	pred = new int[n];
	selected = new int[n];

	printf("------------- Dijstra 알고리즘 경로 출력-------------\n\n");
	printf("시작 정점을 선택하시오 >> ");
	scanf("%d", &start);
	if (start < 0 || start >= n)
	{
		printf("잘못 선택하셨습니다.\n");
		exit(0);
	}
	printf("\n");
	
	//초기화부분
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

		// 다음노드는 가장 작은 거리를 가진 인덱스 값!
		for (i = 0;i<n;i++)
			if (distance[i] < mindistance && !selected[i])	//선택되지 않으면서 가장 거리가 작은것을 찾음
			{
				mindistance = distance[i];	//거리 초기화
				nextnode = i;
			}
		

		selected[nextnode] = 1;	//간곳은 1로 바꿈

		//nextnode를 이용해 더 빠른 길이 있는지 검사!
		for (p = g->adj_list[nextnode];p != NULL;p = p->link)	//nextnode 인덱스 부터 시작해 계속 포문을 돔
			if (!selected[p->vertex])	//선택되지 않은 곳중에
				if (mindistance + p->weight < distance[p->vertex])	//더 빠른 거리가 있는지 검사
				{
					distance[p->vertex] = mindistance + p->weight;	//바꿔줌
					pred[p->vertex] = nextnode;						//바꿔줌
				}
		edges++;	//간선 추가
	}

	//경로와 최종 거리 출력!
	printPath(start, n, distance, pred);
}