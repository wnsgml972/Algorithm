#define _CRT_SECURE_NO_WARNINGS
#define MAX_ELEMENT 100

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct TreeNode
{
	int weight;	//�󵵼�
	char newcode[10];	//������ �ڵ�
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
		fprintf(stderr, "�޸� �Ҵ� ���� \n");
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

	//�ϴ� ������ �󵵼� ���� ���� ��带 ���ϴ� �� ��ŭ ����
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
		//�ּڰ��� ���� �� ��带 �ܸ� ���� 

		x = make_tree(e1.ptree, e2.ptree);
		//���ο� ��带 �ϳ� ����

		e.key = x->weight = e1.key + e2.key;
		//�װͿ� ���� �󵵼� ���� ���� ��ģ ��

		e.ptree = x;
		//�ּڰ��� ���� �� ��带 �ڽ����� ���� ���ο� ��� �ϳ� ����

		insert_min_heap(&h, e);
		//���� ����
	}

	e = delete_min_heap(&h);//��������� ���� ������ ���
	return e;	//������ Ʈ�� ��ȯ
}

void preorder(TreeNode *ptree, char *code)	//���� ��ȸ�� Ʈ���� ���� �� ��尡 ������ �ִ� �ڵ带 �Է� ����
{
	char lcode[10] = "";
	char rcode[10] = "";

	if (ptree)	//Ʈ���� ���̸� �ȵ�!
	{
		strcpy(ptree->newcode, code);		// lcode, rcode�� ���� �޶����� code���� ptree->newcode�� ����

		strcpy(lcode, code);				// lcode�� code�� ����
		strcpy(rcode, code);				// rcode�� code�� ����
		strcat(lcode, "1");					// code�� ���Ե� lcode�� ���� '1'�� �̾� ���� -> ���� ���� 1
		strcat(rcode, "0");					// code�� ���Ե� rcode�� ���� '0'�� �̾� ���� -> ������ ���� 0
		//V

		//LR
		preorder(ptree->left_child, lcode);		// ���� �ڽĿ��Դ� lcode��
		preorder(ptree->right_child, rcode);		// ������ �ڽĿ��Դ� rcode�� ���ο� code������ �Ѱ���
	}
}


void print_code(TreeNode *ptree)	//���� ��ȸ�� Ʈ���� ���� �ڵ� ���! LVR
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

//(5) å �������� 8�� 23��. (���α׷� 8_6�� �����Ͽ� �� ���ڿ� ���� ȣ���� �ڵ带 ����Ͻÿ�.�� e�� 00, t 01, n 11, i100, s 101�� ����� �� �� �ֵ��� �Ͻÿ�)