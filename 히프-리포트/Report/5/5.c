#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENT 100

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct TreeNode
{
	int weight;	//빈도수
	char newcode[10];	//허프만 코드
	struct TreeNode *left_child;
	struct TreeNode *right_child;
}TreeNode;

typedef struct
{
	TreeNode *ptree;
	int key;
}element;

typedef struct
{
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

void init(HeapType *h)
{
	h->heap_size = 0;
}

void insert_min_heap(HeapType *h, element item)
{
	int i = ++h->heap_size;

	while (i != 1 && item.key < h->heap[i / 2].key)
	{
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;
}

element delete_min_heap(HeapType *h)
{
	element item, temp;
	int parent, child;

	parent = 1;
	child = 2;

	item = h->heap[1];
	temp = h->heap[h->heap_size--];

	while (child <= h->heap_size)
	{
		if (child < h->heap_size && (h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key)
			break;

		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;			
	}
	h->heap[parent] = temp;

	return item;
}

TreeNode* make_tree(TreeNode *left, TreeNode *right)
{
	TreeNode *node = (TreeNode*)malloc(sizeof(TreeNode));
	if (node == NULL)
	{
		fprintf(stderr, "메모리 할당 에러 \n");
		exit(1);
	}
	node->left_child = left;
	node->right_child = right;
	return node;
}

void destroy_tree(TreeNode *root)
{
	if (root == NULL)
		return;
	destroy_tree(root->left_child);
	destroy_tree(root->right_child);
	free(root);
}

void min_heap_sort(element a[], int n)
{
	int i;
	HeapType h;
	int k = -1;

	init(&h);
	for (i = 0; i < n; i++)
		insert_min_heap(&h, a[i]);

	for (i = n - 1; i >= 0; i--)
		a[++k] = delete_min_heap(&h);

	for (i = 0; i < n; i++)
		printf("%d  ", a[i].key);
	printf("\n");
}

void print_heap(HeapType *h)
{
	int i;

	for (i = 1; i <= h->heap_size; i++)
		printf("h[%d] -> %d   \n", i, h->heap[i].key);
	printf("\n");
}

element huffman_tree(int freq[], int n)
{
	int i;
	TreeNode *node, *x;
	HeapType h;
	element e, e1, e2;

	init(&h);

	//일단 각각의 빈도수 값을 가진 노드를 원하는 수 만큼 생성
	for (i = 0;i < n;i++)
	{
		node = make_tree(NULL, NULL);
		e.key = node->weight = freq[i];
		e.ptree = node;
		insert_min_heap(&h, e);
	}


	for (i = 1; i < n; i++)
	{
		e1 = delete_min_heap(&h);
		e2 = delete_min_heap(&h);
		//최솟값을 가진 두 노드를 단말 노드로 

		x = make_tree(e1.ptree, e2.ptree);
		//새로운 노드를 하나 만듬

		e.key = x->weight = e1.key + e2.key;
		//그것에 대한 빈도수 값은 둘을 합친 것

		e.ptree = x;
		//최솟값을 가진 두 노드를 자식으로 가진 새로운 노드 하나 생성

		insert_min_heap(&h, e);
		//힙에 대입
	}

	e = delete_min_heap(&h);//결과적으로 남은 마지막 노드
	return e;	//허프만 트리 반환
}

void preorder(TreeNode *ptree, char *code)	//전위 순회로 트리를 돌며 각 노드가 가지고 있는 코드를 입력 받음
{
	char lcode[10] = "";
	char rcode[10] = "";

	if (ptree)	//트리가 널이면 안됨!
	{
		strcpy(ptree->newcode, code);		// lcode, rcode에 따라 달라지는 code값을 ptree->newcode에 대입

		strcpy(lcode, code);				// lcode에 code를 대입
		strcpy(rcode, code);				// rcode에 code를 대입
		strcat(lcode, "1");					// code가 대입된 lcode에 새로 '1'을 이어 붙임 -> 왼쪽 노드는 1
		strcat(rcode, "0");					// code가 대입된 rcode에 새로 '0'을 이어 붙임 -> 오른쪽 노드는 0
		//V

		//LR
		preorder(ptree->left_child, lcode);		// 왼쪽 자식에게는 lcode를
		preorder(ptree->right_child, rcode);		// 오른쪽 자식에게는 rcode를 새로운 code값으로 넘겨줌
	}
}


void print_code(TreeNode *ptree)	//중위 순회로 트리를 돌며 코드 출력! LVR
{
	if (ptree)
	{
		print_code(ptree->left_child); //L
		if (ptree)
			printf("%d -> %s\n", ptree->weight, ptree->newcode); //V
		print_code(ptree->right_child); //R
	}
}

int main()
{
	element huffman;
	int freq[] = { 15, 12, 8, 6, 4 };	//e, t, n, i, s
	char code[10] = "";

	huffman = huffman_tree(freq, 5);
	preorder(huffman.ptree, code);
	print_code(huffman.ptree);
}

//(5) 책 연습문제 8장 23번. (프로그램 8_6을 수정하여 각 문자에 대한 호프만 코드를 출력하시오.즉 e는 00, t 01, n 11, i100, s 101의 결과를 볼 수 있도록 하시오)