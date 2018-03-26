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
// 437P QUIZ 그림


int selected[MAX_VERTICES];	//뽑히면 1 초기화 0
int dist[MAX_VERTICES];		//각 정점에서 갈 수 있는 최소 가중치 like 거리 (distance)

//dist와 selected를 초기화 시킴
void init(int s, int n)
{
	int u;

	for (u = 0;u<n;u++)
		dist[u] = INF;

	dist[s] = 0;	//첫 시작 정점은 0으로 만듬

	for (u = 0;u<n;u++)
		selected[u] = FALSE;	//다 FALSE로 초기화
}

//최소 가중치를 찾아주는 함수
int get_min_vertex(int n)
{
	int v, i;
	for (i = 0;i<n;i++)
		if (!selected[i])	//selected가 아직 안뽑혔으면 검사 -> selected가 아직 0이면	   -> 그값중에 dist를 찾음
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

//바뀌어진 거리중 근처에 있는 인접 정점을 찾음
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

	init(s, n);	//초기화

	for (i = 0;i < n;i++)
	{
		u = get_min_vertex(n);	//최소 가중치를 찾아주는 함수
		selected[u] = TRUE;		//뽑히면 1

		if (dist[u] == INF)	//갈수 없는 곳이면 종료
			return;

		for (v = 0; v < n; v++)
			if (weight[u][v] != INF)
				if (!selected[v] && weight[u][v] < dist[v])  //하나 뽑힌뒤 dist 업데이트 하는 부분, 정점이 각 가중치가 더 작은거로 초기화 될수 있는데 그 부분이다.
					dist[v] = weight[u][v];

		if(i != 0)	//맨 처음 정점은 생략
			print_MST(u, MAX_VERTICES);		//신장트리 출력 함수
	}
}

void main()
{
	int start = 0;	//시작 정점

	printf("------------- prim 알고리즘 신장트리 출력-------------\n\n");
	printf("시작 정점을 선택하시오 >> ");
	scanf("%d", &start);
	if (start < 0 || start >= MAX_VERTICES)
	{
		printf("잘못 선택하셨습니다.\n");
		return;
	}

	prim(start, MAX_VERTICES);
}


/*
신장 트리 모양 출력하기 과제!
ex) (1, 0)  (2, 3)  (3, 4)
-> 간선이 연결되는 과정


*/