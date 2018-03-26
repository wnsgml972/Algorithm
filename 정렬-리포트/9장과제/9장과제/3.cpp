#define _CRT_SECURE_NO_WARNINGS

#define TRUE 1
#define FALSE 0

#include <stdio.h>
#include <stdlib.h>
#include "sort.h"	//�� sort���� ������Ͽ� �������

void input_file()
{
	int i, num;
	char name[20];
	FILE *fp;
	
	//���� ����
	fp = fopen("sort.txt", "w");
	if (fp==NULL)
	{
		printf("���� ���� ����!\n");
		exit(1);
	}
	fprintf(fp, "%d\n", n);

	for (i = 0; i < n; i++)
	{
		printf("%d��° ���ڿ� �̸� �Է� : ", i + 1);
		scanf("%d", &num);
		scanf("%s", name);
		fprintf(fp, "%d, %s\n", num, name);
	}
	fclose(fp);

	//���� �б�	
	fp = fopen("sort.txt", "r");
	if (fp == NULL)
	{
		printf("���� ���� ����!\n");
		exit(1);
	}
	fscanf(fp, "%d\n", &num); //��ó�� �������� ���� �Է��� ���� ��
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
		printf("%d��° ���ڿ� �̸� �Է� : ", i + 1);
		scanf("%d", &list[i].id);
		scanf("%s", list[i].name);
	}
}

int compare(int arg1, int arg2)	//compare �Լ�
{
	int temp;

	if (cending == 2)	//���� ����
		SWAP(arg1, arg2, temp);

	if (arg1 > arg2)
		return TRUE;
	else
		return FALSE;
}

int main()
{
	int i, choice;
	int wh = TRUE;	//���Ϲ� ������ ���� ����
	char choice_sort[2];	//��Ʈ ������ ���� ����

	//����Ʈ�� ���� �Է� ��� �� ������
	while (wh)
	{
		printf("������ ��� �Է� �ްڽ��ϱ�?  ����� �Է�(1)  ���� �Է�(2) >>");
		scanf("%d", &choice);
		if (choice > 2 || choice <= 0)
		{
			printf("�Է��� �߸��Ǿ����ϴ�.\n");
			continue;
		}
		printf("��� �����͸� �Է��Ͻðڽ��ϱ�? >>");
		scanf("%d", &n);
		if (n < 10 || n <= 0)
		{
			printf("10�� �̻��� ���� �Է����ּ���\n");
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
			printf("�߸��Է��ϼ̽��ϴ�.\n\n");
		}
	}

	wh = TRUE;

	while (wh)
	{
		//� ����? ���� ����?
		printf("\n� ���Ĺ���� ���ϰڽ��ϱ�? \n(s: ��������, i; �������� b: ��������, h: �� ����, m: �պ�����, q: �� ����) >>");
		scanf("%s", choice_sort);

		printf("\n� �������� �Ͻðڽ��ϱ�? (1 : ��������,  2 : ��������) >>");
		scanf("%d", &cending);
		if (cending <= 0 || cending > 2)
		{
			printf("�߸��� �����Դϴ�.\n");
			continue;
		}

		switch (choice_sort[0])
		{
		case 's': case 'S':	//�빮�ڱ���
			printf("\n���� ����\n");
			selection_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'i': case 'I':
			printf("\n���� ����\n");
			insertion_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'b': case 'B':
			printf("\n���� ����\n");
			bubble_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'h': case 'H':
			printf("\n�� ����\n");
			shell_sort(list, n, compare);
			wh = FALSE;
			break;
		case 'm': case 'M':
			printf("\n�պ� ����\n");
			merge_sort(list, 0, n - 1, compare);
			wh = FALSE;
			break;
		case 'q': case 'Q':
			printf("\n�� ����\n");
			quick_sort(list, 0, n - 1, compare);
			wh = FALSE;
			break;
		default:
			printf("�׷� ������ �����ϴ�.\n");
		}
	}

	for (i = 0; i < n; i++)
		printf("%d %s\n", list[i].id, list[i].name);
	printf("\n");
}