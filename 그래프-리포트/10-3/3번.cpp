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
//449p 그림 10-36

int A[MAX_VERTICES][MAX_VERTICES];
int path[MAX_VERTICES][MAX_VERTICES];   //최단거리 정점까지 거치는 노드들을 저장

//초기화
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
	
	path_init(path);	//경로를 초기화 시켜줌
	for (i = 0; i < n; i++)
		for (j = 0;j < n; j++)
			A[i][j] = weight[i][j];
	
	for (k = 0;k < n;k++)	//k는 들리는 경로
		for (i = 0;i < n;i++)
			for (j = 0;j < n;j++)
				if (A[i][k] + A[k][j] < A[i][j])
				{
					path[i][j] = k;	//i에서 j로 가는도중 k를 들린다면 그 k값을 저장
					A[i][j] = A[i][k] + A[k][j];
				}
}

// 경로를 저장해놓은 path행렬을 이용해서 start부터 end까지의 중간 이동 경로를 출력
void print_path(int s, int e) 
{
	if (path[s][e] != INF)	//경로가 없다면 넘어감
	{
		print_path(s, path[s][e]);		//첫번째에서 바로 다음칸으로 가는 부분 계속 순환을 돌다보면 끝 부분은 바로 다음 경로만 남음 나머지는 INF에서 걸림
		printf(" %d -->", path[s][e]);
		print_path(path[s][e], e);		//2번째에서 마지막까지 가는부근을 순환을 돌며 끝까지 출력해줌
	}
}

void print_distance(int start, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (i == start)	//시작 정점 제외
			continue;
		printf("%d부터 --> %d까지\n", start, i);
		printf("%d --> ", start);
		print_path(start, i);
		printf(" %d\n", i);
		printf("Total distance : %d\n\n", A[start][i]);
	}
}

void main()
{
	int start = 0;	//시작 정점

	printf("------------- Floyd 알고리즘 최단경로 출력-------------\n\n");
	printf("시작 정점을 선택하시오 >> ");
	scanf("%d", &start);
	if (start < 0 || start >= MAX_VERTICES)
	{
		printf("잘못 선택하셨습니다.\n");
		return;
	}
	printf("\n");

	floyd(MAX_VERTICES);
	print_distance(start, MAX_VERTICES);
}