#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KEY_SIZE 10
#define TABLE_SIZE 13
#define equal(e1,e2) (!strcmp(e1.key,e2.key))

typedef struct 
{
	char key[KEY_SIZE];
}element;

typedef struct ListNode
{
	element item;
	struct ListNode *link;
}ListNode;
ListNode *hash_table[TABLE_SIZE];
//�ؽ��� ���Ḯ��Ʋ �̿��Ͽ� ������ ��

//�ʱ�� �� NULL
void init_table(ListNode *ht[])
{
	int i;
	for (i = 0;i<TABLE_SIZE;i++)
		ht[i] = NULL;
}

//�ƽ�Ű�ڵ� ��ȯ
int transform(char *key)
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

//�����Լ�
int hash_function(char *key)
{
	return transform(key) % TABLE_SIZE;
}

//���� �Լ�
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);
	ListNode *ptr;	//������ ���
	ListNode *node_before = NULL;
	ListNode *node;

	for (node = ht[hash_value]; node;node_before = node, node = node->link)	//�ߺ��� �˻��ϸ鼭 ������ ����
	{
		if (equal(node->item, item)) 
		{
			printf("key is already in the table\n");
			return;
		}
	}

	ptr = new ListNode;
	ptr->item = item;
	ptr->link = NULL;

	if (node_before)	//1�� �̻� �־�����
		node_before->link = ptr;	//�� �ڿ� ptr�� ����
	else
		ht[hash_value] = ptr;	//1���� �����ٸ� �ٷ� ptr ����
}

//Ž�� �Լ�
void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;
	int hash_value = hash_function(item.key);
	for (node = ht[hash_value];node;node = node->link)
	{
		if (equal(node->item, item)) 
		{
			printf("key is found on index %d\n", hash_value);
			return;
		}
	}
	printf("the key is not found\n");
}


void hash_chain_print(ListNode *ht[])
{
	int i;
	ListNode *node;
	for (i = 0;i< TABLE_SIZE;i++) 
	{
		node = ht[i];
		while (node) 
		{
			printf("(%d, %s) ", i, node->item.key);
			node = node->link;
		}
		printf("\n");
	}
}

// ���Ḯ��Ʈ ���� �Լ� 
void hash_chain_delete(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);
	ListNode *node_before = NULL;
	ListNode *node;

	for (node = ht[hash_value]; node;node_before = node, node = node->link)	//�ߺ��� �˻��ϸ鼭 ������ ����
	{
		if (equal(node->item, item))
		{
			if (node_before == NULL)
				ht[hash_value] = node->link;
			else
				node_before->link = node->link;
			printf("key is deleted on the table\n");
			delete[]node;
			return;
		}
	}
	printf("key is not on the table\n");
}

void main()
{
	element tmp;

	init_table(hash_table);
	int op;

	while (1)
	{
		printf("insert the operation you want(0=insert, 1=search, 2=delete, 3=finish)=");
		scanf("%d", &op);

		printf("insert a key >> ");
		scanf("%s", tmp.key);

		switch (op)
		{
		case 0:
			hash_chain_add(tmp, hash_table);
			break;
		case 1:
			hash_chain_find(tmp, hash_table);
			break;
		case 2:
			hash_chain_delete(tmp, hash_table);
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("wrong choice\n");
			exit(0);
		}
		hash_chain_print(hash_table);
	}
}

//2. Ȩ������ 11�� ���α׷� hash_chain���� hash_chain_delete  �Լ��� �߰��Ͽ� ���ϴ� ���ڿ��� ������ �� �ֵ��� ���α׷��� �����Ͻÿ�.


