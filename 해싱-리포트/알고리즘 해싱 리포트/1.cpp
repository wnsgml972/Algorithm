
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

//문자로 된 탐색키를 정수로 변환 -> 아스키코드 값을 다 더해줌
int transform(char *key)
{
	int number = 0;
	while (*key)
		number += *key++;
	return number;
}

//제산 함수 이용 (나머지) transform을 이용해 문자를 정수화 시킴으로서 가능
int hash_function(char *key)
{
	return transform(key) % TABLE_SIZE;
}

//선형조사법 사용
//여기선 탐색값이 중복되는 것을 허용하지 않게함!
void hash_lp_add(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);	//제산함수를 이용한 값을 넣음
	
	while (!empty(ht[i])) 
	{
		if (equal(item, ht[i])) 
		{
			printf("탐색 키 중복\n");
			return;
		}
		i = (i + 1) % TABLE_SIZE;	//선형조사법 1씩 증가시킴!
		if (i == hash_value)		//꽉차면 종료
		{
			printf("table is full\n");
			return;
		}
	}
	ht[i] = item;	//1씩 증가시키다가 올바른 자리에 대입
}

//선형조사법을 이용한 탐색
void hash_lp_search(element item, element ht[])
{
	int i, hash_value;
	hash_value = i = hash_function(item.key);
	while (!empty(ht[i])) 
	{
		if (equal(item, ht[i]))		//찾았을 경우
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

//키값을 다 출력시켜줌
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
		if (equal(item, ht[i]))	//삭제
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


//1. 홈페이지 11장 프로그램 hash_lp에서 hash_lp_delete 함수를 추가하여 원하는 문자열을 삭제할 수 있도록 프로그램을 수정하시오.