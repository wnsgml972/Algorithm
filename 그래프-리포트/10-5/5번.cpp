#include "graph.h"
#include "shortPath.h"

/*
int weight[MAX_VERTICES][MAX_VERTICES] =
{
	{ 0,7,INF,INF,3,10,INF },	0 : 1,4,5
	{ 7,0,4,10,2,6,INF },		1 : 0,2,3,4,5
	{ INF,4,0,2,INF,INF,INF },	2 : 1,3
	{ INF,10,2,0,11,9,4 },		3 : 1,2,4,5,6
	{ 3,2,INF,11,0,INF,5 },		4 : 0,1,3,6
	{ 10,6,INF,9,INF,0,INF },	5 : 0,1,3
	{ INF,INF,INF,4,5,INF,0 }	6 : 3,4
};
*/


//449page 그림 10-36
void insert_grahp(GraphType *g)
{
	insert_edge(g, 0, 1, 7);
	insert_edge(g, 0, 4, 3);
	insert_edge(g, 0, 5, 10);

	insert_edge(g, 1, 0, 7);
	insert_edge(g, 1, 2, 4);
	insert_edge(g, 1, 3, 10);
	insert_edge(g, 1, 4, 2);
	insert_edge(g, 1, 5, 6);

	insert_edge(g, 2, 1, 4);
	insert_edge(g, 2, 3, 2);

	insert_edge(g, 3, 1, 10);
	insert_edge(g, 3, 2, 2);
	insert_edge(g, 3, 4, 11);
	insert_edge(g, 3, 5, 9);
	insert_edge(g, 3, 6, 4);

	insert_edge(g, 4, 0, 3);
	insert_edge(g, 4, 1, 2);
	insert_edge(g, 4, 3, 11);
	insert_edge(g, 4, 6, 5);

	insert_edge(g, 5, 0, 10);
	insert_edge(g, 5, 1, 6);
	insert_edge(g, 5, 3, 9);

	insert_edge(g, 6, 3, 4);
	insert_edge(g, 6, 4, 5);
}

int main()
{
	GraphType g;

	graph_init(&g, 7);	// 7개의 정점을 가진 그래프 초기화
	insert_grahp(&g);
	print_graph(&g);	//초기 그래프

	short_path_Dijstra(&g);

	//완성하시오
}


/*

최단경로
5. shortest_path구하는 프로그램(책 프로그램 10.10)을 prim과제.txt 처럼  연결리스트로 구현하고 파일 분리하기.

*/