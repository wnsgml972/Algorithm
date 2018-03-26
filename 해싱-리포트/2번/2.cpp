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
//해싱을 연결리스틀 이용하여 구현한 것

//초기는 다 NULL
void init_table(ListNode *ht[])
{
	int i;
	for (i = 0;i<TABLE_SIZE;i++)
		ht[i] = NULL;
}

//아스키코드 변환
int transform(char *key)
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

//제산함수
int hash_function(char *key)
{
	return transform(key) % TABLE_SIZE;
}

//삽입 함수
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);
	ListNode *ptr;	//삽입할 노드
	ListNode *node_before = NULL;
	ListNode *node;

	for (node = ht[hash_value]; node;node_before = node, node = node->link)	//중복을 검사하면서 끝까지 가줌
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

	if (node_before)	//1개 이상 있었따면
		node_before->link = ptr;	//그 뒤에 ptr을 삽입
	else
		ht[hash_value] = ptr;	//1개도 없었다면 바로 ptr 삽입
}

//탐색 함수
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

// 연결리스트 삭제 함수 
void hash_chain_delete(element item, ListNode *ht[])
{
	int hash_value = hash_function(item.key);
	ListNode *node_before = NULL;
	ListNode *node;

	for (node = ht[hash_value]; node;node_before = node, node = node->link)	//중복을 검사하면서 끝까지 가줌
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

//2. 홈페이지 11장 프로그램 hash_chain에서 hash_chain_delete  함수를 추가하여 원하는 문자열을 삭제할 수 있도록 프로그램을 수정하시오.


