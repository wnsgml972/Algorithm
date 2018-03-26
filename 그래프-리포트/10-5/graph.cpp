#include <stdio.h>
#include "graph.h"


void graph_init(GraphType *g, int n)
{
	int v;
	g->n = n;
	g->adj_list = new GraphNode *[n];
	for (v = 0;v<n;v++)
		g->adj_list[v] = NULL;
}

void destroy_graph(GraphType *g)
{
	int i;
	for (i = 0;i<g->n;i++)
	{
		GraphNode *node = g->adj_list[i];
		while (node != NULL)
		{
			GraphNode *temp = node->link;
			delete node;
			node = temp;
		}
	}
	delete[] g->adj_list;
}

void insert_edge(GraphType *g, int u, int v, int weight)
{
	GraphNode *node;
	if (u >= g->n || v >= g->n)
	{
		printf("그래프: 정점 번호 오류");
		return;
	}

	node = new GraphNode;
	node->vertex = v;
	node->weight = weight;

	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

void print_graph(GraphType *g)
{
	int i;
	GraphNode *node;
	printf("List of edges:\n");
	for (i = 0;i<g->n;i++)
	{
		node = g->adj_list[i];
		while (node != NULL)
		{
			printf("<%d, %d, %d >", i, node->vertex, node->weight);
			node = node->link;
		}
		printf("\n");
	}
	printf("\n");
}

GraphNode *findNode(GraphNode *node, int vertex)
{
	while (node != NULL)
	{
		if (node->vertex == vertex)
			return node;
		node = node->link;
	}
	return node;
}

void delete_edge(GraphType *g, int u, int v)
{
	if (u >= g->n || v >= g->n)
	{
		printf("그래프: 정점 번호 오류");
		return;
	}
	GraphNode *node;
	node = findNode(g->adj_list[u], v);
	if (node != NULL)
	{
		if (g->adj_list[u] != node)
		{
			GraphNode *temp = g->adj_list[u];
			while (temp->link != node)
				temp = temp->link;
			temp->link = node->link;
		}
		else
		{
			g->adj_list[u] = node->link;
		}
		delete node;
	}
}