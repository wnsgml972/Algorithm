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

int path[MAX_VERTICES][MAX_VERTICES];   //최단거리 정점까지 거치는 노드들을 저장
int check[MAX_VERTICES];				//한 정점으로 가는 정점을 표시, 각 정점이 연결된 만큼 늘어남 ex) 1->2->3->4 이면 check[1] = 4

//초기화
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

	//각각 초기화
	path_init(path);	//일단 다 갈수없음(INF)으로 초기화
	for (i = 0;i<n;i++)
	{
		distance[i] = weight[start][i];
		found[i] = FALSE;
		check[i] = 1;
		path[i][0] = start;	//처음 시작은 다 start에서 시작함
	}

	found[start] = TRUE;
	distance[start] = 0;

	for (i = 0;i<n - 1;i++) 
	{
		u = choose(distance, n, found);	//최단경로 u를 선택
		found[u] = TRUE;	//찾은거로 바꿈

		//원래 거리보다 더 최단경로가 있는지 검사해서 바꿔줌
		for (w = 0;w < n;w++) 
			if (!found[w])
				if (distance[u] + weight[u][w] < distance[w])
				{
					if (i == 0) //처음에는 인접한 정점에 연결
					{
						path[w][check[w]] = u; //갱신된 경로를 경로 배열에 저장
						check[w]++;
					}
					else
					{
						for (j = 0; j < (check[u] + 1); j++) //저장된 만큼 반복
						{
							path[w][j] = path[u][j]; //경로를 갱신 그때 그때 입력해논 최단경로만 이용해서 다른 최단경로를 갱신함
							path[w][j + 1] = u; //끝부분에 자기자신을 저장
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
		if (i == start)	//시작 정점은 제외
			continue;
		printf("%d부터 --> %d까지\n", start, i);
		for (j = 0; j<MAX_VERTICES; j++)
			if (path[i][j] != INF)
				printf("%d -> ", path[i][j]);  //저장된 경로를 출력한다

		printf("%d\n", i);
		printf("Total distance : %d\n\n", distance[i]);
	}
}

void main()
{
	int start = 0;	//시작 정점
	
	printf("------------- Dijstra 알고리즘 최단경로 출력-------------\n\n");
	printf("시작 정점을 선택하시오 >> ");
	scanf("%d", &start);
	if (start < 0 || start >= MAX_VERTICES)
	{
		printf("잘못 선택하셨습니다.\n");
		return;
	}
	
	shortest_path(start, MAX_VERTICES);
	print_distance(start, MAX_VERTICES);
}
