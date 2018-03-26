#ifndef	SHART_PATH
#define	SHART_PATH

#define TRUE 1
#define FALSE 0
#define INF 9999

extern void short_path_Dijstra(GraphType *g);
extern void printPath(int start, int n, int *distance, int *pred);

#endif