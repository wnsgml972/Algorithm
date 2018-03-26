#include "graph.h"
#include "mst.h"

//437page Quiz 그래프

void insert_grahp(GraphType *g)
{
	insert_edge(g, 0, 3, 6);
	insert_edge(g, 0, 7, 1);
	insert_edge(g, 0, 1, 10);

	insert_edge(g, 1, 0, 10);
	insert_edge(g, 1, 5, 2);
	insert_edge(g, 1, 2, 4);

	insert_edge(g, 2, 1, 4);
	insert_edge(g, 2, 5, 7);
	insert_edge(g, 2, 3, 11);

	insert_edge(g, 3, 2, 11);
	insert_edge(g, 3, 7, 3);
	insert_edge(g, 3, 0, 6);

	insert_edge(g, 4, 7, 8);
	insert_edge(g, 4, 5, 5);

	insert_edge(g, 5, 1, 2);
	insert_edge(g, 5, 2, 7);
	insert_edge(g, 5, 4, 5);
	insert_edge(g, 5, 6, 9);

	insert_edge(g, 6, 7, 12);
	insert_edge(g, 6, 5, 9);

	insert_edge(g, 7, 0, 1);
	insert_edge(g, 7, 3, 3);
	insert_edge(g, 7, 4, 8);
	insert_edge(g, 7, 6, 12);
}

int main()
{
	GraphType g;
	
	graph_init(&g, 8);	// 8개의 정점을 가진 그래프 초기화
	insert_grahp(&g);
	print_graph(&g);	//초기 그래프
	
	mst_greedy(&g);
	mst_prim(&g);

	//완성하시오
}


/*

4. prim과제.txt에 있는 mst_greedy 함수에 주석을 붙이고 mst_prim 함수를 완성하시오.(주석을 붙이시오)
test.cpp에 책의 퀴즈나 연습문제에 있는 그래프를 입력하여 실행시켜 보시오.

*/