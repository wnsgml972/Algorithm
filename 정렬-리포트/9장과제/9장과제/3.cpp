#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"	//각 sort들을 헤더파일에 집어넣음

void input_file()
{
	int i, num;
	char name[20];
	FILE *fp;
	
	//파일 쓰기
	fp = fopen("sort.txt", "w");
	if (fp==NULL)
	{
		printf("파일 오픈 실패!\n");
		exit(1);
	}
	fprintf(fp, "%d\n", n);

	for (i = 0; i < n; i++)
	{
		printf("%d번째 숫자와 이름 입력 : ", i + 1);
		scanf("%d", &num);
		scanf("%s", name);
		fprintf(fp, "%d, %s\n", num, name);
	}
	fclose(fp);

	//파일 읽기	
	fp = fopen("sort.txt", "r");
	if (fp == NULL)
	{
		printf("파일 오픈 실패!\n");
		exit(1);
	}
	fscanf(fp, "%d\n", &num); //맨처음 데이터의 숫자 입력한 것을 뺌
	i = -1;
	for (i = 0;i < n;i++)
		fscanf(fp, "%d, %s\n", &list[i].id, list[i].name);

	fclose(fp);
}

void input_user()
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("%d번째 숫자와 이름 입력 : ", i + 1);
		scanf("%d", &list[i].id);
		scanf("%s", list[i].name);
	}
}

int compare(int arg1, int arg2)	//compare 함수
{
	int temp;

	if (cending == 2)	//내림 차순
		SWAP(arg1, arg2, temp);

	if (arg1 > arg2)
		return TRUE;
	else
		return FALSE;
}

int main()
{
	int i, choice;
	int wh = TRUE;	//와일문 조절을 위한 변수
	char choice_sort[2];	//솔트 선택을 위한 변수

	//리스트에 정보 입력 어디에 할 것인지
	while (wh)
	{
		printf("정보를 어디서 입력 받겠습니까?  사용자 입력(1)  파일 입력(2) >>");
		scanf("%d", &choice);
		if (choice > 2 || choice <= 0)
		{
			printf("입력이 잘못되었습니다.\n");
			continue;
		}
		printf("몇개의 데이터를 입력하시겠습니까? >>");
		scanf("%d", &n);
		if (n < 10 || n <= 0)
		{
			printf("10개 이상의 수를 입력해주세요\n");
			continue;
		}
		switch (choice)
		{
		case 1:
			input_user();
			wh = FALSE;
			break;
		case 2:	
			input_file();
			wh = FALSE;
			break;
		default:
			printf("잘못입력하셨습니다.\n\n");
		}
	}

	wh = TRUE;

	while (wh)
	{
		//어떤 정렬? 무슨 차순?
		printf("\n어떤 정렬방식을 택하겠습니까? \n(s: 선택정렬, i; 삽입정렬 b: 버블정렬, h: 쉘 정렬, m: 합병정렬, q: 퀵 정렬) >>");
		scanf("%s", choice_sort);

		printf("\n어떤 차순으로 하시겠습니까? (1 : 오름차순,  2 : 내림차순) >>");
		scanf("%d", &cending);
		if (cending <= 0 || cending > 2)
		{
			printf("잘못된 선택입니다.\n");
			continue;
		}

		switch (choice_sort[0])
		{
		case 's': case 'S':	//대문자까지
			printf("\n선택 정렬\n");
			selection_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'i': case 'I':
			printf("\n삽입 정렬\n");
			insertion_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'b': case 'B':
			printf("\n버블 정렬\n");
			bubble_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'h': case 'H':
			printf("\n쉘 정렬\n");
			shell_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'm': case 'M':
			printf("\n합병 정렬\n");
			merge_sort(list, 0, n - 1, compare);
			wh = FALSE;
			break;
		case 'q': case 'Q':
			printf("\n퀵 정렬\n");
			quick_sort(list, 0, n - 1, compare);
			wh = FALSE;
			break;
		default:
			printf("그런 정렬은 없습니다.\n");
		}
	}

	for (i = 0; i < n; i++)
		printf("%d %s\n", list[i].id, list[i].name);
	printf("\n");
}