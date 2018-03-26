#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct avl_node
{
	struct avl_node *left_child, *right_child;  /* Subtrees. */
	char word[10];
	int diff_height;

}avl_node;


int max(int x, int y)
{
	if (x >= y) 
		return x;
	else
		return y;
}

// ���� ȸ�� �Լ�
avl_node *rotate_left(avl_node *parent)
{
	avl_node *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;

	return child;
}

// ������ ȸ�� �Լ�
avl_node *rotate_right(avl_node *parent)
{
	avl_node *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// ������-���� ȸ�� �Լ�
avl_node *rotate_right_left(avl_node *parent)
{
	avl_node *child = parent->right_child;
	parent->right_child = rotate_left(child);
	return rotate_right(parent);
}
// ����-������ ȸ�� �Լ�
avl_node *rotate_left_right(avl_node *parent)
{
	avl_node *child = parent->left_child;
	parent->left_child = rotate_right(child);
	return rotate_left(parent);
}
// Ʈ���� ���̸� ��ȯ
int get_height(avl_node *node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left_child), get_height(node->right_child));
	return height;
}

// ����� �����μ��� ��ȯ
int get_height_diff(avl_node *node)
{
	if (node == NULL) 
		return 0;
	return
		get_height(node->left_child) - get_height(node->right_child);
}

// Ʈ���� ����Ʈ���� �����
avl_node *rebalance(avl_node *node)
{
	int height_diff = get_height_diff(node);
	if (height_diff > 1)	//1���� Ŭ�� ����
	{
		if (get_height_diff(node->left_child)> 0)	//���ʿ� ���ʿ� �پ ������ ����
			node = rotate_left(node);		//LLȸ��
		else
			node = rotate_left_right(node);	//LRȸ��
	}
	else if (height_diff < -1)	//1���� ������ ������
	{
		if (get_height_diff((node)->right_child) < 0)	//�����ʿ� �����ʿ� �پ ������ ����
			node = rotate_right(node);	//RRȸ��
		else
			node = rotate_right_left(node);	//RLȸ��
	}

	return node;
}


//������ �׸��°� �Ӹ� �ƴ϶� ��ȯ�Լ� ���ư��� ��� �˱�
avl_node  *avl_add(avl_node *root, char *new_key)
{
	if (root == NULL)
	{
		root = (avl_node *)malloc(sizeof(struct avl_node));	//new avl_node;
		if (root == NULL)
		{
			fprintf(stderr, "�޸� �Ҵ� ����\n");
			exit(1);
		}
		strcpy(root->word, new_key);
		(root)->left_child = (root)->right_child = NULL;
	}

	//0 = ��� ���̸� s1 = s2
	//0 < ��� ���̸� s1 > s2
	//0 > ��� ���̸� s1 < s2	
	else if (strcmp(new_key, root->word) < 0)	//���ʿ� ����, ����Ž�� Ʈ������ ���� ������ ����
	{
		(root)->left_child = avl_add(root->left_child, new_key);
		root = rebalance(root);	//���� ���ߴ� �Լ�
	}
	else if (strcmp(new_key, root->word) > 0) //�����ʿ� ����
	{
		(root)->right_child = avl_add((root)->right_child, new_key);
		(root) = rebalance(root);
	}
	else
	{
		fprintf(stderr, "�ߺ��� Ű ����\n");
		exit(1);
	}

	root->diff_height = get_height_diff(root);	//���� �Ŀ��� ������ �������� �����Ƿ� �׶��� �����μ��� ������ ��

	return root;
}

//AVL Ʈ���� Ž���Լ�
avl_node *avl_search(avl_node *node, char *key)
{
	if (node == NULL) 
		return NULL;

	if (strcmp(key, node->word) == 0)
		return node;
	else if (strcmp(key, node->word) < 0)
		return avl_search(node->left_child, key);
	else
		return avl_search(node->right_child, key);
}

//LVR
void inorder(avl_node *node)	
{
	if (node == NULL) 
		return;
	inorder(node->left_child);
	printf("< %s, %d >", node->word, node->diff_height);	//��� �� �� ���� ���
	inorder(node->right_child);
}


avl_node * insert_node(avl_node *root)
{
	root = avl_add(root, "Dec");
	root = avl_add(root, "Jan");
	root = avl_add(root, "Apr");
	root = avl_add(root, "Mar");
	root = avl_add(root, "July");
	root = avl_add(root, "Aug");
	root = avl_add(root, "Oct");
	root = avl_add(root, "Feb");
	root = avl_add(root, "Sept");
	root = avl_add(root, "Now");
	root = avl_add(root, "June");
	root = avl_add(root, "May");

	return root;
}

void main()
{
	avl_node *root = NULL;
	root = insert_node(root);

	inorder(root);
	printf("\n");
	//May�� ã��
	avl_node *node = avl_search(root, "May");

	//May ���
	if (node) 
		printf("%s is found\n", node->word);
}

/*
* 4. ������ 12�� �������� 11���� �ִ� �ܾ���� AVL Ʈ���� �ְ� ȭ�鿡 ��� ���ÿ�.
* �� ����� �����μ�(���ʼ���Ʈ���� ���̿� ������ ����Ʈ���� ������ ��)�� ���� ���ÿ�
*/