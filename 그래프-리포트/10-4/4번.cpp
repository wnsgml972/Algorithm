#include "graph.h"
#include "mst.h"

//437page Quiz �׷���

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
	
	graph_init(&g, 8);	// 8���� ������ ���� �׷��� �ʱ�ȭ
	insert_grahp(&g);
	print_graph(&g);	//�ʱ� �׷���
	
	mst_greedy(&g);
	mst_prim(&g);

	//�ϼ��Ͻÿ�
}


/*

4. prim����.txt�� �ִ� mst_greedy �Լ��� �ּ��� ���̰� mst_prim �Լ��� �ϼ��Ͻÿ�.(�ּ��� ���̽ÿ�)
test.cpp�� å�� ��� ���������� �ִ� �׷����� �Է��Ͽ� ������� ���ÿ�.

*/