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

// 왼쪽 회전 함수
avl_node *rotate_left(avl_node *parent)
{
	avl_node *child = parent->left_child;
	parent->left_child = child->right_child;
	child->right_child = parent;

	return child;
}

// 오른쪽 회전 함수
avl_node *rotate_right(avl_node *parent)
{
	avl_node *child = parent->right_child;
	parent->right_child = child->left_child;
	child->left_child = parent;
	return child;
}
// 오른쪽-왼쪽 회전 함수
avl_node *rotate_right_left(avl_node *parent)
{
	avl_node *child = parent->right_child;
	parent->right_child = rotate_left(child);
	return rotate_right(parent);
}
// 왼쪽-오른쪽 회전 함수
avl_node *rotate_left_right(avl_node *parent)
{
	avl_node *child = parent->left_child;
	parent->left_child = rotate_right(child);
	return rotate_left(parent);
}
// 트리의 높이를 반환
int get_height(avl_node *node)
{
	int height = 0;
	if (node != NULL)
		height = 1 + max(get_height(node->left_child), get_height(node->right_child));
	return height;
}

// 노드의 균형인수를 반환
int get_height_diff(avl_node *node)
{
	if (node == NULL) 
		return 0;
	return
		get_height(node->left_child) - get_height(node->right_child);
}

// 트리를 균형트리로 만든다
avl_node *rebalance(avl_node *node)
{
	int height_diff = get_height_diff(node);
	if (height_diff > 1)	//1보다 클땐 왼쪽
	{
		if (get_height_diff(node->left_child)> 0)	//왼쪽에 왼쪽에 붙어서 균형이 깨짐
			node = rotate_left(node);		//LL회전
		else
			node = rotate_left_right(node);	//LR회전
	}
	else if (height_diff < -1)	//1보다 작을땐 오른쪽
	{
		if (get_height_diff((node)->right_child) < 0)	//오른쪽에 오른쪽에 붙어서 균형이 깨짐
			node = rotate_right(node);	//RR회전
		else
			node = rotate_right_left(node);	//RL회전
	}

	return node;
}


//손으로 그리는것 뿐만 아니라 순환함수 돌아가는 방식 알기
avl_node  *avl_add(avl_node *root, char *new_key)
{
	if (root == NULL)
	{
		root = (avl_node *)malloc(sizeof(struct avl_node));	//new avl_node;
		if (root == NULL)
		{
			fprintf(stderr, "메모리 할당 에러\n");
			exit(1);
		}
		strcpy(root->word, new_key);
		(root)->left_child = (root)->right_child = NULL;
	}

	//0 = 결과 값이면 s1 = s2
	//0 < 결과 값이면 s1 > s2
	//0 > 결과 값이면 s1 < s2	
	else if (strcmp(new_key, root->word) < 0)	//왼쪽에 붙임, 균형탐색 트리에서 값이 작으면 왼쪽
	{
		(root)->left_child = avl_add(root->left_child, new_key);
		root = rebalance(root);	//균형 맞추는 함수
	}
	else if (strcmp(new_key, root->word) > 0) //오른쪽에 붙임
	{
		(root)->right_child = avl_add((root)->right_child, new_key);
		(root) = rebalance(root);
	}
	else
	{
		fprintf(stderr, "중복된 키 에러\n");
		exit(1);
	}

	root->diff_height = get_height_diff(root);	//삽입 후에는 균형이 맞춰져서 나오므로 그때의 균형인수를 받으면 됨

	return root;
}

//AVL 트리의 탐색함수
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
	printf("< %s, %d >", node->word, node->diff_height);	//출력 할 떄 같이 출력
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
	//May를 찾음
	avl_node *node = avl_search(root, "May");

	//May 출력
	if (node) 
		printf("%s is found\n", node->word);
}

/*
* 4. 교과서 12장 연습문제 11번에 있는 단어들을 AVL 트리에 넣고 화면에 찍어 보시오.
* 각 노드의 균형인수(왼쪽서브트리의 높이와 오른쪽 서브트리의 높이의 차)도 같이 찍어보시오
*/