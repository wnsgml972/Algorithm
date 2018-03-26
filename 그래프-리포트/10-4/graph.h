#ifndef	GRAPH_H
#define	GRAPH_H

typedef struct GraphNode
{
	int vertex;
	int weight;
	struct GraphNode *link;
}GraphNode;

typedef struct
{
	int n;	//정점의 개수
	GraphNode **adj_list;
}GraphType;

extern void graph_init(GraphType *g, int n);
extern void destroy_graph(GraphType *g);
extern void insert_edge(GraphType *g, int u, int v, int weight);
extern void print_graph(GraphType *g);
extern GraphNode *findNode(GraphNode *node, int vertex);
extern void delete_edge(GraphType *g, int u, int v);

#endif