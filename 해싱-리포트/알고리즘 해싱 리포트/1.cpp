
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define KEY_SIZE  10
#define TABLE_SIZE 13
#define empty(e) (strlen(e.key)==0)
#define equal(e1,e2) (!strcmp(e1.key,e2.key))

typedef struct 
{
	char key[KEY_SIZE];
}element;

element hash_table[TABLE_SIZE];

void init_table(element ht[])
{
	int i;
	for (i = 0;i<TABLE_SIZE;i++) 
		ht[i].key[0] = NULL;
}

//���ڷ� �� Ž��Ű�� ������ ��ȯ -> �ƽ�Ű�ڵ� ���� �� ������
int transform(char *key)
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

//���� �Լ� �̿� (������) transform�� �̿��� ���ڸ� ����ȭ ��Ŵ���μ� ����
int hash_function(char *key)
{
	return transform(key) % TABLE_SIZE;
}

//��������� ���
//���⼱ Ž������ �ߺ��Ǵ� ���� ������� �ʰ���!
void hash_lp_add(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);	//�����Լ��� �̿��� ���� ����
	
	while (!empty(ht[i])) 
	{
		if (equal(item, ht[i])) 
		{
			printf("Ž�� Ű �ߺ�\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;	//��������� 1�� ������Ŵ!
		if (i == hash_value)		//������ ����
		{
			printf("table is full\n");
			return;
		}
	}
	ht[i] = item;	//1�� ������Ű�ٰ� �ùٸ� �ڸ��� ����
}

//����������� �̿��� Ž��
void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) 
	{
		if (equal(item, ht[i]))		//ã���� ���
		{
			printf("the key is searched in %d\n", i);
			return;
		}
		i = (i + 1) % TABLE_SIZE;
		if (i == hash_value)	
		{
			printf("key is not on the table\n");
			return;
		}
	}
	printf("key is not on the table\n");
}

//Ű���� �� ��½�����
void hash_lp_print(element ht[])
{
	int i;
	for (i = 0;i<TABLE_SIZE;i++)
		printf("[%d]  %s\n", i, ht[i].key);
}

//
void hash_lp_delete(element item, element ht[])
{
	int i;

	for (i = 0;i < TABLE_SIZE;i++)
	{
		if (equal(item, ht[i]))	//����
		{
			ht[i].key[0] = NULL;
			printf("key is deleted on the table\n");
			return;
		}
	}
	printf("key is not on the table\n");
}

void main()
{
	element tmp;
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
			hash_lp_add(tmp, hash_table);
			break;
		case 1:
			hash_lp_search(tmp, hash_table);
			break;
		case 2:
			hash_lp_delete(tmp, hash_table);
			break;
		case 3:
			exit(0);
			break;
		default:
			printf("wrong choice\n");
			exit(0);
		}

		hash_lp_print(hash_table);
	}
}


//1. Ȩ������ 11�� ���α׷� hash_lp���� hash_lp_delete �Լ��� �߰��Ͽ� ���ϴ� ���ڿ��� ������ �� �ֵ��� ���α׷��� �����Ͻÿ�.